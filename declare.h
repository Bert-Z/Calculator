//declare.h这个头文件只存放一些全局变量（设定的类型）以及文法规则需要的函数声明
#ifndef DECLARE_H
#define DECLARE_H

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

#endif
