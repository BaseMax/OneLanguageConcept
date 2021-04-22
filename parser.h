typedef struct _Node {
	void *value;
	struct _Node *next;
	struct _Node *prev;	
} Node;

void new_token(int);
void parser_init(void);
void parser_done(void);
void push(int);
void pop(void);
int getvalue(int);
int depth(void);