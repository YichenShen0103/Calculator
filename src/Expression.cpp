#include "Expression.h" // 包含本文件实现的函数的声明头文件
#include <cctype>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;

/*
 * @brief 计算操作符的优先级
 * @param char op 操作
 * @return int 优先级
 */
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1; // 加减法的优先级次低
    if (op == '*' || op == '/')
        return 2; // 乘除法的优先级最高
    return 0;     // 其他操作符的优先级最低
}

/*
 * @brief 将中缀表达式转换为后缀表达式
 * @return 函数无返回值
 */
void Expression::infixToPostfix()
{
    stack<char> operators; // 操作符栈
    string postfix;        // 存储后缀表达式的字符串

    for (int i = 0; i < expr.length(); i++)
    {
        char ch = expr[i];

        // 如果当前字符是一个数字或字母（操作数），直接添加到后缀表达式中
        if (isdigit(ch))
        {
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.'))
            {
                postfix += expr[i];
                i++;
            }
            postfix += ' '; // 加上空格，以区分数字和操作符
            i--;            // 回退一步，因为当前字符已经处理过了
        }
        else if (isalpha(ch) || ch == '_')
        {
            while (i < expr.length() && (isalpha(expr[i]) || isdigit(expr[i]) || expr[i] == '_'))
            {
                postfix += expr[i];
                i++;
            }
            postfix += ' '; // 加上空格，以区分字母和操作符
            i--;            // 回退一步，因为当前字符已经处理过了
        }
        else if (ch == '(')
        {
            operators.push(ch);
        }
        else if (ch == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                postfix += operators.top();
                postfix += ' '; // 加上空格，以区分操作符和操作数
                operators.pop();
            }
            operators.pop(); // 弹出左括号
        }
        else if (ch == '-')
        {
            if (i == 0 || expr[i - 1] == '(' || expr[i - 1] == ' ' || precedence(expr[i - 1]) < 0)
            {
                postfix += '0'; // 在负号前添加 0
                postfix += ' '; // 添加空格以分隔
            }

            while (!operators.empty() && precedence(operators.top()) >= precedence(ch))
            {
                postfix += operators.top();
                postfix += ' '; // 加上空格，以区分操作符和操作数
                operators.pop();
            }
            operators.push(ch); // 将负号压入栈
        }
        else
        {
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch))
            {
                postfix += operators.top();
                postfix += ' '; // 加上空格，以区分操作符和操作数
                operators.pop();
            }
            operators.push(ch); // 将当前操作符压入栈
        }
    }

    // 处理完所有字符后，将操作符栈中剩余的操作符弹出
    while (!operators.empty())
    {
        postfix += operators.top();
        postfix += ' ';
        operators.pop();
    }

    expr = postfix;
    isPostFix = true;
}

/*
 * @brief 构造函数，初始化表达式
 * @return 函数无返回值
 */
Expression::Expression()
{
    cout << "Please input a expression (donnot include <Space>): ";
    cin >> expr;
    set<string> variables; // 用于存储变量
    for (int i = 0; i < expr.length(); i++)
    {
        char ch = expr[i];
        if (isalpha(ch))
        {
            string var = "";
            while (i < expr.length() && (isalpha(expr[i]) || isdigit(expr[i]) || expr[i] == '_'))
            {
                var += expr[i];
                i++;
            }
            variables.insert(var); // 统计变量
            i--;                   // 回退一步，因为当前字符已经处理过了
        }
    }
    varList = vector<string>(variables.begin(), variables.end()); // 变量列表
    varNum = variables.size();                                    // 变量个数
    isPostFix = false;                                            // 表达式是否为后缀表达式
    varVal = vector<double>(varNum, NAN);                         // 变量值初始化为 NAN
}

/*
 * @brief 析构函数，释放内存
 * @return 函数无返回值
 */
Expression::~Expression() {}

/*
 * @brief 计算表达式的值
 * @return double 表达式的值
 */
double Expression::calculate()
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
            while (i < expr.size() && (isalpha(expr[i]) || isdigit(expr[i]) || expr[i] == '_'))
            {
                var += expr[i];
                i++;
            }
            i--; // 回退一步，因为当前字符已经处理过了

            for (int j = 0; j < varNum; j++)
            {
                if (var == varList[j])
                {
                    index = j; // 找到变量索引
                    break;
                }
            }
            if (index == -1 || isnan(varVal[index]))
            {
                cout << "Error: Undefined or unassigned variable" << endl; // 变量未定义或未赋值
                return NAN;
            }
            sta[top++] = varVal[index];
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
        cout << "Error: Invalid expression" << endl; // 表达式格式错误
        return NAN;
    }
}

/*
 * @brief 变量赋值
 * @param char var 变量名
 *        double val 变量值
 * @return 函数无返回值
 */
void Expression::varAssign(string var, double val)
{
    for (int i = 0; i < varNum; i++)
    {
        if (var == varList[i])
        {
            varVal[i] = val; // 找到变量，赋值
            return;
        }
    }
    cout << "Error: Undefined variable" << endl; // 变量未定义
}

/*
 * @brief 变量是否存在
 * @return bool 变量是否存在
 */
bool Expression::hasVar()
{
    return varNum > 0; // 变量个数大于 0 则存在变量
}

/*
 * @brief 拷贝构造函数
 * @param const Expression &E 复制的对象
 * @return 函数无返回值
 */
Expression::Expression(const Expression &E)
{
    // 拷贝表达式
    expr = E.expr;
    isPostFix = E.isPostFix;
    varNum = E.varNum;
    varList = E.varList;
    varVal = E.varVal;
}

/*
 * @brief 构造函数的重载，专门用于特殊情况，不主动调用
 * @param int x 无意义参数
 * @return 函数无返回值
 */
Expression::Expression(int x) {}

// Expression.cpp