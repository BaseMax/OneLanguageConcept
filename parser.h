#include <stdarg.h>

typedef struct _Node {
	int value;
    int token_type;
    int stack_pos;
    int status;
    void *data;
	struct _Node *next;
	struct _Node *prev;	
} Node;

typedef struct _Token {
	int token;
	void *data;
} sToken;


int new_token(sToken*);
void parser_init(void);
void parser_done(void);
void push(sToken*);
void pop(void);
int getvalue(int);
int gettoken(int);
void *getdata(int);
int depth(void);
void* token_strcopy(char*);
bool is_the_token_usable(sToken*, int);

bool _check_stack(int count, ...);
#define COUNT(...) _COUNT(__VA_ARGS__,20, 19, 18, 17, 16, 15, \
                                      14, 13, 12, 11, 10, 9,\
                                       8,  7,  6,  5,  4, 3, 2, 1)
#define _COUNT(a, b, c, d, e, f, g, h, i, j, k, l, m, o, p, r, s, t, u, v, count, ...) count
#define check_stack(...) _check_stack(COUNT(__VA_ARGS__), __VA_ARGS__)

/*
 * the following types of tokens are declared
 * 
    stok->token = TOK_DATA_STRING
    stok->data = char* string

    stok->token = TOK_EOL
    stok->data = int* TOK_EOL

    stok->token = TOK_DATA_CONTROL
    stok->data = int* token ( onetok.h && CONTROL_CHAR )
     
    stok->token = TOK_DATA_INTEGER
    stok->data = char* Decimal, Hex, Bin
    
    stok->token = TOK_DATA_FLOAT;
    stok->data = char* Float: normal, normalized 
  
    stok->token = TOK_DATA_OPERATION | TOK_DATA_VARAIBLE_TYPE | TOK_DATA_KEYWORD
    stok->data = int* token (onetok.h)

    stok->token = TOK_DATA_NAME
    stok->data = char* user-defined name
  
*/


typedef enum {
  ST_EMPTY = 8192,
  ST_TYPE_SPECIFED,
  ST_ASTERISK_DECLARED_FOR_TYPE,
  ST_NAME_DECLARED,
  ST_NEXT_NAME,
  ST_NEXT_VIRGOL_EOL_DEFINE,
  ST_WAIT_EXPRESION,
  ST_EXPRESION
  
} Status;

#define ACCEPT(x) \
if(x>TOK_END_KEYWORD){\
  if(stok->token == x){\
    ret = true;\
    break;\
  }\
}else{\
 if(extra_token_data == x){\
    ret = true;\
    break;\
  }\
}


#define CH_STATUS(x,y) \
if(status == x){\
  push(stok);\
  status = y;\
  break;\
}
