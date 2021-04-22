#include "scanner.h"

char *readFile(const char *filename) {
  FILE *file = fopen(filename, "rb");
  if (file == NULL)
    return NULL;

  // Find out how big the file is.
  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  // Allocate a buffer for it.
  char *buffer = (char *)malloc(fileSize + 1);
  if (buffer == NULL) {
    fprintf(stderr, "Could not read file \"%s\".\n", filename);
    exit(74);
  }
  // Read the entire file.
  size_t bytesRead = fread(buffer, 1, fileSize, file);
  if (bytesRead < fileSize) {
    fprintf(stderr, "Could not read file \"%s\".\n", filename);
    exit(74);
  }
  // Terminate the string.
  buffer[bytesRead] = '\0';
  fclose(file);
  return buffer;
}

Source src;

void compileFile(char *filename) {
  src.filename = filename;
  src.input = readFile(filename);
  parseFile();
}

void nextToken(void) {
  while (*src.input != '\0') {
    src.tokenValue = "";
    if (*src.input == '\n' || *src.input == '\t' || *src.input == ' ') {
      src.input++;
      continue;
    } else if (isNumber(*src.input) == 1) {
      buffer_t *buf = buffer_new();
      while (isNumber(*src.input) == 1) {
        buffer_appendf(buf, "%c", *src.input++);
      }
      src.tokenValue = buf->data;
    } else if (isAlpha(*src.input) == 1) {
      buffer_t *buf = buffer_new();
      while (isIdent(*src.input) == 1) {
        buffer_appendf(buf, "%c", *src.input++);
      }
      src.tokenValue = buf->data;
      if (strcmp(src.tokenValue, "fn") == 0) {
        src.token = TOKEN_FN;
      } else if (strcmp(src.tokenValue, "while") == 0) {
        src.token = TOKEN_WHILE;
      } else if (strcmp(src.tokenValue, "for") == 0) {
        src.token = TOKEN_FOR;
      } else if (strcmp(src.tokenValue, "if") == 0) {
        src.token = TOKEN_IF;
      } else if (strcmp(src.tokenValue, "else") == 0) {
        src.token = TOKEN_ELSE;
      } else {
        src.token = TOKEN_IDENT;
      }
      return;
    } else if (*src.input == '{') {
      src.input++;
      src.token = '{';
      return;
    } else if (*src.input == '}') {
      src.input++;
      src.token = '}';
      return;
    } else if (*src.input == '(') {
      src.input++;
      src.token = '(';
      return;
    } else if (*src.input == ')') {
      src.input++;
      src.token = ')';
      return;
    } else if (*src.input == '%') {
      src.input++;
      src.token = '%';
      return;
    } else if (*src.input == '/') {
      src.input++;
      src.token = '/';
      return;
    } else if (*src.input == '^') {
      src.input++;
      if (*src.input == '=') {
        src.token = TOKEN_EQUAL_XOR;
        src.input++;
      } else {
        src.token = '^';
      }
      return;
    } else if (*src.input == '%') {
      src.input++;
      if (*src.input == '=') {
        src.token = TOKEN_EQUAL_REM;
        src.input++;
      } else {
        src.token = '%';
      }
      return;
    } else if (*src.input == '+') {
      src.input++;
      if (*src.input == '+') {
        src.token = TOKEN_ADD_ADD;
        src.input++;
      } else if (*src.input == '=') {
        src.token = TOKEN_EQUAL_ADD;
        src.input++;
      } else {
        src.token = '+';
      }
      return;
    } else if (*src.input == '-') {
      src.input++;
      if (*src.input == '-') {
        src.token = TOKEN_MINUS_MINUS;
        src.input++;
      } else if (*src.input == '=') {
        src.token = TOKEN_EQUAL_MINUS;
        src.input++;
      } else {
        src.token = '-';
      }
      return;
    } else if (*src.input == '*') {
      src.input++;
      if (*src.input == '*') {
        src.token = TOKEN_POW;
        src.input++;
      } else if (*src.input == '=') {
        src.token = TOKEN_EQUAL_MUL;
        src.input++;
      } else {
        src.token = '*';
      }
      return;
    } else if (*src.input == '&') {
      src.input++;
      if (*src.input == '&') {
        src.token = TOKEN_LOG_AND;
        src.input++;
      } else if (*src.input == '=') {
        src.token = TOKEN_EQUAL_AND;
        src.input++;
      } else {
        src.token = '&';
      }
      return;
    } else if (*src.input == '|') {
      src.input++;
      if (*src.input == '|') {
        src.token = TOKEN_LOG_OR;
        src.input++;
      } else if (*src.input == '=') {
        src.token = TOKEN_EQUAL_OR;
        src.input++;
      } else {
        src.token = '|';
      }
      return;
    } else if (*src.input == '>') {
      src.input++;
      if (*src.input == '=') {
        src.token = TOKEN_REL_GE;
        src.input++;
      } else if (*src.input == '>') {
        src.input++;
        if (*src.input == '=') {
          src.token = TOKEN_EQUAL_SR;
          src.input++;
        } else {
          src.token = TOKEN_REL_SR;
        }
      } else {
        src.token = '>';
      }
      return;
    } else if (*src.input == '<') {
      src.input++;
      if (*src.input == '=') {
        src.token = TOKEN_REL_LE;
        src.input++;
      } else if (*src.input == '<') {
        src.input++;
        if (*src.input == '=') {
          src.token = TOKEN_EQUAL_SL;
          src.input++;
        } else {
          src.token = TOKEN_REL_SL;
        }
      } else {
        src.token = '<';
      }
      return;
    } else if (*src.input == '!') {
      src.input++;
      if (*src.input == '=') {
        src.token = TOKEN_REL_NE;
        src.input++;
      } else {
        src.token = '!';
      }
      return;
    }
    // printf("%c\n", *src.input++);
    src.input++;
  }
  if (*src.input == '\0') {
    src.token = TOKEN_EOF;
  }
}
