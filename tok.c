#include "tok.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

Tokenizer *NewTokenizer(char *r) {
  Tokenizer *t = (Tokenizer *)malloc(sizeof(Tokenizer));
  t->r = r;
  t->token = TOK_ERROR;
  t->tokenSize = 0;
  return t;
}

int Token(Tokenizer *t) {
  t->tokenSize = 0;
  if ((int)(t->r[0]) == TOK_EOF)
    return t->token = TOK_EOF;

  if (issuitable(t)) {

    if (isnumber(t)) {
      if (t->tokenSize > 2) {
        if (t->r[1] == 'x')
          return t->token = TOK_HEXNUMBER;
        if (t->r[1] == 'b')
          return t->token = TOK_BINNUMBER;
      }
      return t->token = TOK_NUMBER;
    }

    if (iskeyword(t))
      return t->token;

    if (t->r[0] >= 'a' && t->r[0] <= 'z')
      return t->token = TOK_VARIABLE;
  }
  if (isoperation(t))
    return t->token;

  t->tokenSize = 1;
  return t->token = TOK_OTHER;
}

char *Value(Tokenizer *t) {
  static char szBuffer[255] = "";
  if (t->tokenSize > 0) {
    memcpy(&szBuffer[0], t->r, t->tokenSize);
    szBuffer[t->tokenSize] = '\0';
  }
  return szBuffer;
}

void Next(Tokenizer *t) {
  if (t->token == TOK_EOF)
    return;
  t->r += t->tokenSize;
  while (((t->r[0]) != TOK_EOF) && (strchr(SKIP_CHAR, t->r[0]) != NULL))
    t->r++;
}

void SkipEOL(Tokenizer *t) {
  while (t->r[t->tokenSize] != '\n' && t->r[t->tokenSize] != TOK_EOF) {
    t->tokenSize++;
  }
}

bool issuitable(Tokenizer *t) {
  while (strchr(SUITABLE_CHAR, tolower(t->r[t->tokenSize])) != NULL && t->r[t->tokenSize] != TOK_EOF) {
    t->tokenSize++;
  }
  return t->tokenSize != 0;
}

bool isnumber(Tokenizer *t) {
  if (isdigit(t->r[0])) {
    if (strchr(SUITABLE_DIGIT, tolower(t->r[1])) != NULL) {
      int i;
      for (i = 2; i < t->tokenSize; i++) {
        if (!isxdigit(t->r[i]))
          return false;
      }
      if (!isdigit(t->r[1]) && i < 3)
        return false;
      return true;
    }
  }
  return false;
}

bool iskeyword(Tokenizer *t) {
  char *buff = malloc(t->tokenSize + 1);
  memcpy(buff, t->r, t->tokenSize);
  buff[t->tokenSize] = '\0';
  for (int ci = 0; ci < t->tokenSize; ci++)
    buff[ci] = tolower(buff[ci]);
  for (int i = 0; i < KEY__MAX - KEY_START - 1; i++) {
    if (strstr(keywords[i], buff) == keywords[i]) {
      free(buff);
      t->token = i + KEY_START + 1;
      return true;
    }
  }
  free(buff);
  return false;
}

bool isoperation(Tokenizer *t) {
  for (int i = 0; i < OP__MAX - OP_START - 1; i++) {
    if (opchar[i][0] == t->r[0] && opchar[i][1] == t->r[1]) {
      t->tokenSize = 2;
      t->token = i + OP_START + 1;
      return true;
    }
  }

  for (int i = 0; i < OP__MAX - OP_START - 1; i++) {
    if (opchar[i][0] == t->r[0]) {
      t->tokenSize = 1;
      t->token = i + OP_START + 1;
      return true;
    }
  }
  return false;
}