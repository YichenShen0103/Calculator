#include "Vector.h" // 本文件实现的函数声明位置
#include <iostream>
#include <cmath>
using namespace std;

/*
 * @brief 构造函数，初始化N个元素的向量
 * @param N 向量的维度
 * @return 构造函数无返回值
 */
Vector::Vector(int N)
{
    coef = new int[N]; // 为向量分配内存空间

    cout << "Please input " << N << " numbers: ";
    for (int i = 0; i < N; i++)
    {
        cin >> coef[i]; // 输入向量的各个元素
    }
    degree = N; // 向量的维度
}

/*
 * @brief 析构函数，释放向量的内存空间
 * @return 析构函数无返回值
 */
Vector::~Vector()
{
    delete[] coef; // 释放向量的内存空间
    coef = nullptr;
}

/*
 * @brief 打印向量
 * @return 无返回值
 */
void Vector::printVector()
{
    cout << "< ";
    for (int i = 0; i < degree - 1; i++)
    {
        cout << coef[i] << " , "; // 打印向量的各个元素，并用空格隔开
    }
    cout << coef[degree - 1] << " >" << endl;
}

/*
 * @brief 获取向量的维度
 * @return int 向量的维度
 */
int Vector::VectorDegree()
{
    return degree;
}

/*
 * @brief 向量加法
 * @param V2 另一个向量
 * @return 无返回值
 */
void Vector::addVector(Vector *V2)
{
    for (int i = 0; i < V2->VectorDegree(); i++)
    {
        coef[i] += V2->coef[i]; // 向量的各个元素相加
    }

    delete V2;
    V2 = nullptr; // 释放V2内存空间
}

/*
 * @brief 向量减法
 * @param V2 另一个向量
 * @return 无返回值
 */
void Vector::subtractVector(Vector *V2)
{
    for (int i = 0; i < V2->VectorDegree(); i++)
    {
        coef[i] -= V2->coef[i]; // 向量的各个元素相减
    }

    delete V2;
    V2 = nullptr; // 释放V2内存空间
}

/*
 * @brief 向量点乘
 * @param V2 另一个向量
 * @return int 向量点乘的结果
 */
int Vector::dotProduct(Vector *V2)
{
    int result = 0;
    for (int i = 0; i < V2->VectorDegree(); i++)
    {
        result += coef[i] * V2->coef[i]; // 向量的各个元素点乘
    }

    return result;
}

/*
 * @brief 向量模长
 * @return double 向量模长
 */
double Vector::magnitude()
{
    double result = 0;
    for (int i = 0; i < degree; i++)
    {
        result += coef[i] * coef[i]; // 向量的各个元素平方和
    }
    result = sqrt(result); // 计算向量模长,sqrt()函数来自cmath头文件

    return result;
}

/*
 * @brief 向量夹角
 * @param V2 另一个向量
 * @return double 向量夹角的弧度值
 */
double Vector::cosine(Vector *V2)
{
    int dot = dotProduct(V2); // 向量点乘
    int mag1 = magnitude();   // 向量模长
    int mag2 = V2->magnitude();
    double result = dot / (mag1 * mag2); // 计算向量夹角

    delete V2;
    V2 = nullptr; // 释放V2内存空间
    return result;
}

// Vector.cpp