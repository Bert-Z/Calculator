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

//calculator function
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

//main 
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
            cerr << e.what() << endl;       //输出错误
        }
        catch (...)
        {
            cerr << "exception\n";          
        }
    }

    return 0;
}