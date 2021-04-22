#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define SKIP_CHAR \
  (char[]) { ' ', '\r', '\t' }
#define SUITABLE_CHAR \
  (char[]) { "abcdefghijklmnopqrstuvwxyz_0123456789" }
#define SUITABLE_DIGIT \
  (char[]) { "xb0123456789" }
#define EOL '\n'
#define HEX 'x'
#define BIN 'b'
#define STR '\"'
#define SHIELD '\\'

typedef enum {
  TOK_EOF = 0,
  TOK_NUMBER,
  TOK_HEXNUMBER,
  TOK_BINNUMBER,
  TOK_STRING,
  TOK_VARIABLE,
  TOK_OTHER = -2,
  TOK_ERROR = -3
} TokenType;

typedef enum {
  OP__START = 100,
  TOK_EOL,
  TOK_LT,
  TOK_GT,
  TOK_DOTS,
  TOK_SHL,
  TOK_A_SHL,
  TOK_SAR,
  TOK_A_SAR,
  TOK_SUM,
  TOK_INCR,
  TOK_A_SUM,
  TOK_DIFFERENCE,
  TOK_DECR,
  TOK_A_DIFFERENCE,
  TOK_PRODUCT,
  TOK_A_PRODUCT,
  TOK_QUOTIENT,
  TOK_A_QUOTIENT,
  TOK_REMINDER,
  TOK_A_REMINDER,
  TOK_B_NOT,
  TOK_A_B_NOT,
  TOK_B_AND,
  TOK_A_B_AND,
  TOK_B_OR,
  TOK_A_B_OR,
  TOK_B_XOR,
  TOK_A_B_XOR,
  TOK_L_NOT,
  TOK_L_AND,
  TOK_L_OR,
  TOK_L_XOR,
  TOK_OPEN_BRACKET,
  TOK_CLOSE_BRACKET,
  TOK_OPEN_FBRACKET,
  TOK_CLOSE_FBRACKET,
  TOK_OPEN_SBRACKET,
  TOK_CLOSE_SBRACKET,
  OP_COMMENT,
  OP__MAX
} OpNum;

#define opchar                               \
  (const char * [OP__MAX - OP__START - 1]) { \
    "\n",                                    \
        "<",                                 \
        ">",                                 \
        "...",                               \
        "<<",                                \
        "<<=",                               \
        ">>",                                \
        ">>=",                               \
        "+",                                 \
        "++",                                \
        "+=",                                \
        "-",                                 \
        "--",                                \
        "-=",                                \
        "*",                                 \
        "*=",                                \
        "/",                                 \
        "/=",                                \
        "%",                                 \
        "%=",                                \
        "~",                                 \
        "~=",                                \
        "&",                                 \
        "&=",                                \
        "|",                                 \
        "|=",                                \
        "^",                                 \
        "^=",                                \
        "!",                                 \
        "&&",                                \
        "||",                                \
        "!=",                                \
        "(",                                 \
        ")",                                 \
        "{",                                 \
        "}",                                 \
        "[",                                 \
        "]",                                 \
        "//"                                 \
  }

typedef enum {
  TOK__START = 200,
  TOK_INT,
  TOK_VOID,
  TOK_CHAR,
  TOK_IF,
  TOK_ELSE,
  TOK_WHILE,
  TOK_BREAK,
  TOK_RETURN,
  TOK_FOR,
  TOK_EXTERN,
  TOK_STATIC,
  TOK_UNSIGNED,
  TOK_GOTO,
  TOK_DO,
  TOK_CONTINUE,
  TOK_SWITCH,
  TOK_CASE,
  TOK_CONST1,
  TOK_CONST2,
  TOK_CONST3,
  TOK_VOLATILE1,
  TOK_VOLATILE2,
  TOK_VOLATILE3,
  TOK_LONG,
  TOK_REGISTER,
  TOK_SIGNED1,
  TOK_SIGNED2,
  TOK_SIGNED3,
  TOK_AUTO,
  TOK_INLINE1,
  TOK_INLINE2,
  TOK_INLINE3,
  TOK_RESTRICT1,
  TOK_RESTRICT2,
  TOK_RESTRICT3,
  TOK_EXTENSION,
  TOK_FLOAT,
  TOK_DOUBLE,
  TOK_BOOL,
  TOK_SHORT,
  TOK_STRUCT,
  TOK_UNION,
  TOK_TYPEDEF,
  TOK_DEFAULT,
  TOK_ENUM,
  TOK_SIZEOF,
  TOK_ATTRIBUTE1,
  TOK_ATTRIBUTE2,
  TOK_ALIGNOF1,
  TOK_ALIGNOF2,
  TOK_TYPEOF1,
  TOK_TYPEOF2,
  TOK_TYPEOF3,
  TOK_LABEL,
  TOK_DEFINE,
  TOK_INCLUDE,
  TOK_INCLUDE_NEXT,
  TOK_IFDEF,
  TOK_IFNDEF,
  TOK_ELIF,
  TOK_ENDIF,
  TOK_DEFINED,
  TOK_UNDEF,
  TOK_WARNING,
  TOK_LINE,
  TOK_PRAGMA,
  TOK___LINE__,
  TOK___FILE__,
  TOK___DATE__,
  TOK___TIME__,
  TOK___FUNCTION__,
  TOK___VA_ARGS__,
  TOK___FUNC__,
  TOK_SECTION1,
  TOK_SECTION2,
  TOK_ALIGNED1,
  TOK_ALIGNED2,
  TOK_PACKED1,
  TOK_PACKED2,
  TOK_UNUSED1,
  TOK_UNUSED2,
  TOK_CDECL1,
  TOK_CDECL2,
  TOK_CDECL3,
  TOK_STDCALL1,
  TOK_STDCALL2,
  TOK_STDCALL3,
  TOK_FASTCALL1,
  TOK_FASTCALL2,
  TOK_FASTCALL3,
  TOK_DLLEXPORT,
  TOK_NORETURN1,
  TOK_NORETURN2,
  TOK_builtin_types_compatible_p,
  TOK_builtin_constant_p,
  TOK_builtin_frame_address,
  TOK_builtin_malloc,
  TOK_builtin_free,
  TOK_malloc,
  TOK_free,
  TOK_REGPARM1,
  TOK_REGPARM2,
  TOK_pack,
  TOK_memcpy,
  TOK_memset,
  TOK___divdi3,
  TOK___moddi3,
  TOK___udivdi3,
  TOK___umoddi3,
  TOK_realloc,
  TOK_memalign,
  TOK_calloc,
  TOK_memmove,
  TOK_strlen,
  TOK_strcpy,
  TOK_alloca,
  TOK__MAX
} KeyWordsNum;

#define keywords                               \
  (const char * [TOK__MAX - TOK__START - 1]) { \
    "int",                                     \
        "void",                                \
        "char",                                \
        "if",                                  \
        "else",                                \
        "while",                               \
        "break",                               \
        "return",                              \
        "for",                                 \
        "extern",                              \
        "static",                              \
        "unsigned",                            \
        "goto",                                \
        "do",                                  \
        "continue",                            \
        "switch",                              \
        "case",                                \
        "const",                               \
        "__const",                             \
        "__const__",                           \
        "volatile",                            \
        "__volatile",                          \
        "__volatile__",                        \
        "long",                                \
        "register",                            \
        "signed",                              \
        "__signed",                            \
        "__signed__",                          \
        "auto",                                \
        "inline",                              \
        "__inline",                            \
        "__inline__",                          \
        "restrict",                            \
        "__restrict",                          \
        "__restrict__",                        \
        "__extension__",                       \
        "float",                               \
        "double",                              \
        "_Bool",                               \
        "short",                               \
        "struct",                              \
        "union",                               \
        "typedef",                             \
        "default",                             \
        "enum",                                \
        "sizeof",                              \
        "__attribute",                         \
        "__attribute__",                       \
        "__alignof",                           \
        "__alignof__",                         \
        "typeof",                              \
        "__typeof",                            \
        "__typeof__",                          \
        "__label__",                           \
        "define",                              \
        "include",                             \
        "include_next",                        \
        "ifdef",                               \
        "ifndef",                              \
        "elif",                                \
        "endif",                               \
        "defined",                             \
        "undef",                               \
        "warning",                             \
        "line",                                \
        "pragma",                              \
        "__LINE__",                            \
        "__FILE__",                            \
        "__DATE__",                            \
        "__TIME__",                            \
        "fn",                                  \
        "__VA_ARGS__",                         \
        "__func__",                            \
        "section",                             \
        "__section__",                         \
        "aligned",                             \
        "__aligned__",                         \
        "packed",                              \
        "__packed__",                          \
        "unused",                              \
        "__unused__",                          \
        "cdecl",                               \
        "__cdecl",                             \
        "__cdecl__",                           \
        "stdcall",                             \
        "__stdcall",                           \
        "__stdcall__",                         \
        "fastcall",                            \
        "__fastcall",                          \
        "__fastcall__",                        \
        "dllexport",                           \
        "noreturn",                            \
        "__noreturn__",                        \
        "__builtin_types_compatible_p",        \
        "__builtin_constant_p",                \
        "__builtin_frame_address",             \
        "__builtin_malloc",                    \
        "__builtin_free",                      \
        "malloc",                              \
        "free",                                \
        "regparm",                             \
        "__regparm__",                         \
        "pack",                                \
        "memcpy",                              \
        "memset",                              \
        "__divdi3",                            \
        "__moddi3",                            \
        "__udivdi3",                           \
        "__umoddi3",                           \
        "realloc",                             \
        "memalign",                            \
        "calloc",                              \
        "memmove",                             \
        "strlen",                              \
        "strcpy",                              \
        "alloca"                               \
  }

typedef struct {
  char *r;
  int token;
  int tokenSize;
} Tokenizer;

Tokenizer *NewTokenizer(char *data2parse);
int Token(Tokenizer *t);
char *Value(Tokenizer *t);
int Next(Tokenizer *t);
void skipcommentline(Tokenizer *t);
bool isstring(Tokenizer *t);
bool issuitable(Tokenizer *t);
bool isnumber(Tokenizer *t);
bool iskeyword(Tokenizer *t);
bool isoperation(Tokenizer *t);