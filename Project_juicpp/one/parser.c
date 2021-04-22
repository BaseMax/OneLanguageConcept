#include "parser.h"

extern Source src;
void parseFile(void) {
    // printf("%s\n", src.input);
    nextToken();
    while(src.token != TOKEN_EOF) {
        if(src.token == TOKEN_FN) {
            parseFunction();
        }
        else {
            printf("Error: Bad statement in the file %s\n", tokenName(src.token));
            nextToken();
        }
    }
}
void parseBlock(void) {
    except('{');
    while(src.token != TOKEN_EOF && src.token != '}') {
        printf("STATEMENT:%s\n", tokenName(src.token));
        parseStatement();
    }
    except('}');
}
void parseStatements(void) {
    if(src.token == '{') {
        parseBlock();
    }
    else {
        parseStatement();
    }
}
void parseFunction(void) {
    except(TOKEN_FN);
    char* ident=src.tokenValue;
    except(TOKEN_IDENT);
    printf("==== Define function %s\n", ident);
    parseBlock();
}
void parseStatement(void) {
    if(src.token == TOKEN_IF) {
        parseIf();
    }
    else if(src.token == TOKEN_FOR) {
        parseFor();
    }
    else if(src.token == TOKEN_WHILE) {
        parseWhile();
    }
    else {
        printf("Error: Bad statement in the block %s\n", tokenName(src.token));
        nextToken();
    }
}
void parseWhile(void) {
    except(TOKEN_WHILE);
    parseBlock();
}
void parseFor(void) {
    except(TOKEN_FOR);
    parseBlock();
}
void parseIf(void) {
    except(TOKEN_IF);
    parseBlock();
}
