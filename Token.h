//Token.h这个头文件只存放有关Token类的定义说明
#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

//建立一个Token类型用于数据正确的读取储存
class Token
{
  public:
    char kind;
    double value;
    Token(char ch)
        : kind(ch), value(0) {}
    Token(char ch, double val)
        : kind(ch), value(val) {}
};

#endif
