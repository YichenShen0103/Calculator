#include "ListNode.h" // 包含本文件实现的函数的声明
#include <iostream>
using namespace std;

/*
 * @brief Node 类的构造函数
 * @param double value 数值
 *        int exp 指数
 * @return 无返回值
 */
Node::Node(double value, int exp)
    : data(value), expn(exp), next(nullptr) // 初始化数据域
{
}

/*
 * @brief Polyn_LN 类的构造函数
 * @param int N 多项式的项数
 * @return 无返回值
 */
Polyn_LN::Polyn_LN(int N)
    : head(nullptr) // 初始化头指针为空
{
    degree = 0; // 初始化多项式的阶数（实际为项数）为0
    while (true)
    {
        cout << "Please input " << N + 1 << " numbers ( the " << N + 1 << "th shall not be 0 ): ";
        double val;
        for (int i = 0; i < N + 1; i++)
        {
            cin >> val;
            append(val); // 逐项输入多项式
        }
        if (val)
        {
            cout << "Initialized!" << endl;
            break;
        }
        else
        {
            cout << "Error: The " << N + 1 << "th number is 0! Try again!" << endl; // N+1 个数为 0
            exit(0);
        }
    }
}

/*
 * @brief 在尾部添加一个节点
 * @param double value 数值
 * @return 无返回值
 */
void Polyn_LN::append(double value)
{
    Node *newNode = new Node(value, degree++); // 创建新节点
    if (head == nullptr)
    {
        head = newNode; // 头指针为空，则直接指向新节点
    }
    else
    {
        Node *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next; // 找到尾节点
        }
        temp->next = newNode;    // 尾节点的下一节点指向新节点
        newNode->next = nullptr; // 新节点的下一节点指向 nullptr
    }
}

/*
 * @brief 两个多项式相加
 * @param Polyn_LN *P2 另一个多项式
 * @return 无返回值
 */
void Polyn_LN::addPolyn(Polyn_LN *P2)
{
    Node *p1 = this->head; // 指向第一个多项式的头节点
    Node *p2 = P2->head;   // 指向第二个多项式的头节点
    Node *prev = nullptr;  // 用于追踪前一个节点
    while (p1 != nullptr && p2 != nullptr)
    {
        if (p1->expn == p2->expn)
        {
            p1->data += p2->data; // 相同指数项相加
            if (p1->data == 0)
            { // 如果系数为0，删除该项
                if (prev == nullptr)
                {
                    head = p1->next;
                }
                else
                {
                    prev->next = p1->next;
                }
                Node *temp = p1;
                p1 = p1->next;
                delete temp;
                continue;
            }
            prev = p1;
            p1 = p1->next;
            p2 = p2->next; // 同时移动两个指针
        }
        else if (p1->expn < p2->expn) // 指数小的项移到前面
        {
            prev = p1;
            p1 = p1->next;
        }
        else
        {
            Node *newNode = new Node(p2->data, p2->expn);
            if (prev == nullptr) // 头指针为空，则直接指向新节点
            {
                newNode->next = head;
                head = newNode;
            }
            else
            {
                prev->next = newNode;
                newNode->next = p1;
            }
            prev = newNode;
            p2 = p2->next;
            degree++;
        }
    }
    // 如果 P2 还有剩余的项
    while (p2 != nullptr)
    {
        Node *newNode = new Node(p2->data, p2->expn); // 复制 P2 的剩余项
        if (prev == nullptr)
        {
            newNode->next = head;
            head = newNode;
        }
        else
        {
            prev->next = newNode;
        }
        prev = newNode;
        p2 = p2->next;
        degree++; // 阶数增加
    }
}

/*
 * @brief 两个多项式相减
 * @param Polyn_LN *P2 另一个多项式
 * @return 无返回值
 */
void Polyn_LN::subtractPolyn(Polyn_LN *P2)
{
    Node *p1 = this->head; // 指向第一个多项式的头节点
    Node *p2 = P2->head;   // 指向第二个多项式的头节点
    Node *prev = nullptr;  // 用于追踪前一个节点
    while (p1 != nullptr && p2 != nullptr)
    {
        if (p1->expn == p2->expn) // 相同指数项相减
        {
            p1->data -= p2->data;
            prev = p1;
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->expn < p2->expn) // p1 指数小的项移到前面
        {
            prev = p1;
            p1 = p1->next;
        }
        else // p2 指数小的项不动
        {
            Node *newNode = new Node((-1) * p2->data, p2->expn);
            if (prev == nullptr)
            {
                newNode->next = head;
                head = newNode;
            }
            else
            {
                prev->next = newNode;
                newNode->next = p1;
            }
            prev = newNode;
            p2 = p2->next;
            degree++;
        }
    }
    // 如果 P2 还有剩余的项
    while (p2 != nullptr)
    {
        Node *newNode = new Node((-1) * p2->data, p2->expn); // 复制 P2 的剩余项
        if (prev == nullptr)                                 // 头指针为空，则直接指向新节点
        {
            newNode->next = head;
            head = newNode;
        }
        else // 否则，插入到 prev 后面
        {
            prev->next = newNode;
        }
        prev = newNode;
        p2 = p2->next;
        degree++;
    }
}

/*
 * @brief 输出多项式
 * @return 无返回值
 */
void Polyn_LN::printPolyn()
{
    Node *temp = head; // 指向头节点
    while (temp->next != nullptr)
    {
        if (temp->expn == 0) // 系数为 1 时，省略 x
        {
            cout << temp->data << " + ";
        }
        else if (temp->expn == 1)
        {
            cout << temp->data << "x + ";
        }
        else
        {
            cout << temp->data << "x^" << temp->expn << " + ";
        }
        temp = temp->next;
    }
    cout << temp->data << "x^" << temp->expn << endl;
}

/*
 * @brief 析构函数，释放内存
 * @return 无返回值
 */
Polyn_LN::~Polyn_LN()
{
    Node *temp;
    while (head != nullptr)
    {
        // 释放内存
        temp = head;
        head = head->next;
        delete temp;
    }
}

/*
 * @brief 查找指定指数的节点
 * @param int expn 指数
 * @return Node* 节点指针
 */
Node *Polyn_LN::findNode(int expn)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->expn == expn) // 找到指定指数的节点
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr; // 没找到，返回 nullptr
}

/*
 * @brief 计算多项式相乘的值并存入P1
 * @param Polyn_LN *P2 另一个多项式
 * @return 函数无返回值
 */
void Polyn_LN::multiplyPolyn(Polyn_LN *P2)
{
    Polyn_LN *P3 = new Polyn_LN(); // 新建一个多项式
    Node *p1 = this->head;         // 指向第一个多项式的头节点
    while (p1 != nullptr)
    {
        Node *p2 = P2->head; // 指向第二个多项式的头节点
        while (p2 != nullptr)
        {
            if (P3->findNode(p1->expn + p2->expn) == nullptr) // 指数不存在，新建节点
            {
                Node *newNode = new Node(p1->data * p2->data, p1->expn + p2->expn);
                P3->append(newNode->data);
            }
            else // 指数存在，累加
            {
                Node *temp = P3->findNode(p1->expn + p2->expn);
                temp->data += p1->data * p2->data;
            }
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    this->head = P3->head; // P3给P1赋值
    this->degree = P3->degree;
}

/*
 * @brief 构造函数，一般用于特殊情况
 * @return 无返回值
 */
Polyn_LN::Polyn_LN()
{
    head = nullptr; // 初始化头指针为空
    degree = 0;
}

/*
 * @brief 求导函数
 * @param int n 求导次数
 * @return 无返回值
 */
void Polyn_LN::derivative(int n)
{
    for (int i = 0; i < n; i++) // 求导 n 次
    {
        if (degree == 0) // 阶数（长度）为 0，达到边界条件
        {
            degree++;
            return;
        }
        Node *curr = head;
        Node *prev = nullptr;
        while (curr != nullptr)
        {
            if (curr->expn != 0)
            {
                curr->data *= curr->expn; // 系数乘以指数
                curr->expn--;
            }
            else
            {
                curr->data = 0;
            }
            prev = curr;
            curr = curr->next;
        }
        if (prev != nullptr)
        {
            prev->next = nullptr;
        }
        degree--;
    }

    while (head->expn == 0 && head->data == 0 && head->next != nullptr)
        head = head->next; // 去除首项为 0 的项
}

// ListNode.cpp