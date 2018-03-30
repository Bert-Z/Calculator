// This is a calculator program
// Built by Bert_Z

#include <exception>
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <string>

using namespace std;

const char number = '8';
const char print = ';';
const char quit = 'q';
const string prompt = ">";
const string result = "=";

//class
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

//Token_stream function
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
    default:
        throw runtime_error("Bad token");
        // cerr << "Bad token";
        // system("pause");
        // exit(EXIT_FAILURE);
    }
}

//early declaration
Token_stream ts;
double expression();

//rule
double primary()
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
            // cerr << "')'expected";
            // system("pause");
            // exit(EXIT_FAILURE);
        }

        return d;
    }
    case '-':
        return -primary();
    case '+':
        return +primary();
    case number:
        return t.value;
    default:
        throw runtime_error("primary expected");
        // cerr << "primary expected";
        // system("pause");
        // exit(EXIT_FAILURE);
    }
};

double term()
{
    double left = primary();
    Token t = ts.get();

    while (true)
    {
        switch (t.kind)
        {
        case '*':

            left *= primary();
            t = ts.get();
            break;

        case '/':
        {
            double d = primary();
            if (d == 0)
                throw runtime_error("divide by zero");
            // cerr << "divide by zero";
            left /= d;
            t = ts.get();
            break;
        }
        case '%':
        {
            double d = primary();
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

double expression()
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
    cout << prompt;
    Token t = ts.get();

    while (t.kind == print)
        t = ts.get();
    if (t.kind == quit)
    {
        system("pause");
        exit(EXIT_SUCCESS);
    }
    ts.putback(t);
    cout << result << expression() << endl;
}

//main loop
int main()
{

    while (cin)
    {
        try
        {
            calculate();
            // if (t.kind == 'q')
            //     break;
            // if (t.kind == ';')
            //     cout << "=" << val << endl;
            // else
            //     ts.putback(t);
            // val = expression();
        }
        catch (exception &e)
        {
            cerr << e.what() << endl;
        }
        catch (...)
        {
            cerr << "exception\n";
        }
    }

    return 0;
}