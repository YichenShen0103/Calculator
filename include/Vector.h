#ifndef VECTOR_H
#define VECTOR_H

// Vector 类的声明
class Vector
{
    friend class Matrix; // 设置友元类，方便Matrix调用内容

private:
    int degree;                    // 维度
    double magnitude();            // 向量模长
    double dotProduct(Vector *V2); // 向量点乘

public:
    int *coef;                       // 系数数组
    Vector(int N);                   // 构造函数
    Vector(int N, int x);            // 构造函数，一般不调用，用于静默创建对象
    ~Vector();                       // 析构函数
    void printVector();              // 打印向量
    int VectorDegree();              // 向量的维度
    void addVector(Vector *V2);      // 向量加法
    void subtractVector(Vector *V2); // 向量减法
    double cosine(Vector *V2);       // 向量余弦
};

#endif

// Vector.h