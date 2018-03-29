// This is a calculator program
// Built by Bert_Z

#include <iostream>
#include <stdlib.h>

using namespace std;

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
    case ';': //cout something
    case 'q': //quit
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
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
        return Token('8', val);
    }
    default:
        cerr << "Bad token";
        exit(EXIT_FAILURE);
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
            cerr << "')'expected";
            exit(EXIT_FAILURE);
        }

        return d;
    }

    case '8':
        return t.value;
    default:
        cerr << "primary expected";
        exit(EXIT_FAILURE);
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
                cerr << "divide by zero";
            left /= d;
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

//main loop
int main()
{
    try
    {
        double val;

        while (cin)
        {
            Token t = ts.get();

            if (t.kind == 'q')
                break;
            if (t.kind == ';')
                cout << "=" << val << endl;
            else
                ts.putback(t);
            val = expression();
        }
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "exception\n";
        return 2;
    }
}