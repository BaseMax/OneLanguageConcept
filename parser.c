#include "lexer.h"
#include "parser.h"

Node* L;
Node* Ltop;
int status = ST_EMPTY;
int stack_marker = 0;


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
    if(! is_the_token_usable(stok, status)){
        return 1;
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
                    case TOK_OP_MUL:{
                        CH_STATUS(ST_TYPE_SPECIFED,ST_ASTERISK_DECLARED_FOR_TYPE);
                    }
                    case TOK_VIRGOL:{
                        CH_STATUS(ST_NAME_DECLARED,ST_NEXT_NAME);
                    }
                    case TOK_OP_DEFINE:{
                        CH_STATUS(ST_NAME_DECLARED,ST_NEXT_NAME);
                        CH_STATUS(ST_NEXT_VIRGOL_EOL_DEFINE,ST_WAIT_EXPRESION);
                    }
                    default:{
                        ret = 1;
                        break;
                    }
            }
            break;
        }
        case TOK_DATA_VARAIBLE_TYPE:{
            if( status == ST_EMPTY ){ 
                stack_marker = depth();
                status = ST_TYPE_SPECIFED;
                push(stok);                                 
                break;
            }
            ret = 1;
            break;
        }
        case TOK_DATA_NAME:{
            if( status == ST_EMPTY ){
                stack_marker = depth();
                status = ST_NAME_DECLARED;
                push(stok);                          
                break;
            }
            CH_STATUS(ST_TYPE_SPECIFED,ST_NAME_DECLARED);
            CH_STATUS(ST_ASTERISK_DECLARED_FOR_TYPE,ST_NAME_DECLARED);
            CH_STATUS(ST_NEXT_NAME,ST_NEXT_VIRGOL_EOL_DEFINE);
            ret = 1;
            break;
        }
        case TOK_EOL:{
            if(status == ST_NAME_DECLARED){
                //one var declared set to programm tree
                //& remove from stack
                while((Ltop->stack_pos == stack_marker) && (Ltop -> prev != NULL)) pop();
                status = Ltop->status;
                break;
            }
            if(status == ST_NEXT_VIRGOL_EOL_DEFINE){
                //several var declared set to programm tree
                //& remove from stack
                while((Ltop->stack_pos == stack_marker) && (Ltop -> prev != NULL)) pop();
                status = Ltop->status;
                break;
            }
            if(status == ST_EXPRESION){
                //var + assigned value declared set to programm tree
                //& remove from stack
                while((Ltop->stack_pos == stack_marker) && (Ltop -> prev != NULL)) pop();
                status = Ltop->status;
                break;
            }
            ret = 1;
            break;
        }
        case TOK_DATA_INTEGER:{
             CH_STATUS(ST_WAIT_EXPRESION,ST_EXPRESION);
        }
        default:{
            ret = 1;
            break;
        }
    }
   return ret;
}

void parser_init(){
    L = (Node*)malloc(sizeof(Node));
    L->value = 0;
    L->stack_pos = stack_marker;
    L->status = ST_EMPTY;
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
    Ltmp->stack_pos = stack_marker;
    Ltmp->status = status;
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
        Ltop->next = NULL;
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

