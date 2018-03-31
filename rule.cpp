//rule.cpp这个文件用于存放有关文法的函数实现
#include "Token_stream.h"
#include "declare.h"
#include <stdexcept>

using namespace std;

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