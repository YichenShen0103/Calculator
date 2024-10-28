#include "Function.h" // 包含本文件实现的函数声明位置所在的头文件
#include <iostream>
#include <unordered_map>
#include <cmath>
using namespace std;
extern unordered_map<string, Function *> functions; // 定义一个变量哈希表

/*
 * @brief 构造函数，调用父类的构造函数，并要求用户输入函数名
 * @return 构造函数无返回值
 */
Function::Function() : Expression()
{
    cout << "Please name your function: ";
    cin >> name;           // 要求用户输入函数名
    nonPostFixExpr = expr; // 保存原始表达式，用于后续输出
}

/*
 * @brief 拷贝构造函数，调用父类的拷贝构造函数
 * @param other 要拷贝的对象
 * @return 拷贝构造函数无返回值
 */
Function::Function(const Function &other) : Expression(other)
{
    name = other.name;
    nonPostFixExpr = other.nonPostFixExpr;
}

/*
 * @brief 析构函数
 * @return 析构函数无返回值
 */
Function::~Function() {}

/*
 * @brief 计算函数值并输出
 * @return 函数无返回值
 */
void Function::calAndShowValue()
{
    for (const auto &pair : varMap)
    {
        cout << "Please input the value of " << pair.first << ": ";
        cin >> varMap[pair.first]; // 要求用户输入变量值
    }
    cout << name << "(";
    for (const auto &pair : varMap)
    { // 格式化输出
        cout << varMap[pair.first] << ", ";
    }
    cout << "\b\b  \b\b) = ";
    cout << calculate() << endl;
}

/*
 * @brief 格式化输出函数
 * @return 函数无返回值
 */
void Function::showFunction()
{
    cout << name << "(";
    for (const auto &pair : varMap)
    { // 格式化输出
        cout << pair.first << ", ";
    }
    cout << "\b\b  \b\b) = " << nonPostFixExpr << endl;
    // Test
    this->infixToPostfix();
    cout << expr << endl;
}

double Function::calculate()
{
    if (!isPostFix)
        infixToPostfix();

    vector<double> sta(expr.size());
    int top = 0;

    for (int i = 0; i < expr.size(); ++i)
    {
        if (isspace(expr[i]))
            continue; // 跳过空格
        if (isdigit(expr[i]))
        {
            double num = 0;
            while (i < expr.size() && (isdigit(expr[i]) || expr[i] == '.'))
            {
                if (expr[i] == '.') // 处理小数点
                {
                    double fraction = 0.1;
                    i++;
                    while (i < expr.size() && isdigit(expr[i]))
                    {
                        num += (expr[i] - '0') * fraction; // 累加小数部分
                        fraction *= 0.1;
                        i++;
                    }
                    break; // 小数部分处理完毕
                }
                else
                {
                    num = num * 10 + (expr[i] - '0'); // 累加整数部分
                }
                i++;
            }
            sta[top++] = num; // 入栈
            i--;              // 回退一步
        }
        else if (isalpha(expr[i]))
        {
            int index = -1; // 变量索引
            string var = "";
            while (i < expr.size() && (isalpha(expr[i]) || isdigit(expr[i]) || expr[i] == '_' ||
                                       expr[i] == '(' || expr[i] == ')'))
            {
                if (expr[i] == '(') // 处理函数调用
                {
                    int level = 0;
                    string subName = var;
                    Function *subFunc = functions[subName];
                    var = "";
                    string exp = "";
                    i++;
                    vector<double> params(0);
                    while (i < expr.size() && expr[i] != ')' && !level)
                    {
                        if (expr[i] == '(')
                            level++;
                        else if (expr[i] == ')')
                            level--;
                        else if (expr[i] == ',')
                        {
                            params.push_back(Function(exp, varMap).calculate()); // 递归计算函数值
                            exp = "";
                            i++;
                            continue;
                        }
                        else if (isspace(expr[i]))
                        {
                            i++;
                            continue;
                        }
                        exp += expr[i];
                        i++;
                    }
                    params.push_back(Function(exp, varMap).calculate()); // 递归计算函数值
                    int p = 0;
                    for (const auto &pair : subFunc->varMap)
                    {
                        subFunc->varMap[pair.first] = params[p++];
                    }
                    sta[top++] = subFunc->calculate(); // 入栈
                    i++;
                    break; // 函数调用处理完毕
                }
                var += expr[i];
                i++;
            }
            i--; // 回退一步，因为当前字符已经处理过了

            if (var != "")
                sta[top++] = varMap[var];
        }
        else if (expr[i] == '-') // 处理负号
        {
            if (top == 0) // 如果栈为空，视为负数
            {
                i++;
                double num = 0;
                while (i < expr.size() && isdigit(expr[i]))
                {
                    num = num * 10 + (expr[i] - '0');
                    i++;
                }
                sta[top++] = -num; // 将负数入栈
                i--;               // 回退一步
            }
            else // 二元操作符
            {
                double op2 = sta[--top];
                double op1 = sta[--top];
                sta[top++] = op1 - op2; // 处理二元操作符
            }
        }
        else
        {
            // 处理二元操作符
            double op2 = sta[--top];
            double op1 = sta[--top];
            switch (expr[i])
            {
            case '+':
                sta[top++] = op1 + op2;
                break;
            case '-':
                sta[top++] = op1 - op2;
                break;
            case '*':
                sta[top++] = op1 * op2;
                break;
            case '/':
                if (op2 == 0)
                {
                    cout << "Error: Division by zero" << endl; // 除数为 0
                    return NAN;
                }
                sta[top++] = op1 / op2;
                break;
            case '^':
                sta[top++] = pow(op1, op2);
                break;
            default:
                cout << "Error: Invalid operator" << endl; // 非法操作符
                return NAN;
            }
        }
    }

    if (top == 1)
    {
        return sta[0]; // 正常返回结果
    }
    else
    {
        cout << endl;
        cout << "Error: Invalid expression" << endl; // 表达式格式错误
        for (int i = 0; i < sta.size(); ++i)
        {
            cout << sta[i] << " ";
        }
        return NAN;
    }
}

Function::Function(string exp, unordered_map<string, double> varMap) : Expression(exp)
{
    name = "";
    nonPostFixExpr = exp;
    for (const auto &pair : varMap)
    {
        this->varMap[pair.first] = pair.second;
    }
}

// Function.cpp