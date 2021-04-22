#include "lexer.h"
#include "parser.h"

Node* L;
Node* Ltop;
int status;


int new_token(sToken *stok){
    int ret = 0;
    //int stack_length=depth();
    if(getvalue(0) == TOK_START_BLOCK_COMMENT){
        if(*((int*)stok->data) == TOK_END_BLOCK_COMMENT){
            pop();
        }
        return 0;
    }
    if(getvalue(0) == TOK_LINE_COMMENT){
        if(stok->token == TOK_EOL){
            pop();
        }
        if(*((int*)stok->data) == TOK_SHIELD){
            push(stok);
        }
        return 0;
    }
    if((getvalue(1) == TOK_LINE_COMMENT)&&(getvalue(0)==TOK_SHIELD)){
        if(stok->token == TOK_EOL){
            pop();
        }
        return 0;
    }
    if((getvalue(0)==TOK_SHIELD)){
        if(stok->token == TOK_EOL){
            pop();
        }
        return 0;
    }
    switch(stok->token){
        case TOK_DATA_CONTROL:{
            switch (*((int*)stok->data)){
                    case TOK_START_BLOCK_COMMENT:
                    case TOK_LINE_COMMENT:
                    case TOK_SHIELD:{
                                    push(stok);
                                    break;
                    }
                    case TOK_PARENT_LEFT:{
                                    if(check_stack(TOK_DATA_NAME,TOK_DATA_VARAIBLE_TYPE)){
                                      printf("function detected %s\n",(char*)getdata(0));
                                    }                        
                                    break;
                    }
                //all in stack for test
                    default:{
                            push(stok);
                            break;
                    }
            }
            break;
        }
        //all in stack for test
        default:{
            push(stok);
            break;
        }
        /*
        case TOK_DATA_STRING:{
            push(stok);
            break;
        }
        case TOK_DATA_NAME:{
            push(stok);
            break;
        }
         */ 
            
    }

 // for test
/*
   if(stok->token == TOK_DATA_STRING){
        printf("\"%s\"\n",((char*)stok->data));
   }

   if(stok->token == TOK_DATA_INTEGER){
       printf("%s\n",((char*)stok->data));
   }
   if(stok->token == TOK_DATA_FLOAT){
       printf("%s\n",((char*)stok->data));
   }
   if(stok->token == TOK_DATA_NAME){
       printf("%s\n",((char*)stok->data));
   }
   if((stok->token == TOK_DATA_CONTROL)){
       printf("%d\n",*(int*)stok->data);
   }
 */  
   return ret;
}

void parser_init(){
    L = (Node*)malloc(sizeof(Node));
    L->value = 0;
    L->token_type = TOK_DATA_OTHERS;
    L->next = NULL;
    L->prev = NULL;
    L->data = NULL;
    Ltop = L;
}

void parser_done(){
    while(Ltop->prev != NULL){
        Node *Ltmp = Ltop->prev;
        if(Ltop->data != NULL) free(Ltop->data);
        free(Ltop);
        Ltop = Ltmp;
    }
    free(L);
}

void* token_strcopy(char* data){
   void *ret = NULL;
   char *p = data; 
   while(p[0]){p++;};
   ret = malloc(p-data+1);
   strcpy(ret,data);
   return ret;
}

void push(sToken *_stok){
    Node * Ltmp = (Node*)malloc(sizeof(Node));
    Ltmp->prev = Ltop;
    Ltmp->next = NULL;
    Ltop->next = Ltmp;
    switch(_stok->token){
        case TOK_DATA_STRING:{
            Ltmp->value = TOK_DATA_STRING;
            Ltmp->token_type = TOK_DATA_OTHERS;
            Ltmp->data = token_strcopy((char*)_stok->data); //stok->data = char* string
            break;
        }
        case TOK_DATA_CONTROL:{
            Ltmp->value = *(int*)_stok->data; //stok->data = int* token ( onetok.h && CONTROL_CHAR )
            Ltmp->token_type = TOK_DATA_CONTROL;
            Ltmp->data = NULL;
            break;

        }
        case TOK_DATA_INTEGER:{
            Ltmp->value = TOK_DATA_INTEGER;
            Ltmp->token_type = TOK_DATA_OTHERS;
            Ltmp->data = token_strcopy((char*)_stok->data);//stok->data = char* Decimal, Hex, Bin
            break;
        }
        case TOK_DATA_FLOAT:{
            Ltmp->value = TOK_DATA_FLOAT;
            Ltmp->token_type = TOK_DATA_OTHERS;
            Ltmp->data = token_strcopy((char*)_stok->data);//stok->data = char* Float: normal, normalized 
            break;

        }
        case TOK_DATA_OPERATION:
        case TOK_DATA_VARAIBLE_TYPE:
        case TOK_DATA_KEYWORD:{
            Ltmp->value = *(int*)_stok->data; //    stok->data = int* token (onetok.h)
            Ltmp->token_type = _stok->token;
            Ltmp->data = NULL;
            break;
        }

        case TOK_DATA_NAME:{
            Ltmp->value = TOK_DATA_NAME;
            Ltmp->token_type = TOK_DATA_OTHERS;
            Ltmp->data = token_strcopy((char*)_stok->data);//stok->data = char* user-defined name    
            break;

        }
        default:{ //however it shouldn't have happened TOK_EOL
            Ltmp->value = _stok->token;
            Ltmp->token_type = _stok->token;
            Ltmp->data = NULL;
            break;
        }
    }
    Ltop = Ltmp;
}

void pop(){
    if(Ltop->prev != NULL){
        Node *Ltmp = Ltop->prev;
        if(Ltop->data != NULL) free(Ltop->data);
        free(Ltop);
        Ltop = Ltmp;
    }
}

int depth(){
    int length = 0;
    Node * Ltmp = Ltop;
    while (Ltmp->prev != NULL){
        length++;
        Ltmp = Ltmp->prev;
    }
    return length;
}

int getvalue(int pos){
    int tpos = 0;
    Node * Ltmp = Ltop;
    while ((tpos!=pos)&&(Ltmp->prev != NULL)){
        tpos++;
        Ltmp = Ltmp->prev;
    }
    return (tpos==pos)?Ltmp->value:-1;
}

int gettoken(int pos){
    int tpos = 0;
    Node * Ltmp = Ltop;
    while ((tpos!=pos)&&(Ltmp->prev != NULL)){
        tpos++;
        Ltmp = Ltmp->prev;
    }
    return (tpos==pos)?Ltmp->token_type:-1;
}

void* getdata(int pos){
    int tpos = 0;
    Node * Ltmp = Ltop;
    while ((tpos!=pos)&&(Ltmp->prev != NULL)){
        tpos++;
        Ltmp = Ltmp->prev;
    }
    return (tpos==pos)?Ltmp->data:NULL;
}


bool _check_stack(int count, ...) {
	va_list	arg_ptr;
	int		i = 0;

	va_start(arg_ptr, count);

	for (i = 0; i < count; i++) {
        int j=va_arg(arg_ptr, int);
        switch(j){
            case TOK_DATA_OPERATION:
            case TOK_DATA_VARAIBLE_TYPE:
            case TOK_DATA_KEYWORD:{
                    if(gettoken(i) != j){
                        i = count+1;
                    }
                    break;
            }
            default:{
                if(getvalue(i) != j){
                    i = count+1;
                }
            }
	}
    }
	return (i>count)?false:true;
}
