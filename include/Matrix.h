#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"
#include <vector>
using namespace std;

class Matrix
{
private:
    bool isSquare;                      // 是否是方阵
    Matrix *getSubMatrix(int r, int c); // 获取子矩阵

public:
    int row, col;                      // 行数和列数
    vector<double> eigenVal;           // 特征值
    vector<Vector *> data;             // 二维数组
    Matrix(int rows, int cols);        // 构造函数
    Matrix(int rows, int cols, int x); // 特殊构造函数，一般不调用，用于静默初始化
    ~Matrix();                         // 析构函数
    void printMatrix();                // 打印矩阵
    void addMatrix(Matrix *m);         // 矩阵加法
    void subtractMatrix(Matrix *m);    // 矩阵减法
    void multiplyMatrix(Matrix *m);    // 矩阵乘法
    void T();                          // 矩阵转置
    void eigenValue();                 // 矩阵的特征值
    double determinant();              // 矩阵的行列式
};

#endif

// matrix.h