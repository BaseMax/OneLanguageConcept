#include "lexer.h"
#include "parser.h"
#include <regex.h>


char* src;
char* start_of_stack;
int src_current_char_pos = 1;
int src_current_line = 1;
CharType new_data_type_in_the_buffer = CHAR_BAD;
CharType old_data_type_in_the_buffer = CHAR_BAD;
bool IsStrMode=false;


int lexer(char* programm_src){
    
    int result = 0;
    src = programm_src;
    skip_unnecessary_char();
    while(src[0] != TOK_EOF) {
        if(src[0] == TOK_STR) {
            IsStrMode = !IsStrMode;
            if(IsStrMode){
                //new_token(TOK_STR);
                start_of_stack = src+1;
            }else{
                sToken *stok = malloc(sizeof(sToken));
                stok->token = TOK_DATA_STRING;
                stok->data = malloc(src-start_of_stack+1);
                memcpy(stok->data,start_of_stack,src-start_of_stack);
                *((char*)stok->data+(src-start_of_stack)) = '\0';
                if(new_token(stok) != 0){
                    //todo
                    //error message here;
                }
                free(stok->data);
                free(stok);
                src++;
                src_current_char_pos++;
            }
        }
        if(IsStrMode){
            if(src[0] == TOK_SHIELD_){
                src++;
                src_current_char_pos++;
            }
            if(src[0] == TOK_EOL){
                errormessage("completion character \" expected");
                IsStrMode = false;
            }
        }else{
            new_data_type_in_the_buffer = character_check(TOLOWER(src[0]));
            unsigned char compare_result = calc_result(new_data_type_in_the_buffer,old_data_type_in_the_buffer);
            switch(compare_result){
                case 0b10001000://old bad     new bad
                                {
                                    if(strchr(SKIP_CHAR, src[0]) == NULL)
                                        printf("An unknown symbol was encountered.\nIt should be included in one of the lexer.h lists\nline %d pos %d - %d ('%c')\n",src_current_line, (src_current_char_pos-1), src[0],src[0]);
                                    if(src[0] == TOK_EOL){
                                       sToken *stok = malloc(sizeof(sToken));
                                       stok->token = TOK_EOL;
                                       stok->data = malloc(sizeof(int));
                                       *((int*)stok->data) = TOK_EOL;
                                       if(new_token(stok) != 0){
                                            errormessage("unexpected end of the line");
                                           //todo
                                           //error message here; 
                                       }
                                       free(stok->data);
                                       free(stok);
                                       src_current_line++; 
                                       src_current_char_pos = 0;
                                    }
                                    if(skip_unnecessary_char()){
                                        src--;
                                        src_current_char_pos--;
                                    }
                                    break;
                                }
                case 0b00010001://old control new control
                case 0b00100010://old digit   new digit
                case 0b01000100://old word    new word
                                {
                                break;
                                }
                case 0b10000001://old bad     new control
                case 0b10000010://old bad     new digit
                case 0b10000100://old bad     new word
                                {
                                    old_data_type_in_the_buffer = new_data_type_in_the_buffer;
                                    start_of_stack = src;
                                    break;
                                }
                case 0b00010010://old control new digit
                case 0b00010100://old control new word
                case 0b00100001://old digit   new control
                case 0b00100100://old digit   new word
                case 0b01000001://old word    new control
                case 0b01000010://old word    new digit
                case 0b00011000://old control new bad
                case 0b00101000://old digit   new bad
                case 0b01001000://old word    new bad
                                {
                                    int length = src-start_of_stack;
                                    switch(old_data_type_in_the_buffer){
                                        case CHAR_CONTROL:{
                                            int pos = token_search((char*)&one_keywords,sizeof(one_keywords), start_of_stack,length);
                                            //int save_length = length;
                                            //todo
                                            while((pos<0)&&(length >1)){
                                              src--;  
                                              src_current_char_pos--;
                                              length--;
                                              pos = token_search((char*)&one_keywords,sizeof(one_keywords), start_of_stack,length);
                                              //todo
                                              //ismodifed = true;
                                            }
                                            if(pos>0){
                                               sToken *stok = malloc(sizeof(sToken));
                                               stok->token = TOK_DATA_CONTROL;
                                               stok->data = malloc(sizeof(int));
                                               *((int*)stok->data) = pos;
                                               if(new_token(stok) != 0){
                                                    errormessage("not expected control character");
                                                   //todo
                                                   //error message here; 
                                               }
                                               free(stok->data);
                                               free(stok);
                                            }else{
                                                if(start_of_stack[0] == TOK_EOL){
                                                   sToken *stok = malloc(sizeof(sToken));
                                                   stok->token = TOK_EOL;
                                                   stok->data = malloc(sizeof(int));
                                                   *((int*)stok->data) = TOK_EOL;
                                                   if(new_token(stok) != 0){
                                                        errormessage("unexpected end of the line");
                                                       //todo
                                                       //error message here; 
                                                   }
                                                   free(stok->data);
                                                   free(stok);
                                                   src_current_line++; 
                                                   src_current_char_pos = 0;
                                                }else{
                                                    printf("Error at line %d pos %d \"%.*s\"\n",src_current_line, (src_current_char_pos-length), length, start_of_stack);
                                                }
                                            }
                                            break;
                                        }
                                        case CHAR_DIGIT:{
                                            regex_t pattern;
                                            char* digit_text = malloc(length+1);
                                            strncpy(digit_text,start_of_stack,length);
                                            digit_text[length]='\0';

                                            int result = regcomp(&pattern, "^[0-9]+$|^0[xX][0-9a-fA-F]+$|^0[bB][01]+$", REG_EXTENDED);
                                            result = regexec(&pattern, digit_text, 0, NULL, 0);
                                            if(result == 0){
                                                regfree(&pattern);
//                                                int base = 0;
//                                                if((digit_text[1] == 'b')|(digit_text[1]=='B')){
//                                                    digit_text[1]='0';
//                                                    base = 2;
//                                                }
//                                                int val = (int)strtol(digit_text, NULL, base);
                                                sToken *stok = malloc(sizeof(sToken));
                                                stok->token = TOK_DATA_INTEGER;
                                                stok->data = digit_text;
                                                if(new_token(stok) != 0){
                                                    errormessage("not expected integer number");
                                                    //todo
                                                    //error message here;
                                                }
                                                free(stok);
                                                free(digit_text);
                                                break;
                                            }
                                            regfree(&pattern);

                                            result = regcomp(&pattern, "^[0-9]+\\.[0-9]+$|^[0-9]+\\.[0-9]+e[+-][0-9]+$", REG_EXTENDED);
                                            result = regexec(&pattern, digit_text, 0, NULL, 0);
                                            if(result == 0){
                                                regfree(&pattern);
//                                                float val = atof(digit_text);
                                                sToken *stok = malloc(sizeof(sToken));
                                                stok->token = TOK_DATA_FLOAT;
                                                stok->data = digit_text;
                                                if(new_token(stok) != 0){;
                                                    errormessage("not expected float number");
                                                    //todo
                                                    //error message here;
                                                }
                                                free(stok);
                                                free(digit_text);
                                                break;
                                            }
                                            regfree(&pattern);

                                            free(digit_text);
                                            break;
                                        }
                                        case CHAR_WORD:{
                                            int pos = token_search((char*)&one_keywords,sizeof(one_keywords), start_of_stack,length);
                                            if(pos>0){
                                               int ttype = typekeyword(pos);
                                               sToken *stok = malloc(sizeof(sToken));
                                               stok->token = ttype;
                                               stok->data = malloc(sizeof(int));
                                               *((int*)stok->data) = pos;
                                               if(new_token(stok) != 0){
                                                    errormessage("not expected keyword");
                                                   //todo
                                                   //error message here; 
                                               }
                                               free(stok->data);
                                               free(stok);
                                            }else{
                                                sToken *stok = malloc(sizeof(sToken));
                                                stok->token = TOK_DATA_NAME;
                                                stok->data = malloc(length+1);
                                                memcpy(stok->data,start_of_stack,length);
                                                *((char*)stok->data+length) = '\0';
                                                if(new_token(stok) != 0){
                                                    errormessage("not expected name");
                                                    //todo
                                                    //error message here;
                                                }
                                                free(stok->data);
                                                free(stok);
                                            }
                                            break;
                                        }
                                        default:{}
                                    }
                                    src--;
                                    src_current_char_pos--;
                                    if(skip_unnecessary_char()){
                                        src--;
                                        src_current_char_pos--;
                                    }
                                    old_data_type_in_the_buffer = CHAR_BAD;
                                    break;
                                }
            }
        }
        src++;
        src_current_char_pos++;
    }
    
    return result;
}

bool skip_unnecessary_char(){
  bool ret = false;
  while (((src[0]) != TOK_EOF) && (strchr(SKIP_CHAR, src[0]) != NULL)) {
      src++;
      ret = true;
      src_current_char_pos++;
  }
  return ret;    
}

CharType character_check(char in){
   CharType ret = CHAR_BAD; 
   switch(old_data_type_in_the_buffer){
        case CHAR_BAD://old bad
        {
           if (strchr(CONTROL_CHAR, in) != NULL) {
               ret = CHAR_CONTROL;
           }else if(strchr(DIGIT_CHAR_START, in) != NULL){
               ret = CHAR_DIGIT;
           }else if(strchr(WORD_CHAR, in) != NULL){
               ret = CHAR_WORD;
           }
           break;
        }
        case CHAR_CONTROL://old control
        {
           if (strchr(CONTROL_CHAR, in) != NULL) {
               ret = CHAR_CONTROL;
           }
           break;
        }
        case CHAR_DIGIT://old digit
        {
           if(strchr(DIGIT_CHAR, in) != NULL){
               ret = CHAR_DIGIT;
           }
           break;
        }
        case CHAR_WORD://old word
        {
           if(strchr(WORD_CHAR, in) != NULL){
               ret = CHAR_WORD;
           }
           break;
        }
   }
   return ret;
}

unsigned char calc_result(CharType news,CharType olds){
   unsigned char res ='\0';
   switch(olds){
       case CHAR_CONTROL:{res |= 0x10; break;}
       case CHAR_DIGIT:{res |= 0x20; break;}
       case CHAR_WORD:{res |= 0x40; break;}
       case CHAR_BAD: {res |= 0x80; break;}
   }
   switch(news){
       case CHAR_CONTROL:{res |= 0x01; break;}
       case CHAR_DIGIT:{res |= 0x02; break;}
       case CHAR_WORD:{res |= 0x04; break;}
       case CHAR_BAD: {res |= 0x08; break;}
   }
   return res;
}

int token_search(char* token_byte_array,int token_byte_array_length, char* keyword,int keyword_length){
    int ret = 1;
    int pos_search = 0;
    int pos_text = 0;
    int len_search = keyword_length;
    int len_text = token_byte_array_length;    
    
    for (pos_text = 0; pos_text < len_text;++pos_text) {
        if(token_byte_array[pos_text] == keyword[pos_search]) {
            ++pos_search;
            if((pos_search == len_search)&(token_byte_array[pos_text+1]=='\0')) {
                return ret+TOK_START;
            }
        } else {
           pos_text -=pos_search;
           pos_search = 0;
           while(token_byte_array[pos_text] != '\0'){
               pos_text++;
           }
           ret++;
        }
    }
    return -1;
}

int typekeyword(int token){
    int ret = TOK_DATA_OTHERS;
    switch(token){
        case TOK_START ... TOK_END_OPERATION-1:{
            ret = TOK_DATA_OPERATION;
            break;
        }
        case TOK_END_OPERATION+1 ... TOK_END_VARAIBLE_TYPE-1:{
            ret = TOK_DATA_VARAIBLE_TYPE;
            break;
        }
        case TOK_END_VARAIBLE_TYPE+1 ... TOK_END_KEYWORD-1:{
            ret = TOK_DATA_KEYWORD;
            break;
        }
    }
    return ret;
}


void errormessage(char* msg){
    printf("Error %s at line %d pos %ld \"%.*s\"\n",msg, src_current_line, (src_current_char_pos-(src-start_of_stack)), (int)(src-start_of_stack), start_of_stack);
}