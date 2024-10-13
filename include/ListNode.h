#ifndef LISTNODE_H
#define LISTNODE_H

// Node 类的声明
class Node
{
public:
    double data; // 系数域
    int expn;    // 指数域
    Node *next;  // 指针域

    Node(double value, int exp); // 构造函数
};

// Polyn_LN 类的声明
class Polyn_LN
{
public:
    Node *head; // 头指针
    int degree; // 多项式的最高次项的指数

    Polyn_LN(int N);                  // 构造函数
    Polyn_LN();                       // 构构函数，一般不主动调用，用于特殊情况处理
    void append(double value);        // 尾插法
    Node *findNode(int expn);         // 查找指定指数的节点
    void addPolyn(Polyn_LN *P2);      // 多项式相加
    void subtractPolyn(Polyn_LN *P2); // 多项式相减
    void multiplyPolyn(Polyn_LN *P2); // 多项式相乘
    void derivative(int n);           // 求导
    void printPolyn();                // 输出多项式
    ~Polyn_LN();                      // 析构函数
};

#endif

// ListNode.h