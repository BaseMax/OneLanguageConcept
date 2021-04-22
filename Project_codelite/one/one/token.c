#include "token.h"

int isLower(char c){
    return c >= 'a' && c <= 'z';
}

int isUpper(char c){
    return c >= 'A' && c <= 'Z';
}

int isAlpha(char c){
    return (
        (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        c == '_'
    );
}

int isIdent(char c){
    return (
        (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') ||
        c == '_'
    );
}

int isNumber(char c){
    return c >= '0' && c <= '9';
}

char* tokenName(unsigned char token){
    // if(token > 127){}
    if(token == TOKEN_IF){
        return "if";
    }
    else if(token == TOKEN_ELSE){
        return "else";
    }
    else if(token == TOKEN_WHILE){
        return "while";
    }
    else if(token == TOKEN_FOR){
        return "for";
    }
    else if(token == TOKEN_REPEAT){
        return "repeat";
    }
    else if(token == TOKEN_FN){
        return "fn";
    }
    else if(token == TOKEN_IDENT) {
        return "ident";
    }
    else if(token == TOKEN_EOF) {
        return "EOF";
    }
    else if(token == TOKEN_ADD_ADD) { return "++"; }
    else if(token == TOKEN_MINUS_MINUS) { return "--"; }
    else if(token == TOKEN_POW) { return "**"; }

    else if(token == TOKEN_REL_GE) { return ">="; }
    else if(token == TOKEN_REL_LE) { return "<="; }
    else if(token == TOKEN_LOG_AND) { return "&&"; }
    else if(token == TOKEN_LOG_OR) { return "||"; }
    else if(token == TOKEN_REL_NE) { return "!="; }
    else if(token == TOKEN_REL_SR) { return ">>"; }
    else if(token == TOKEN_REL_SL) { return "<<"; }

    else if(token == TOKEN_EQUAL_ADD) { return "+="; }
    else if(token == TOKEN_EQUAL_MINUS) { return "-="; }
    else if(token == TOKEN_EQUAL_MUL) { return "*="; }
    else if(token == TOKEN_EQUAL_DIV) { return "/="; }
    else if(token == TOKEN_EQUAL_REM) { return "%="; }

    else if(token == TOKEN_EQUAL_SL) { return "<<="; }
    else if(token == TOKEN_EQUAL_SR) { return ">>="; }
    else if(token == TOKEN_EQUAL_AND) { return "&="; }
    else if(token == TOKEN_EQUAL_OR) { return "|="; }
    else if(token == TOKEN_EQUAL_XOR) { return "^="; }
    return (char[]){token, '\0'};
}

extern Source src;

void except(TokenType tok) {
    if(src.token != tok) {
        printf("Error: expect %s, but found %s:%s\n", tokenName(tok), tokenName(src.token), src.tokenValue);
        exit(-1);
    }
    else {
        nextToken();
    }
}
