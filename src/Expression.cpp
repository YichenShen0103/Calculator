#include "Expression.h" // 包含本文件实现的函数的声明头文件
#include <cctype>
#include <queue>
#include <memory>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;

/*
 * @brief 判断表达式中的e是否为科学计数法的一部分
 * @param string expr 表达式字符串
 * @param int index e所在的位置
 * @return bool 是否为科学计数法的一部分
 */
bool isScitificNotation(string expr, int index)
{
    if (expr[index] != 'e')
        return false; // e 不是科学计数法的一部分

    if (index == 0)
        return true; // 表达式开头，则不是科学计数法的一部分

    index--;
    while (index >= 0)
    {
        char ch = expr[index];
        if (ch == '.' || ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^' || ch == '(' || ch == ')')
            return true; // 遇到操作符或括号，则是科学计数法的一部分
        if (isalpha(ch))
            return false; // 遇到字母，则不是科学计数法的一部分
        index--;
    }
    return true; // 遍历到表达式开头均为数字，则是科学计数法的一部分
}

/*
 * @brief 计算操作符的优先级
 * @param char op 操作
 * @return int 优先级
 */
int precedence(char op)
{
    if (op == '^')
        return 3; // 幂运算的优先级最高
    if (op == '+' || op == '-')
        return 1; // 加减法的优先级次低
    if (op == '*' || op == '/')
        return 2; // 乘除法的优先级次高
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
            bool hasE = false;       // 指示是否有 e
            bool singleMinus = true; // 指示是否只有一个 e
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.' || (expr[i] == '-' && hasE && singleMinus) || (expr[i] == 'e' && !hasE)))
            {
                if (expr[i] == '-')
                    singleMinus = false;
                if (expr[i] == 'e')
                    hasE = true;
                postfix += expr[i];
                i++;
            }
            postfix += ' '; // 加上空格，以区分数字和操作符
            i--;            // 回退一步，因为当前字符已经处理过了
        }
        else if (isalpha(ch) || ch == '_')
        {
            while (i < expr.length() && (isalpha(expr[i]) || isdigit(expr[i]) || expr[i] == '_' ||
                                         expr[i] == '('))
            {
                if (expr[i] == '(')
                {
                    postfix += expr[i];
                    i++;
                    int level = 0;
                    while (i < expr.length() && expr[i] != ')' && !level)
                    {
                        if (expr[i] == '(')
                            level++;
                        else if (expr[i] == ')')
                            level--;
                        postfix += expr[i];
                        i++;
                    }
                }
                postfix += expr[i];
                i++;
            }
            postfix += ' '; // 加上空格，以区分字母和操作符
            --i;            // 回退一步，因为当前字符已经处理过了
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
            if (ch == 'e' && isScitificNotation(expr, i)) // 处理 e
                continue;                                 // 科学计数法跳过

            string var = "";
            while (i < expr.length() && (isalpha(expr[i]) || isdigit(expr[i]) || expr[i] == '_' ||
                                         expr[i] == '(' || expr[i] == ')'))
            {
                if (expr[i] == '(')
                {
                    var = "";
                    int level = 0;
                    string sub = "";
                    ++i;
                    while (i < expr.length() && expr[i] != ')' && !level)
                    {
                        if (expr[i] == '(')
                            level++;
                        else if (expr[i] == ')')
                            level--;
                        sub += expr[i];
                        i++;
                    }
                    Expression subExpr(sub);
                    for (auto var : subExpr.varMap)
                    {
                        variables.insert(var.first); // 统计变量
                    }
                    i++;
                    continue;
                }
                if (expr[i] != ')')
                    var += expr[i];
                i++;
            }
            if (var != "")
            {
                variables.insert(var); // 统计变量
                i--;                   // 回退一步，因为当前字符已经处理过了
            }
        }
    }
    for (auto var : variables)
    {
        varMap[var] = NAN; // 变量值初始化为 NAN
    }
    varNum = variables.size(); // 变量个数
    isPostFix = false;         // 表达式是否为后缀表达式
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
            if (expr[i] == 'e') // 处理指数
            {
                i++;
                int exp = 0;
                int sign = 1;
                if (i < expr.size() && expr[i] == '-')
                {
                    sign = -1;
                    i++;
                }
                while (i < expr.size() && isdigit(expr[i]))
                {
                    exp = exp * 10 + (expr[i] - '0');
                    i++;
                }
                num *= pow(10, exp * sign); // 乘以 10 的指数次方
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
    varMap[var] = val; // 变量赋值
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
    varMap = E.varMap;
}

/*
 * @brief 构造函数的重载，专门用于特殊情况，不主动调用
 * @param int x 无意义参数
 * @return 函数无返回值
 */
Expression::Expression(int x) {}

/*
 * @brief 构造函数的重载，不依赖用户输入
 * @param string s 表达式字符串
 */
Expression::Expression(string s)
{
    expr = s;
    set<string> variables; // 用于存储变量
    for (int i = 0; i < expr.length(); i++)
    {
        char ch = expr[i];
        if (isalpha(ch))
        {
            if (ch == 'e' && isScitificNotation(expr, i)) // 处理 e
                continue;                                 // 科学计数法跳过

            string var = "";
            while (i < expr.length() && (isalpha(expr[i]) || isdigit(expr[i]) || expr[i] == '_' ||
                                         expr[i] == '(' || expr[i] == ')'))
            {
                if (expr[i] == '(')
                {
                    var = "";
                    ++i;
                    int level = 0;
                    string sub = "";
                    while (i < expr.length() && expr[i] != ')' && !level)
                    {
                        if (expr[i] == '(')
                            level++;
                        else if (expr[i] == ')')
                            level--;
                        sub += expr[i];
                        i++;
                    }
                    Expression subExpr(sub);
                    for (auto var : subExpr.varMap)
                    {
                        variables.insert(var.first); // 统计变量
                    }
                    i++;
                    continue;
                }
                if (expr[i] != ')')
                    var += expr[i];
                i++;
            }
            if (var != "")
                variables.insert(var); // 统计变量
            i--;                       // 回退一步，因为当前字符已经处理过了
        }
    }
    for (auto it = variables.rbegin(); it != variables.rend(); ++it)
    {
        varMap[*it] = NAN; // 变量值初始化为 NAN
    }
    varNum = variables.size(); // 变量个数
    isPostFix = false;         // 表达式是否为后缀表达式
}

/*
 * @brief 树结点的构造函数
 * @param string value 结点的值
 * @return 构造函数无返回值
 */
Tree::Tree(string value) : val(value), left(nullptr), right(nullptr) {}

/*
 * @brief 表达式是否为后缀表达式
 * @return bool 是否为后缀表达式
 */
bool Expression::isPost()
{
    return isPostFix;
}

/*
 * @brief 根据逆波兰表达式构建表达式树
 * @return shared_ptr<Tree> 表达式树的根节点
 */
shared_ptr<Tree> Expression::buildExpressionTree()
{
    stack<shared_ptr<Tree>> st;
    if (!isPost())
        infixToPostfix();
    int i = 0;
    string token = "";
    while (i < expr.length())
    {
        token = "";
        while (!isspace(expr[i]) && i < expr.length())
        {
            token += expr[i];
            i++;
        }
        i++;
        if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^")
        {
            // 运算符 -> 弹出两个操作数并构建子树
            auto right = st.top();
            st.pop();
            auto left = st.top();
            st.pop();
            auto node = make_shared<Tree>(token);
            node->left = left;
            node->right = right;
            st.push(node);
        }
        else
        {
            // 操作数 -> 创建新节点并入栈
            st.push(make_shared<Tree>(token));
        }
    }
    return st.top();
}

/*
 * @brief 返回树的深度
 * @param shared_ptr<Tree> node 树根节点
 * @return int 树的深度
 */
int getTreeDepth(shared_ptr<Tree> node)
{
    if (!node)
        return 0;
    return max(getTreeDepth(node->left), getTreeDepth(node->right)) + 1;
}

/*
 * @brief 格式化输出树
 * @return 函数无返回值
 */
void Tree::prettyPrintTree()
{
    shared_ptr<Tree> root(this, [](Tree *) {});
    if (!this)
    {
        cout << "Empty tree" << endl;
        return;
    }

    // 获取树的深度
    int depth = getTreeDepth(root);

    deque<pair<shared_ptr<Tree>, int>> queue;
    queue.push_back({root, 0}); // 加入根节点
    int currentLevel = 0;
    string result;
    int maxWidth = pow(2, depth) - 1; // 树的最大宽度
    Tree emptyTree(" ");
    shared_ptr<Tree> nullTree = make_shared<Tree>(emptyTree);
    // 层次遍历
    while (!queue.empty())
    {
        deque<shared_ptr<Tree>> levelNodes;
        while (!queue.empty() && queue.front().second == currentLevel)
        {
            shared_ptr<Tree> node = queue.front().first;
            queue.pop_front();
            levelNodes.push_back(node);
        }

        // 计算当前层的间距
        int space = maxWidth / (pow(2, currentLevel + 1));
        for (int i = 0; i < space; i++)
        {
            result += " ";
        }

        // 打印当前层的所有节点
        for (auto &node : levelNodes)
        {
            result += node ? node->val : " ";
            for (int i = 0; i < space * 2 + 1; i++)
            {
                result += " ";
            }
            if (node)
            {
                if (node->left)
                    queue.push_back({node->left, currentLevel + 1});
                else if (currentLevel + 1 < depth)
                    queue.push_back({nullTree, currentLevel + 1});
                if (node->right)
                    queue.push_back({node->right, currentLevel + 1});
                else if (currentLevel + 1 < depth)
                    queue.push_back({nullTree, currentLevel + 1});
            }
        }

        result += "\n";
        currentLevel++;
    }

    cout << result;
}

// Expression.cpp