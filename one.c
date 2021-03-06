#include "one.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

void usage() {
  printf("USAGE:\n");
  printf("./one <file.one>\n");
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

int main(int argc, char *argv[]) {
  if (argc != 2) {
    usage();
    exit(0);
  }
  char *one = oneread(argv[1]);
  if (one == NULL) {
    error("one file read error\n");
    exit(1);
  }
  parser_init();
  int result = lexer(one);
  
  //L prt to first struct Node. all token in list
  // int value      - token;
  // int token_type - ;
  // int stack_pos - ignore this;
  // int status - ignore this;
  // void *data - additionaldata eg string or char;
  // struct _Node *next;
  // struct _Node *prev;	
  //
  //skip = L->next
  //exept = (L->token == <exp>) ? skip : null
  //or exept = (*((int*)stok->data)  == <exp>) ? skip : null
  
  parser_done();
/*
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
*/
//  twowrite(twobuffer, 10, argv[2]);
//  free(twobuffer);
//  free(t);
  free(one);
  if(result) exit(1);
}
