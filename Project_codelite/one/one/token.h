#ifndef TOKEN_H
#define TOKEN_H 1

int isLower(char c);
int isUpper(char c);
int isAlpha(char c);
int isIdent(char c);
int isNumber(char c);
char* tokenName(unsigned char token);

typedef enum {
    TOKEN_EOF=128,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_FOR,
    TOKEN_REPEAT,
    TOKEN_FN,
    TOKEN_IDENT,

    TOKEN_ADD_ADD,//++
    TOKEN_MINUS_MINUS,//--
    TOKEN_POW,//**
    TOKEN_REL_GE,//>=
    TOKEN_REL_LE,//<=
    TOKEN_LOG_AND,//&&
    TOKEN_LOG_OR,//||
    TOKEN_REL_NE,//!=
    TOKEN_REL_SR,//>>
    TOKEN_REL_SL,//<<

    TOKEN_EQUAL_ADD,//+=
    TOKEN_EQUAL_MINUS,//-=
    TOKEN_EQUAL_MUL,//*=
    TOKEN_EQUAL_DIV,///=
    TOKEN_EQUAL_REM,//%=
    TOKEN_EQUAL_SL,//<<=
    TOKEN_EQUAL_SR,//>>=
    TOKEN_EQUAL_AND,//&=
    TOKEN_EQUAL_OR,//|=
    TOKEN_EQUAL_XOR,//^=
} TokenType;

void except(TokenType tok);

#include <stdlib.h>
#include "parser.h"
#endif
