/* 
 This is a calculator program
 Author: Bert_Z (张万强)
 Student code: 516072910091
*/

//这个main.cpp文件用于存放calculator功能函数和main函数的实现

#include "Token_stream.h"
#include "declare.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

//class

//Token_stream function

//early declaration

//rule

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
    double ans = expression();
    cout << result << ans << endl;
    ansValue = ans;
}

//main loop
int main()
{

    while (cin)
    {
        try
        {
            calculate();
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