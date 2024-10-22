#include "Matrix.h" // 包含本文件实现的函数声明位置所在的头文件
#include "Vector.h" // 包含Vector类声明所在的头文件
#include <vector>
#include <cmath>
#include <map>
#include <iostream>
using namespace std;

/*
 * @brief 计算矩阵M的余子式
 * @param int r 行下标
 * @param int c 列下标
 * @return Matrix * 矩阵M的代数余子式的指针
 */
Matrix *Matrix::getSubMatrix(int r, int c)
{
    Matrix *sub = new Matrix(row - 1, col - 1); // 新建一个子矩阵
    for (int i = 0; i < row; i++)
    {
        if (i == r)
            continue; // 跳过行r
        for (int j = 0; j < col; j++)
        {
            if (j == c)
                continue;                                                 // 跳过列c
            sub->data[i - (i > r)]->coef[j - (j > c)] = data[i]->coef[j]; // 填充子矩阵
        }
    }
    return sub; // 返回子矩阵
}

/*
 * @brief 特殊构造函数，用于静默创建对象
 * @param int rows 矩阵的行数
 * @param int cols 矩阵的列数
 * @param int x 占位变量，用于与其他构造函数区分
 * @return 构造函数无返回值
 */
Matrix::Matrix(int rows, int cols, int x)
{
    this->row = rows;
    this->col = cols;
    data = vector<Vector *>(rows, nullptr); // 定义一个cols个元素的向量
    for (int i = 0; i < rows; i++)
    {
        data[i] = new Vector(cols, 0); // 为每一行分配一个cols个元素的向量
    }
    isSquare = (rows == cols);    // 判断矩阵是否为方阵
    eigenVal = vector<double>(0); // 定义一个空的特征值向量
}

/*
 * @brief 构造函数
 * @param int rows 矩阵的行数
 * @param int cols 矩阵的列数
 * @return 构造函数无返回值
 */
Matrix::Matrix(int rows, int cols)
{
    this->row = rows;
    this->col = cols;
    data = vector<Vector *>(rows, nullptr); // 定义一个cols个元素的向量
    for (int i = 0; i < rows; i++)
    {
        cout << "Line " << i + 1 << ": " << endl;
        data[i] = new Vector(cols); // 为每一行分配一个cols个元素的向量
    }
    isSquare = (rows == cols);    // 判断矩阵是否为方阵
    eigenVal = vector<double>(0); // 定义一个空的特征值向量
}

/*
 * @brief 析构函数
 * @return 析构函数无返回值
 */
Matrix::~Matrix()
{
    for (int i = 0; i < row; i++)
    {
        if (data[i] != nullptr)
            delete data[i]; // 释放每一行的向量内存
    }
}

/*
 * @brief 格式化输出矩阵，具体样式类似于python3的numpy库
 * @return 函数无返回值
 */
void Matrix::printMatrix()
{
    cout << "["; // 输出矩阵的开始符
    for (int i = 0; i < row; i++)
    {
        if (i != 0)
            cout << " ";
        cout << "[ "; // 输出每一行的开始符
        for (int j = 0; j < col - 1; j++)
        {
            cout << data[i]->coef[j] << " "; // 输出每一个元素
        }
        cout << data[i]->coef[col - 1] << " ]";
        if (i != row - 1)
            cout << endl; // 输出每一行的结束符
    }
    cout << "]" << endl; // 输出矩阵的结束符
}

/*
 * @brief 矩阵加法
 * @param Matrix *M 另一个矩阵的指针
 * @return 函数无返回值
 */
void Matrix::addMatrix(Matrix *M)
{
    if (row != M->row || col != M->col)
        cout << "Error: Matrix dimensions do not match." << endl;
    else
        for (int i = 0; i < row; i++)
        {
            data[i]->addVector(M->data[i]); // 逐行相加
            M->data[i] = nullptr;
        }
    delete M; // 释放M指向的内存
}

/*
 * @brief 矩阵减法
 * @param Matrix *M 另一个矩阵的指针
 * @return 函数无返回值
 */
void Matrix::subtractMatrix(Matrix *m)
{
    if (row != m->row || col != m->col)
        cout << "Error: Matrix dimensions do not match." << endl;
    else
        for (int i = 0; i < row; i++)
        {
            data[i]->subtractVector(m->data[i]); // 逐行相减
            m->data[i] = nullptr;
        }
    delete m; // 释放m指向的内存
}

/*
 * @brief 计算矩阵行列式的值
 * @return double 矩阵行列式的值
 */
double Matrix::determinant()
{
    if (isSquare == false)
    {
        cout << "Error: Matrix is not square." << endl;
        return NAN; // 矩阵不是方阵，无法计算行列式
    }
    // 基本情况: 1x1 矩阵
    if (row == 1)
    {
        return data[0]->coef[0];
    }
    // 基本情况: 2x2 矩阵
    if (row == 2)
    {
        return data[0]->coef[0] * data[1]->coef[1] - data[0]->coef[1] * data[1]->coef[0];
    }

    int det = 0;
    for (int j = 0; j < row; j++)
    {
        // 拉普拉斯展开，(-1)^(i+j) * 矩阵[0][j] * 子矩阵行列式
        Matrix *subMatrix = getSubMatrix(0, j);
        det += (j % 2 == 0 ? 1 : -1) * data[0]->coef[j] * subMatrix->determinant();
        delete subMatrix;
    }

    return det;
}

/*
 * @brief 计算矩阵的转置矩阵
 * @return 函数无返回值
 */
void Matrix::T()
{
    vector<Vector *> temp(col, nullptr);
    for (int i = 0; i < row; i++)
    {
        temp[i] = new Vector(col, 0); // 为每一行分配一个col个元素的向量
        for (int j = 0; j < col; j++)
        {
            temp[i]->coef[j] = data[j]->coef[i]; // 转置矩阵
        }
    }
    for (int i = 0; i < row; i++)
    {
        delete data[i];    // 释放原矩阵内存
        data[i] = temp[i]; // 转置矩阵
    }

    int tmp = row;
    row = col;
    col = tmp; // 矩阵维度交换
}

void Matrix::multiplyMatrix(Matrix *M)
{
    if (col != M->row)
    {
        cout << "Wrong scale of the two Matrixs" << endl; // 矩阵维度不匹配，无法相乘
        return;
    }

    vector<Vector *> Ans(row, nullptr); // 结果矩阵Ans的大小为m x p
    for (int i = 0; i < row; i++)
    {
        Ans[i] = new Vector(col, 0); // 为每一行分配一个col个元素的向量
        for (int j = 0; j < col; j++)
        {
            Ans[i]->coef[j] = 0;
        }
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < M->col; j++)
        {
            for (int k = 0; k < col; k++)
            {
                Ans[i]->coef[j] += data[i]->coef[k] * M->data[k]->coef[j]; // 逐元素相乘
            }
        }
    }

    for (int i = 0; i < row; i++)
    {
        delete data[i]; // 释放Ans矩阵内存
    }
    data = Ans;   // 结果矩阵C赋值给矩阵A
    col = M->col; // 矩阵A的列数变为p
    delete M;     // 释放M指向的内存
}

/*
 * @brief 计算矩阵的特征值
 * @return 函数无返回值
 */
void Matrix::eigenValue()
{
    if (col != row) // 矩阵不是方阵
    {
        cout << "Error: Matrix is not square." << endl;
        return;
    }

    int nDim = row; // 矩阵维度
    eigenVal.resize(nDim);
    int nJt = 1000;      // 最大迭代次数
    double dbEps = 1e-6; // 精度要求
    vector<double> pMatrix(nDim * nDim);
    vector<double> pdblVects(nDim * nDim);
    for (int i = 0; i < nDim; i++)
    {
        for (int j = 0; j < nDim; j++)
        {
            pMatrix[i * nDim + j] = data[i]->coef[j];
        }
    }
    for (int i = 0; i < nDim; i++)
    {
        pdblVects[i * nDim + i] = 1.0f;
        for (int j = 0; j < nDim; j++)
        {
            if (i != j)
                pdblVects[i * nDim + j] = 0.0f;
        }
    }

    int nCount = 0; // 迭代次数
    while (1)
    {
        // 在pMatrix的非对角线上找到最大元素
        double dbMax = pMatrix[1];
        int nRow = 0;
        int nCol = 1;
        for (int i = 0; i < nDim; i++) // 行
        {
            for (int j = 0; j < nDim; j++) // 列
            {
                double d = fabs(pMatrix[i * nDim + j]);

                if ((i != j) && (d > dbMax))
                {
                    dbMax = d;
                    nRow = i;
                    nCol = j;
                }
            }
        }

        if (dbMax < dbEps) // 精度符合要求
            break;

        if (nCount > nJt) // 迭代次数超过限制
            break;

        nCount++;

        double dbApp = pMatrix[nRow * nDim + nRow];
        double dbApq = pMatrix[nRow * nDim + nCol];
        double dbAqq = pMatrix[nCol * nDim + nCol];

        // 计算旋转角度
        double dbAngle = 0.5 * atan2(-2 * dbApq, dbAqq - dbApp);
        double dbSinTheta = sin(dbAngle);
        double dbCosTheta = cos(dbAngle);
        double dbSin2Theta = sin(2 * dbAngle);
        double dbCos2Theta = cos(2 * dbAngle);

        pMatrix[nRow * nDim + nRow] = dbApp * dbCosTheta * dbCosTheta +
                                      dbAqq * dbSinTheta * dbSinTheta + 2 * dbApq * dbCosTheta * dbSinTheta;
        pMatrix[nCol * nDim + nCol] = dbApp * dbSinTheta * dbSinTheta +
                                      dbAqq * dbCosTheta * dbCosTheta - 2 * dbApq * dbCosTheta * dbSinTheta;
        pMatrix[nRow * nDim + nCol] = 0.5 * (dbAqq - dbApp) * dbSin2Theta + dbApq * dbCos2Theta;
        pMatrix[nCol * nDim + nRow] = pMatrix[nRow * nDim + nCol];

        for (int i = 0; i < nDim; i++)
        {
            if ((i != nCol) && (i != nRow))
            {
                int u = i * nDim + nRow; // p
                int w = i * nDim + nCol; // q
                dbMax = pMatrix[u];
                pMatrix[u] = pMatrix[w] * dbSinTheta + dbMax * dbCosTheta;
                pMatrix[w] = pMatrix[w] * dbCosTheta - dbMax * dbSinTheta;
            }
        }

        for (int j = 0; j < nDim; j++)
        {
            if ((j != nCol) && (j != nRow))
            {
                int u = nRow * nDim + j; // p
                int w = nCol * nDim + j; // q
                dbMax = pMatrix[u];
                pMatrix[u] = pMatrix[w] * dbSinTheta + dbMax * dbCosTheta;
                pMatrix[w] = pMatrix[w] * dbCosTheta - dbMax * dbSinTheta;
            }
        }

        // 计算特征向量
        for (int i = 0; i < nDim; i++)
        {
            int u = i * nDim + nRow; // p
            int w = i * nDim + nCol; // q
            dbMax = pdblVects[u];
            pdblVects[u] = pdblVects[w] * dbSinTheta + dbMax * dbCosTheta;
            pdblVects[w] = pdblVects[w] * dbCosTheta - dbMax * dbSinTheta;
        }
    }

    // 对特征值进行排序以及重新排列特征向量,特征值即pMatrix主对角线上的元素
    map<double, int> mapEigen;
    for (int i = 0; i < nDim; i++)
    {
        eigenVal[i] = pMatrix[i * nDim + i];

        mapEigen.insert(make_pair(eigenVal[i], i));
    }

    vector<double> pdbTmpVec(nDim * nDim);
    map<double, int>::reverse_iterator iter = mapEigen.rbegin();
    for (int j = 0; iter != mapEigen.rend() && j < nDim; ++iter, ++j)
    {
        for (int i = 0; i < nDim; i++)
        {
            pdbTmpVec[i * nDim + j] = pdblVects[i * nDim + iter->second];
        }

        // 特征值重新排列
        eigenVal[j] = iter->first;
    }

    // 设定正负号
    for (int i = 0; i < nDim; i++)
    {
        double dSumVec = 0;
        for (int j = 0; j < nDim; j++)
            dSumVec += pdbTmpVec[j * nDim + i];
        if (dSumVec < 0)
        {
            for (int j = 0; j < nDim; j++)
                pdbTmpVec[j * nDim + i] *= -1;
        }
    }

    pdblVects = pdbTmpVec;
}

// Matrix.cpp