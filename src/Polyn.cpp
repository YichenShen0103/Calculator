#include "Polyn.h" // 包含类声明头文件
#include <iostream>
using namespace std;

/*
 * @brief 用于多项式的加长
 * @param
 *   int m 新的多项式的阶数
 * @return 函数无返回值
 */
void Polyn::expand(int m)
{
    // 如果当前阶数已经大于或等于 m，则无需扩展，直接返回
    if (level >= m)
        return;

    // 分配一个新的数组，用于存储扩展后的系数数组
    double *new_coef = new double[m + 1];

    // 遍历所有的项，将原有系数复制到新数组中，其余部分补零
    for (int i = 0; i <= m; i++)
    {
        if (i <= level) // 如果 i 小于或等于当前阶数，将原系数复制到新数组
        {
            new_coef[i] = coef[i];
        }
        else // 否则，将新位置的系数设置为 0
        {
            new_coef[i] = 0;
        }
    }

    // 释放旧的系数数组内存
    delete[] coef;

    // 将 coef 指针指向新的扩展后的系数数组
    coef = new_coef;

    // 更新多项式的阶数
    level = m;
}

/*
 * @brief 构造函数，用于初始化一个N阶多项式
 * @param
 *   int N 多项式的阶数
 * @return 构造函数无返回值
 */
Polyn::Polyn(int N)
{
    // 分配内存来存储N阶多项式的系数
    coef = new double[N + 1];

    // 循环输入系数，确保最高阶系数不为0
    while (true)
    {
        cout << "Please input " << N + 1 << " numbers ( the " << N + 1 << "th shall not be 0 ): ";
        for (int i = 0; i < N + 1; i++)
        {
            cin >> coef[i]; // 输入系数
        }
        if (coef[N]) // 确保最后一个系数不为0
        {
            cout << "Initialized!" << endl;
            break;
        }
        else
        {
            cout << "Error: The " << N + 1 << "th number is 0! Try again!" << endl;
            exit(0); // 如果最高阶系数为0，直接退出程序
        }
    }
    level = N; // 设置多项式的阶数
}

/*
 * @brief 析构函数，释放多项式的系数内存
 * @return 析构函数无返回值
 */
Polyn::~Polyn()
{
    // 释放系数数组的内存
    delete[] coef;
}

/*
 * @brief 打印多项式的表示
 * @return 函数无返回值
 */
void Polyn::printPolyn()
{
    // 打印常数项
    cout << coef[0] << " + ";
    // 打印其他阶数的项
    for (int i = 1; i < level; i++)
    {
        cout << coef[i] << "x^" << i << " + ";
    }
    // 打印最高阶项
    cout << coef[level] << "x^" << level << endl;
}

/*
 * @brief 获取多项式的阶数
 * @return 返回多项式的阶数
 */
int Polyn::PolynLength()
{
    return level; // 返回当前多项式的阶数
}

/*
 * @brief 将当前多项式与另一个多项式相加
 * @param
 *   Polyn *P2 另一个多项式
 * @return 函数无返回值
 */
void Polyn::addPolyn(Polyn *P2)
{
    // 扩展当前多项式的阶数以匹配P2的阶数
    if (level < P2->PolynLength())
        expand(P2->PolynLength());

    // 逐项相加
    for (int i = 0; i <= P2->PolynLength(); i++)
    {
        coef[i] += P2->coef[i];
    }

    // 删除P2，防止内存泄漏
    delete P2;
    P2 = nullptr;
}

/*
 * @brief 将当前多项式减去另一个多项式
 * @param
 *   Polyn *P2 另一个多项式
 * @return 函数无返回值
 */
void Polyn::subtractPolyn(Polyn *P2)
{
    // 扩展当前多项式的阶数以匹配P2的阶数
    if (level < P2->PolynLength())
        expand(P2->PolynLength());

    // 逐项相减
    for (int i = 0; i < P2->PolynLength(); i++)
    {
        coef[i] -= P2->coef[i];
    }

    // 处理最高阶项的特殊情况
    if (coef[level] == P2->coef[level])
    {
        coef[level] = 0;
        level -= 1; // 阶数减少1
    }
    else
        coef[level] -= P2->coef[level];

    // 删除P2
    delete P2;
    P2 = nullptr;
}

/*
 * @brief 将当前多项式与另一个多项式相乘
 * @param
 *   Polyn *P2 另一个多项式
 * @return 函数无返回值
 */
void Polyn::multiplyPolyn(Polyn *P2)
{
    int P1_len = level;                // 记录当前多项式的阶数
    int m = level + P2->PolynLength(); // 计算相乘后的最高阶数
    expand(m);                         // 扩展多项式以容纳结果

    // 创建一个新的数组来存储结果
    double *new_coef = new double[m + 1]();

    // 逐项相乘并累加结果
    for (int i = 0; i <= P1_len; i++)
    {
        for (int j = 0; j <= P2->PolynLength(); j++)
        {
            new_coef[i + j] += coef[i] * P2->coef[j];
        }
    }

    // 释放原来的系数数组
    delete[] coef;
    coef = new_coef; // 更新系数数组指针
}

/*
 * @brief 计算当前多项式的导数
 * @param
 *   int n 导数的阶数
 * @return 函数无返回值
 */
void Polyn::derivative(int n)
{
    double *new_coef = new double[level + 1](); // 创建新数组存储导数结果

    // 复制当前的系数
    for (int i = 0; i <= level; i++)
    {
        new_coef[i] = coef[i];
    }

    // 计算n阶导数
    for (int i = 0; i < n; i++)
    {
        if (level == -1) // 如果阶数已经降为-1，直接退出
        {
            level = 0;
            break;
        }
        int j = 0;
        while (j < level)
        {
            new_coef[j] = new_coef[j + 1] * (j + 1); // 计算导数
            j++;
        }
        new_coef[j] = 0; // 导数的最高阶项系数为0
        level--;         // 阶数减少
    }

    coef = new_coef; // 更新系数数组
}

// Polyn.cpp