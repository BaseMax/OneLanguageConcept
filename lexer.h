#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  CHAR_CONTROL = 4092,
  CHAR_DIGIT,
  CHAR_WORD,
  CHAR_BAD
} CharType;

#define SKIP_CHAR (char[]) { ' ', '\r', '\t' , '\n', '\0'}
#define CONTROL_CHAR (char[]) { ',', '(', ')','{','}','#','"',':','\\' ,'/','*','=', '+', '-', '.','\0'}
#define DIGIT_CHAR_START (char[]) { "0123456789\0" }
#define DIGIT_CHAR (char[]) { "+-xbabcdef.0123456789\0"  }
#define WORD_CHAR (char[]) {"abcdefghijklmnopqrstuvwxyz_.0123456789\0"}
#define TOK_EOF 0
#define TOK_EOL '\n'
#define TOK_STR '\"'
#define TOK_SHIELD_ '\\'


#define ISLOWER(c) ('a' <= (c) && (c) <= 'z')
#define ISUPPER(c) ('A' <= (c) && (c) <= 'Z')
#define TOUPPER(c) (ISLOWER(c) ? 'A' + ((c) - 'a') : (c))
#define TOLOWER(c) (ISUPPER(c) ? ((c) -'A') + 'a' : (c))

enum one_token {
TOK_NULL = 255
#define DEF(id, str) ,id
#include "onetok.h"
#undef DEF
,
TOK_DATA_INTEGER,
TOK_DATA_FLOAT,
TOK_DATA_NAME
//extra token here
};

static const char one_keywords[] = 
#define DEF(id, str) str "\0"
#include "onetok.h"
#undef DEF
;

int token_search(char*, int, char*, int);
unsigned char calc_result(CharType,CharType);
CharType character_check(char);
bool skip_unnecessary_char(void);
int lexer(char*);