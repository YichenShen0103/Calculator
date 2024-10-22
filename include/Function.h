#ifndef FUNCTION_H
#define FUNCTION_H

#include "Expression.h"

class Function : public Expression // 继承Expression类
{
private:
    string nonPostFixExpr; // 非后缀表达式

public:
    string name;                 // 函数名
    Function();                  // 构造函数
    double calculate();          // 计算表达式的值
    Function(const Function &E); // 拷贝构造函数
    ~Function();                 // 析构函数
    void calAndShowValue();      // 计算函数值
    void showFunction();         // 显示函数表达式
};

#endif

// FUNCTION_H