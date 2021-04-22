typedef struct _Node {
	void *value;
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
void push(int);
void pop(void);
int getvalue(int);
int depth(void);