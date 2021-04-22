#include "lexer.h"
#include "parser.h"

bool is_the_token_usable(sToken *stok, int status){
  bool ret = false;
  int extra_token_data =*((int*)stok->data);
  switch(status){
      case ST_EMPTY:{
          ret = true;
          break;
      }
      case ST_TYPE_SPECIFED:{
          ACCEPT(TOK_DATA_NAME);
          ACCEPT(TOK_OP_MUL);
          break;
      }
      case ST_ASTERISK_DECLARED_FOR_TYPE:{
          ACCEPT(TOK_DATA_NAME);
          break;
      }
      case ST_NAME_DECLARED:{
          ACCEPT(TOK_VIRGOL);
          ACCEPT(TOK_OP_DEFINE);
          break;
      }
      case ST_NEXT_VIRGOL_EOL_DEFINE:{
          ACCEPT(TOK_VIRGOL);
          ACCEPT(TOK_OP_DEFINE);
          break;
      }
      case ST_NEXT_NAME:{
          ACCEPT(TOK_DATA_NAME);
          break;
      }
      case ST_WAIT_EXPRESION:{
          ACCEPT(TOK_DATA_INTEGER);
          break;
      }
      case ST_EXPRESION:{
          ACCEPT(TOK_DATA_INTEGER);
          break;
      }
      default:{
          break;
      }
  }
  //extra token
  if(stok->token == TOK_EOL){
    ret = true;
  }
  if((extra_token_data == TOK_SHIELD) || \
     (extra_token_data == TOK_START_BLOCK_COMMENT) || \
     (extra_token_data == TOK_END_BLOCK_COMMENT) || \
     (extra_token_data == TOK_LINE_COMMENT)){
    ret = true;
  }
  return ret;  
}