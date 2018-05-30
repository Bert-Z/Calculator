/* 
 This is a calculator program
 Author: Bert_Z (张万强)
 Student code: 516072910091
*/

//这个main.cpp文件用于存放calculator功能函数和main函数的实现


#include "calculate.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

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