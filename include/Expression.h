#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// Expression 类的声明
class Expression
{
protected:          // 保护成员，便于Function类继承使用
    bool isPostFix; // 是否是后缀表达式
    int varNum;     // 变量个数

public:
    unordered_map<string, double> varMap;   // 变量索引
    bool hasSub;                            // 是否有子表达式
    string expr;                            // 表达式字符串
    Expression();                           // 默认构造函数
    Expression(int x);                      // 构造函数，用于特殊情况，一般不调用
    Expression(const Expression &E);        // 拷贝构造函数
    bool hasVar();                          // 是否有变量
    ~Expression();                          // 析构函数
    double calculate();                     // 计算表达式的值
    void varAssign(string var, double val); // 变量赋值
    void infixToPostfix();                  // 将中缀表达式转换为后缀表达式
};

#endif

// Expression.h