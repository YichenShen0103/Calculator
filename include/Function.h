#ifndef FUNCTION_H
#define FUNCTION_H

#include "Expression.h"

class Edge
{
private:
    string v, w;

public:
    Edge(string v, string w, int we);
    int weight;
    string start();
    string end();
    bool operator==(const Edge &e) const;
    bool operator!=(const Edge &e) const;
};

class Digraph
{
private:
    int V;
    int E;
    unordered_map<string, vector<pair<string, int>>> inFunc;
    unordered_map<string, int> outDegree;
    unordered_map<string, vector<Edge>> adj;

public:
    Digraph();
    void addVertex(string v);
    int getV() const;
    int getE() const;
    void addEdge(Edge &e);
    vector<Edge> adjList(string v);
    vector<Edge> edges();
    void showDigraph();
    void shortestPath(string s, string t);
    int findCycleLength();
    bool dfs(const string &v, unordered_map<string, int> &visitState, unordered_map<string, string> &parent, int &cycleLength);
    void showHotFunc(int n);
    void graph2file();
};

Digraph *buildFuncGraph();
Digraph *loadFuncGraph();

class Function : public Expression // 继承Expression类
{
private:
    string nonPostFixExpr; // 非后缀表达式

public:
    string name;                                              // 函数名
    Function();                                               // 构造函数
    Function(string expr, unordered_map<string, double> var); // 构造函数，用于函数调用
    double calculate();                                       // 计算表达式的值
    shared_ptr<Tree> buildFuncTree();                         // 构建函数调用树
    Function(const Function &E);                              // 拷贝构造函数
    ~Function();                                              // 析构函数
    void calAndShowValue();                                   // 计算函数值
    void showFunction();                                      // 显示函数表达式
};

#endif

// Function.h