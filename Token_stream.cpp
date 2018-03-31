//Token_stream.cpp这个文件用于存放有关Token_stream类的函数实现
#include "Token_stream.h"
#include "declare.h"
#include <iostream>

using namespace std;

//类比cin建立一个Token流用于正确读取数字和文件

Token_stream::Token_stream()
    : full(false), buffer(0) {}

void Token_stream::putback(Token t)
{
    buffer = t;
    full = true;
}

Token Token_stream::get()
{
    if (full)
    {
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;

    switch (ch)
    {
    case print: //cout something
    case quit:  //quit
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '%':
    case '/':
    case '!':
        return Token(ch);
    case '.':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        cin.putback(ch);
        double val;
        cin >> val;
        return Token(number, val);
    }
    case 'A':
    {
        cin.putback(ch);
        char a = cin.get();
        char n = cin.get();
        char s = cin.get();
        if (a == 'A' && n == 'N' && s == 'S')
        {
            return Token(number, ansValue);
        }
    }
    default:
        throw runtime_error("Bad token");
    }
}