#ifndef VECTOR_H
#define VECTOR_H

// Vector 类的声明
class Vector
{
private:
    int degree;                 // 维度
    double magnitude();         // 向量模长
    int dotProduct(Vector *V2); // 向量点乘

public:
    int *coef;                       // 系数数组
    Vector(int N);                   // 构造函数
    ~Vector();                       // 析构函数
    void printVector();              // 打印向量
    int VectorDegree();              // 向量的维度
    void addVector(Vector *V2);      // 向量加法
    void subtractVector(Vector *V2); // 向量减法
    double cosine(Vector *V2);       // 向量余弦
};

#endif

// Vector.h