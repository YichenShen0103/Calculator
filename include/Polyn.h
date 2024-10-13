#ifndef POLYN_H
#define POLYN_H

// Polyn 类的声明
class Polyn
{
private:
    int level;          // 多项式的阶数
    void expand(int m); // 扩充多项式的阶数

public:
    double *coef;                  // 多项式的系数
    Polyn(int N);                  // 构造函数，创建多项式
    ~Polyn();                      // 析构函数，释放内存
    void printPolyn();             // 输出多项式
    int PolynLength();             // 计算多项式的长度
    void addPolyn(Polyn *P2);      // 多项式加法
    void subtractPolyn(Polyn *P2); // 多项式减法
    void multiplyPolyn(Polyn *P2); // 多项式乘法
    void derivative(int n);        // 求导
};

#endif

// Polyn.h