#include "lexer.h"
#include "parser.h"

Node* L;
Node* Ltop;
int status;


void new_token(int token){
    int stack_length=depth();
    if(getvalue(0) == TOK_START_BLOCK_COMMENT){
        if(token == TOK_END_BLOCK_COMMENT){
            pop();
            printf("end comments\n\n"); 
        }
//        printf(" skip \n"); 
        return;
    }
    if(getvalue(0) == TOK_LINE_COMMENT){
        if(token == TOK_EOL){
            pop();
            printf("end comments\n\n"); 
        }
        if(token == TOK_SHIELD){
            push(token);
        }
//        printf(" skip \n"); 
        return;
    }
    if((getvalue(1) == TOK_LINE_COMMENT)&&(getvalue(0)==TOK_SHIELD)){
        if(token == TOK_EOL){
            pop();
        }
//        printf(" skip \n"); 
        return;
    }
    switch(token){
        case TOK_START_BLOCK_COMMENT:
        case TOK_LINE_COMMENT:{
            printf("start comments\n\n"); 
            push(token);
            break;
        }
    }
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