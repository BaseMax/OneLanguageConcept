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
            push(*((int*)stok->data));
        }
        return 0;
    }
    if((getvalue(1) == TOK_LINE_COMMENT)&&(getvalue(0)==TOK_SHIELD)){
        if(stok->token == TOK_EOL){
            pop();
        }
        return 0;
    }
    switch(stok->token){
        case TOK_DATA_CONTROL:{
            switch (*((int*)stok->data)){
                case TOK_START_BLOCK_COMMENT:
                case TOK_LINE_COMMENT:{
                push(*((int*)stok->data));
                break;
            }
            break;
        }
        }
    }

 // for test
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
   
   return ret;
}

void parser_init(){
    L = (Node*)malloc(sizeof(Node));
    L->value = malloc(sizeof(int));
    L->next = NULL;
    L->prev = NULL;
    Ltop = L;
    *((int*)Ltop->value) = 0;
}

void parser_done(){
    while(Ltop->prev != NULL){
        Node *Ltmp = Ltop->prev;
        if(Ltop->value != NULL) free(Ltop->value);
        free(Ltop);
        Ltop = Ltmp;
    }
    free(L);
}

void push(int value){
    Node * Ltmp = (Node*)malloc(sizeof(Node));
    Ltmp->prev = Ltop;
    Ltmp->next = NULL;
    Ltop->next = Ltmp;
    Ltmp->value= malloc(sizeof(int));
    Ltop = Ltmp;
    *((int*)Ltop->value) = value;
}

void pop(){
    if(Ltop->prev != NULL){
        Node *Ltmp = Ltop->prev;
        if(Ltop->value != NULL) free(Ltop->value);
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
    return (tpos==pos)?*((int*)Ltmp->value):-1;
}