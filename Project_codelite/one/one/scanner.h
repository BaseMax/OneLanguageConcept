#pragma once
#ifndef SCANNER_H
#define SCANNER_H 1
#include "buffer.h"
#include "parser.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *directory;
  char *filename;
  char *input;
  TokenType token;
  char *tokenValue;
} Source;

char *readFile(const char *filename);
void compileFile(char *filename);
void scanFile(char *input);
void nextToken(void);

#endif
