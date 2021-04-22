#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define MAX_NUMLEN 5
#define MAX_CHAR_IN_KEYWORD 16
#define SKIP_CHAR \
  (char[]) { ' ', '\r', '\t' }

#define SUITABLE_CHAR \
  (char[]) { "abcdefghijklmnopqrstuvwxyz_0123456789" }

#define SUITABLE_DIGIT \
  (char[]) { "xb0123456789" }

typedef enum {
  TOK_EOF = 0,
  TOK_NUMBER,
  TOK_HEXNUMBER,
  TOK_BINNUMBER,
  TOK_VARIABLE,
  TOK_OTHER = -2,
  TOK_ERROR = -3
} TokenType;

typedef enum {
  OP_START = 100,
  TOK_EOL,
  OP_PLUS,
  OP_PLUSPLUS,
  OP_COMMENT,
  OP__MAX
} OpNum;

#define opchar \
  (const char * [OP__MAX - OP_START - 1]) { "\n", "+", "++", "//" }

typedef enum {
  KEY_START = 200,
  KEY_IF,
  KEY_ELSE,
  KEY_DIV,
  KEY_FN,
  KEY_MAIN,
  KEY__MAX
} KeyWordsNum;

#define keywords \
  (const char * [KEY__MAX - KEY_START - 1]) { "if", "else", "div", "fn", "main" }

typedef struct {
  char *r;
  int token;
  int tokenSize;
} Tokenizer;

Tokenizer *NewTokenizer(char *data2parse);
int Token(Tokenizer *t);
char *Value(Tokenizer *t);
void Next(Tokenizer *t);
void SkipEOL(Tokenizer *t);
bool issuitable(Tokenizer *t);
bool isnumber(Tokenizer *t);
bool iskeyword(Tokenizer *t);
bool isoperation(Tokenizer *t);