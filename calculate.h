//Calculate.h的文件中只包括计算的语法与函数，具体的界面在interface.cpp
#ifndef CALCULATE_H
#define CALCULATE_H

#include <iostream>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

const char number = '8';
const char print = ';';
const char quit = 'q';
const char prompt = '>';
const char result = '=';
double ansValue = 0;

//factorial
int factorial(int n);

//rule
double basic();
double primary();
double mid();
double term();
double expression();

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

//阶乘函数
int factorial(int n)
{
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

//文法规则
double basic()                                          //basic包括括号运算和数字读取
{
    Token t = ts.get();
    switch (t.kind)
    {
    case '(':
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')')
        {
            throw runtime_error("')'excepted");
        }

        return d;
    }
    case number:
        return t.value;
    default:
        throw runtime_error("basic expected");
    }
};

double primary()                                        //primary包括阶乘运算
{
    double left = basic();
    Token t = ts.get();
    if (t.kind == '!')
    {
        if (int(left) == left && left >= 0)
            return factorial(left);
        else
            throw runtime_error("error");
    }

    else
        ts.putback(t);
    return left;
}

double mid()                                            //mid包括正负号运算
{
    Token t = ts.get();
    switch (t.kind)
    {
    case '-':
        return -mid();
    case '+':
        return +mid();
    default:
        ts.putback(t);
        return primary();
    }
}

double term()                                           //term包括乘、除、取余运算
{
    double left = mid();
    Token t = ts.get();

    while (true)
    {
        switch (t.kind)
        {
        case '*':

            left *= mid();
            t = ts.get();
            break;

        case '/':
        {
            double d = mid();
            if (d == 0)
                throw runtime_error("divide by zero");
            // cerr << "divide by zero";
            left /= d;
            t = ts.get();
            break;
        }
        case '%':
        {
            double d = mid();
            int i1 = int(left);
            if (i1 != left)
                throw runtime_error("error");
            int i2 = int(d);
            if (i2 != d)
                throw runtime_error("error");
            if (d == 0)
                throw runtime_error("%:divided by zero");
            left = i1 % i2;
            t = ts.get();
            break;
        }

        default:
            ts.putback(t);
            return left;
        }
    }
};

double expression()                                                     //expression包括加减运算
{
    double left = term();
    Token t = ts.get();

    while (true)
    {
        switch (t.kind)
        {
        case '+':
            left += term();
            t = ts.get();
            break;
        case '-':
            left -= term();
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
};

void calculate()
{
    cout << prompt;             //输入时打印'>'
    Token t = ts.get();

    while (t.kind == print)     //读到';'输出结果
        t = ts.get();
    if (t.kind == quit)         //读到'q'退出程序
    {
        system("pause");
        exit(EXIT_SUCCESS);
    }
    ts.putback(t);
    double ans = expression();
    cout << result << ans << endl;      //输出结果

    ansValue = ans;                 //用 "ANS"记录上次输出的结果
}


#endif