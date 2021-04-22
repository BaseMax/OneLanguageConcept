#include "one.h"
#include <stdio.h>
#include <stdlib.h>

Tokenizer *t;
int linecount = 1;
int charpos = 0;

void usage() {
  printf("USAGE:\n");
  printf("./two <file.one> <file.two>\n");
}

void error(char *message) {
  fprintf(stderr, message);
}

char *oneread(char *onename) {
  FILE *onefile = fopen(onename, "rb");
  if (onefile == NULL) {
    return NULL;
  }
  fseek(onefile, 0L, SEEK_END);
  size_t onefilesize = ftell(onefile);
  rewind(onefile);
  char *onebuffer = (char *)malloc(onefilesize + 1);
  if (onebuffer == NULL) {
    error("error malloc onebuffer\n");
    return NULL;
  }
  size_t onebytesread = fread(onebuffer, 1, onefilesize, onefile);
  if (onebytesread < onefilesize) {
    free(onebuffer);
    error("Could not read file.one\n");
    return NULL;
  }
  onebuffer[onebytesread] = '\0';
  fclose(onefile);
  return onebuffer;
}

void twowrite(char *twobuffer, size_t twobufferlength, char *twoname) {
  FILE *twofile = fopen(twoname, "w+");
  if (twofile == NULL) {
    error("Could not create file.two\n");
    exit(1);
  }
  fwrite(twobuffer, sizeof(char), twobufferlength, twofile);
  fclose(twofile);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    usage();
    exit(0);
  }
  char *one = oneread(argv[1]);
  if (one == NULL) {
    error("one file read error\n");
    exit(1);
  }

  t = NewTokenizer(one);
  if (t == NULL) {
    free(one);
    error("error malloc t\n");
    exit(1);
  }

  while (Token(t) != TOK_EOF) {
    statement(t);
  }

  char *twobuffer = (char *)malloc(10);
  if (twobuffer == NULL) {
    free(one);
    free(t);
    error("error malloc twobuffer\n");
    exit(1);
  }

  twowrite(twobuffer, 10, argv[2]);
  free(twobuffer);
  free(t);
  free(one);
}

void statement(Tokenizer *t) {
  switch (t->token) {
  case OP_COMMENT: {
    skipcommentline(t);
    break;
  }
  case TOK_OTHER: {
    printf("unknown %s line %d pos %d\n", Value(t), linecount, charpos);
    break;
  }
  case TOK_NUMBER: {
    printf("num %d\n", atoi(Value(t)));
    break;
  }
  case TOK_HEXNUMBER: {
    printf("num 0x%lx\n", strtoul(Value(t), NULL, 0));
    break;
  }
  case TOK_BINNUMBER: {
    printf("num %s\n", Value(t));
    break;
  }
  case TOK_STRING: {
    printf("string %s\n", Value(t));
    break;
  }
  case TOK_VARIABLE: {
    printf("%s\n", Value(t));
    break;
  }
  case TOK_EOL: {
    linecount++;
    charpos = 0;
    break;
  }
  default:
    printf("%s\n", Value(t));
  }
  charpos += Next(t);
}