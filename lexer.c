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
            //todo отправить одним токеном
            IsStrMode = !IsStrMode;
            if(IsStrMode){
                new_token(TOK_STR);
                start_of_stack = src+1;
            }else{
                printf("%.*s\n", src-start_of_stack, start_of_stack);
                new_token(TOK_STR);
                src++;
                src_current_char_pos++;
            }
        }
        if(IsStrMode){
            if(src[0] == TOK_SHIELD_){
                src++;
                src_current_char_pos++;
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
                                       //printf("Extra token TOK_EOL\n");
                                       new_token(TOK_EOL);
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
                                    //printf("token %s %.*s\n",namet[0], length, start_of_stack);
                                    switch(old_data_type_in_the_buffer){
                                        case CHAR_CONTROL:{
                                            int pos = token_search(&one_keywords,sizeof(one_keywords), start_of_stack,length);
                                            int save_length = length;
                                            bool ismodifed = false;
                                            while((pos<0)&&(length >1)){
                                              src--;  
                                              src_current_char_pos--;
                                              length--;
                                              pos = token_search(&one_keywords,sizeof(one_keywords), start_of_stack,length);
                                              ismodifed = true;
                                            }
                                            if(ismodifed){
                                                 printf("The control character is not recognized and therefore modified.\nInitially \"%.*s\"\n",\
                                                         save_length, start_of_stack);
                                            }
                                            if(pos>0){
                                               new_token(pos); 
                                            }else{
                                                if(start_of_stack[0] == TOK_EOL){
                                                   //printf("Extra token TOK_EOL\n");
                                                   new_token(TOK_EOL);
                                                   src_current_line++; 
                                                   src_current_char_pos = 0;
                                                }else{
                                                    printf("An unknown control character was encountered.\nIt should be included in the onetok.h\nline %d pos %d \"%.*s\"\n",\
                                                            src_current_line, (src_current_char_pos-length), length, start_of_stack);
                                                }
                                            }
                                            break;
                                        }
                                        case CHAR_DIGIT:{
                                            // send digit token
                                            regex_t pattern;
                                            char* digit_text = malloc(length+1);
                                            strncpy(digit_text,start_of_stack,length);
                                            digit_text[length]='\0';

                                            int result = regcomp(&pattern, "^[0-9]+$|^0[xX][0-9a-fA-F]+$|^0[bB][01]+$", REG_EXTENDED);
                                            result = regexec(&pattern, digit_text, 0, NULL, 0);
                                            if(result == 0){
                                                regfree(&pattern);
                                                new_token(TOK_DATA_INTEGER);
                                                int base = 0;
                                                if((digit_text[1] == 'b')|(digit_text[1]=='B')){
                                                    digit_text[1]='0';
                                                    base = 2;
                                                }
                                                int val = (int)strtol(digit_text, NULL, base);
                                                free(digit_text);
                                                break;
                                            }
                                            regfree(&pattern);

                                            result = regcomp(&pattern, "^[0-9]+\.[0-9]+$|^[0-9]+\.[0-9]+e[+-][0-9]+$", REG_EXTENDED);
                                            result = regexec(&pattern, digit_text, 0, NULL, 0);
                                            if(result == 0){
                                                regfree(&pattern);
                                                new_token(TOK_DATA_FLOAT);
                                                float val = atof(digit_text);
                                                free(digit_text);
                                                break;
                                            }
                                            regfree(&pattern);

                                            free(digit_text);
                                            break;
                                        }
                                        case CHAR_WORD:{
                                            int pos = token_search(&one_keywords,sizeof(one_keywords), start_of_stack,length);
                                            if(pos>0){
                                               new_token(pos); 
                                            }else{
                                                new_token(TOK_DATA_NAME);
                                                printf("if this is a keyword it should be added in the onetok.h\nline %d pos %d %.*s\n",\
                                                        src_current_line, (src_current_char_pos-length),length, start_of_stack);
                                            }
                                            break;
                                        }
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
            if((pos_search == len_search)&&(token_byte_array[pos_text+1]=='\0')) {
                return ret+TOK_NULL;
            }
        } else {
           pos_text -=pos_search;
           pos_search = 0;
           if(token_byte_array[pos_text]=='\0')ret++;
        }
    }
    return -1;
}