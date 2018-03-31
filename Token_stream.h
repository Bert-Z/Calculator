//Token_stream.h这个头文件只存放有关Token_stream类的定义说明
#ifndef TOKEN_STREAM_H_INCLUDED
#define TOKEN_STREAM_H_INCLUDED

#include "Token.h"

class Token_stream
{
  public:
    Token_stream();
    Token get();
    void putback(Token t);

  private:
    bool full;
    Token buffer;
};

Token_stream ts;

#endif
