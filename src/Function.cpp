#include "Function.h" // 包含本文件实现的函数声明位置所在的头文件
#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <ctime>
#include <queue>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cmath>
using namespace std;
extern unordered_map<string, Function *> functions; // 定义一个变量哈希表
extern bool change_since_save;

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
}

/*
 * @brief 重写基类的计算函数
 * @return double 计算结果
 */
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

/*
 * @brief 根据变量表和串创造函数，用于类内调用，外部一般不调用
 * @return 构造函数无返回值
 */
Function::Function(string exp, unordered_map<string, double> varMap) : Expression(exp)
{
    name = "";
    nonPostFixExpr = exp;
    for (const auto &pair : varMap)
    {
        this->varMap[pair.first] = pair.second;
    }
}

/*
 * @brief 生成一棵函数调用树、
 * @return shared_ptr<Tree> 调用书的根节点
 */
shared_ptr<Tree> Function::buildFuncTree()
{
    if (!isPostFix)
        infixToPostfix();
    shared_ptr<Tree> root = make_shared<Tree>(name);
    unordered_map<string, int> fun;

    int i = 0;
    string sub = "";
    while (i < expr.length())
    {
        sub = "";
        while (!isspace(expr[i]) && i < expr.length())
        {
            sub += expr[i];
            i++;
        }
        i++;
        if (isalpha(sub[0]))
        {
            int j = 0;
            bool flag = false;
            string subname = "";
            while (j < sub.length() && isalpha(sub[j]) || isdigit(sub[j]) || sub[j] == '_' || sub[j] == '(' || sub[j] == ')' || sub[j] == ',')
            {
                if (sub[j] == '(')
                    flag = true;
                if (j != '(' && !flag)
                    subname += sub[j];
                j++;
            }
            if (j == sub.length() && flag)
            {
                if (functions.find(subname) != functions.end())
                {
                    if (fun.find(subname) != fun.end()) // 如果已经标记为访问过，则是递归调用
                    {
                        cout << "Error: Recursive function calls are not allowed." << endl;
                        return nullptr;
                    }

                    fun[subname] = 1;                                         // 标记为已访问
                    shared_ptr<Tree> t = functions[subname]->buildFuncTree(); // 递归调用

                    if (t == nullptr) // 如果子树构造失败，直接返回错误
                        return nullptr;

                    // 添加子树到当前节点
                    if (root->left == nullptr)
                        root->left = t;
                    else if (root->right == nullptr)
                        root->right = t;
                    else
                        cout << "Error: Subfunctions are not allowed to have more than two" << endl;

                    fun.erase(subname); // 清除标记，允许其它非递归路径继续访问
                }
                else
                {
                    cout << "Error: Undefined function " << subname << endl;
                    return nullptr;
                }
            }
        }
    }
    return root;
}

Edge::Edge(string v, string w, int we) : v(v), w(w), weight(we) {}

string Edge::start()
{
    return v;
}

string Edge::end()
{
    return w;
}

Digraph::Digraph() : V(0), E(0)
{
    adj = unordered_map<string, vector<Edge>>();
    inFunc = unordered_map<string, vector<pair<string, int>>>();
    outDegree = unordered_map<string, int>();
}

int Digraph::getV() const
{
    return V;
}

int Digraph::getE() const
{
    return E;
}

void Digraph::addEdge(Edge &e)
{
    string v = e.start();
    outDegree[v]++;
    if (e.weight == -1)
    {
        cout << "Please input the weight of the edge ( " << v << " -> " << e.end() << " ): ";
        cin >> e.weight;
    }
    inFunc[e.end()].push_back(pair<string, int>(v, e.weight));
    adj[v].push_back(e);
    E++;
}

vector<Edge> Digraph::adjList(string v)
{
    return adj[v];
}

vector<Edge> Digraph::edges()
{
    vector<Edge> allEdges;
    for (auto pair : adj)
    {
        string v = pair.first;
        for (Edge &e : adj[v])
        {
            if (find(allEdges.begin(), allEdges.end(), e) == allEdges.end())
            {
                allEdges.push_back(e);
            }
        }
    }
    return allEdges;
}

Digraph *buildFuncGraph()
{
    Digraph *G = new Digraph();
    for (auto pair : functions)
    {
        string v = pair.first;
        G->addVertex(v);
    }
    for (auto pair : functions)
    {
        string v = pair.first;
        Function *f = pair.second;
        if (!f->isPostFix)
            f->infixToPostfix();

        int i = 0;
        string sub = "";
        while (i < f->expr.length())
        {
            sub = "";
            while (!isspace(f->expr[i]) && i < f->expr.length())
            {
                sub += f->expr[i];
                i++;
            }
            i++;
            if (isalpha(sub[0]))
            {
                int j = 0;
                bool flag = false;
                string subname = "";
                while (j < sub.length() && isalpha(sub[j]) || isdigit(sub[j]) || sub[j] == '_' || sub[j] == '(' || sub[j] == ')' || sub[j] == ',')
                {
                    if (sub[j] == '(')
                        flag = true;
                    if (j != '(' && !flag)
                        subname += sub[j];
                    j++;
                }
                if (j == sub.length() && flag)
                {
                    if (functions.find(subname) != functions.end())
                    {
                        Edge e(v, subname, -1);
                        G->addEdge(e);
                    }
                    else
                    {
                        cout << "Error: Undefined function " << subname << endl;
                        return nullptr;
                    }
                }
            }
        }
    }
    G->graph2file();
    return G;
}

void Digraph::showDigraph()
{
    for (auto pair : adj)
    {
        cout << "-----" << endl;
        string v = pair.first;
        cout << "| " << v << " |";
        for (Edge &e : adj[v])
        {
            cout << " -> " << e.end();
        }
        cout << endl;
    }
    cout << "-----" << endl;
}

bool Edge::operator==(const Edge &e) const
{
    return e.v == v && e.w == w && e.weight == weight;
}

bool Edge::operator!=(const Edge &e) const
{
    return e.v != v || e.w != w || e.weight != weight;
}

void Digraph::addVertex(string v)
{
    if (adj.find(v) == adj.end())
    {
        adj[v] = vector<Edge>();
        inFunc[v] = vector<pair<string, int>>();
        outDegree[v] = 0;
        V++;
    }
}

void Digraph::shortestPath(string start, string end)
{
    if (adj.find(start) == adj.end() || adj.find(end) == adj.end())
    {
        cout << "Start or end vertex does not exist in the graph." << endl;
        return;
    }

    // BFS
    unordered_map<string, string> parent; // 用于追踪路径
    unordered_set<string> visited;
    queue<string> q;
    q.push(start);
    visited.insert(start);
    parent[start] = ""; // 起点没有父结点

    while (!q.empty())
    {
        string current = q.front();
        q.pop();

        // 找到目标结点，输出路径
        if (current == end)
        {
            vector<string> path;
            for (string at = end; at != ""; at = parent[at])
            {
                path.push_back(at);
            }
            reverse(path.begin(), path.end());

            cout << "Shortest path from " << start << " to " << end << ": ";
            for (size_t i = 0; i < path.size(); ++i)
            {
                cout << path[i];
                if (i < path.size() - 1)
                    cout << " -> ";
            }
            cout << endl;
            cout << "Path length: " << path.size() - 1 << endl;
            return;
        }

        // 遍历邻接结点
        for (auto &e : adj[current])
        {
            string neighbor = e.end();
            if (visited.find(neighbor) == visited.end())
            {
                visited.insert(neighbor);
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    cout << "No path found from " << start << " to " << end << "." << endl;
}

/*
 * @brief 计算环长度
 * @return int 环长度
 */
int Digraph::findCycleLength()
{
    unordered_map<string, int> visitState; // 0: 未访问, 1: 正在访问, 2: 已访问
    unordered_map<string, string> parent;  // 记录结点的父结点
    int cycleLength = 0;

    // DFS 遍历
    for (auto &kv : adj)
    {
        if (visitState[kv.first] == 0)
        { // 如果结点未访问
            if (dfs(kv.first, visitState, parent, cycleLength))
                return cycleLength;
        }
    }

    return 0; // 没有环
}

/*
 * @brief 深度优先搜索，检测环并计算环的长度
 * @param v 要访问的结点
 * @param visitState 记录结点的访问状态
 * @param parent 记录结点的父结点
 * @param cycleLength 记录环的长度
 * @return bool 是否有环
 */
bool Digraph::dfs(const string &v, unordered_map<string, int> &visitState, unordered_map<string, string> &parent, int &cycleLength)
{
    visitState[v] = 1; // 标记为正在访问

    for (auto &e : adj[v])
    {
        string neighbor = e.end();

        if (visitState[neighbor] == 0)
        { // 如果邻接结点未访问
            parent[neighbor] = v;
            if (dfs(neighbor, visitState, parent, cycleLength))
                return true;
        }
        else if (visitState[neighbor] == 1)
        { // 如果邻接结点正在访问，发现环
            // 计算环的长度
            cycleLength = 1;
            string current = v;
            while (current != neighbor)
            {
                current = parent[current];
                cycleLength++;
            }
            return true;
        }
    }

    visitState[v] = 2; // 标记为已访问
    return false;
}

/*
 * @brief 输出热门函数
 * @param n 热门度阈值
 * @return 函数无返回值
 */
void Digraph::showHotFunc(int n)
{
    time_t now = time(nullptr);
    tm *localTime = localtime(&now);

    // 格式化并输出
    string timeStr = to_string(localTime->tm_year + 1900) + "_" + // 年份
                     to_string(localTime->tm_mon + 1) + "_" +     // 月份（0~11，需要+1）
                     to_string(localTime->tm_mday) + "_" +        // 日期
                     to_string(localTime->tm_hour) + "_" +        // 小时
                     to_string(localTime->tm_min) + "_" +         // 分钟
                     to_string(localTime->tm_sec);                // 秒
    string root = "../";
    string filename = root + "file/" + "HotFunc_" + timeStr + ".txt";
    system("powershell -Command \"Remove-Item ..\\file\\* -Recurse -Force\"");
    ofstream file(filename);
    int count = 0;
    cout << "Hot functions:" << endl;
    file << "Hot functions:" << endl;
    for (auto pair : inFunc)
    {
        int degree = pair.second.size();
        if (degree >= n)
        {
            cout << pair.first << " degree: " << degree << endl;
            for (auto &p : pair.second)
                file << pair.first << " " << p.second << " " << p.first << " " << degree << endl;
            count++;
        }
    }
    if (count == 0)
    {
        cout << "None" << endl;
        file << "None" << endl;
    }
    file.close();
}

void Digraph::graph2file()
{
    // 获取当前时间戳
    time_t now = time(nullptr);
    tm *localTime = localtime(&now);

    // 格式化并输出
    string timeStr = to_string(localTime->tm_year + 1900) + "_" + // 年份
                     to_string(localTime->tm_mon + 1) + "_" +     // 月份（0~11，需要+1）
                     to_string(localTime->tm_mday) + "_" +        // 日期
                     to_string(localTime->tm_hour) + "_" +        // 小时
                     to_string(localTime->tm_min) + "_" +         // 分钟
                     to_string(localTime->tm_sec);                // 秒
    string root = "../";
    string filename = root + "cache/" + "cache_" + timeStr + ".txt";
    system("powershell -Command \"Remove-Item ..\\cache\\* -Recurse -Force\"");
    ofstream file(filename);
    for (auto pair : adj)
    {
        string v = pair.first;
        for (Edge &e : adj[v])
        {
            string w = e.end();
            file << v << " " << e.weight << " " << w << endl;
        }
    }
    change_since_save = false;
    file.close();
}

Digraph *loadFuncGraph()
{
    string cacheDirectory = "../cache"; // 假设缓存文件在这个目录下
    Digraph *G = new Digraph();

    // 遍历目录找到唯一文件
    string cacheFile;
    for (const auto &entry : filesystem::directory_iterator(cacheDirectory))
    {
        if (entry.is_regular_file())
        { // 检查是否是普通文件
            cacheFile = entry.path().string();
            break; // 只有一个文件，找到后直接退出循环
        }
    }
    // 检查是否找到文件
    if (cacheFile.empty())
    {
        std::cerr << "缓存目录中没有找到文件！" << std::endl;
        return nullptr;
    }

    ifstream file(cacheFile);
    if (!file.is_open())
    { // 检查文件是否成功打开
        std::cerr << "无法打开文件！" << std::endl;
        return nullptr;
    }

    string line;
    string v;
    int weight;
    string w;
    while (getline(file, line))
    {
        istringstream iss(line);
        iss >> v >> weight >> w;
        G->addVertex(v);
        G->addVertex(w);
        Edge e(v, w, weight);
        G->addEdge(e);
    }

    file.close(); // 关闭文件
    return G;
}

// Function.cpp
