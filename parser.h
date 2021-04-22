typedef struct _Node {
	int value;
    int token_type;
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
int depth(void);
void* token_strcopy(char*);

/*
 * the following types of tokens are declared
 * 
    stok->token = TOK_DATA_STRING
    stok->data = char* string

    stok->token = TOK_EOL
    stok->data = int* 0

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