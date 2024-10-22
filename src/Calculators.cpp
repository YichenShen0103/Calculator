#include "Calculators.h" // 该头文件包含本文件实现的函数的声明
#include "Vector.h"      // 包含 Vector 类声明
#include "Polyn.h"       // 包含 Polyn 类声明
#include "ListNode.h"    // 包含 ListNode 类声明
#include "Expression.h"  // 包含 Expression 类声明
#include "Function.h"    // 包含 Function 类声明
#include "Matrix.h"      // 包含 Matrix 类声明
#include <iostream>
#include <iomanip>
#include <unordered_map>
using namespace std;

extern unordered_map<string, Function *> functions; // 全局函数表

/*
 * @brief 矩阵计算器的主函数
 * @return 函数无返回值
 */
void MatrixCalculator()
{
    cout << "-------------------" << endl;
    cout << "Welcome to MatrixCalculator!" << endl;
    while (true)
    {
        char mode = menu('M'); // 显示菜单并获取用户选择
        switch (mode)
        {
        case '1': // 矩阵加法
        {
            int coln, rown, colm, rowm;
            cout << "Input the dimension of the first matrix (rows cols): "; // 输入矩阵的维度
            cin >> rown >> coln;
            Matrix *M1 = new Matrix(rown, coln);                              // 创建第一个矩阵
            cout << "Input the dimension of the second matrix (rows cols): "; // 输入矩阵的维度
            cin >> rowm >> colm;
            Matrix *M2 = new Matrix(rowm, colm); // 创建第二个矩阵
            cout << "M1: " << endl;
            M1->printMatrix();
            cout << "M2: " << endl;
            M2->printMatrix();
            M1->addMatrix(M2); // 加法运算
            cout << "M1 + M2: " << endl;
            M1->printMatrix();
            delete M1; // 释放内存
            break;
        }
        case '2': // 矩阵减法
        {
            int coln, rown, colm, rowm;
            cout << "Input the dimension of the first matrix (rows cols): "; // 输入矩阵的维度
            cin >> rown >> coln;
            Matrix *M1 = new Matrix(rown, coln);                              // 创建第一个矩阵
            cout << "Input the dimension of the second matrix (rows cols): "; // 输入矩阵的维度
            cin >> rowm >> colm;
            Matrix *M2 = new Matrix(rowm, colm); // 创建第二个矩阵
            cout << "M1: " << endl;
            M1->printMatrix();
            cout << "M2: " << endl;
            M2->printMatrix();
            M1->subtractMatrix(M2); // 减法运算
            cout << "M1 - M2: " << endl;
            M1->printMatrix();
            delete M1; // 释放内存
            break;
        }
        case '3': // 帮助信息
        {
            cout << "PolynCalculator_ListNode is a simple calculator for polynomials." << endl;
            cout << "This version uses ListNodes to implement the same functionality." << endl;
            cout << "You can add/subtract two polynomials by inputting their degrees and coefficients." << endl;
            cout << "For more detail, please read our instructions." << endl;
            break;
        }
        case 'm': // 矩阵乘法
        {
            int coln, rown, colm, rowm;
            cout << "Input the dimension of the first matrix (rows cols): "; // 输入矩阵的维度
            cin >> rown >> coln;
            Matrix *M1 = new Matrix(rown, coln);                              // 创建第一个矩阵
            cout << "Input the dimension of the second matrix (rows cols): "; // 输入矩阵的维度
            cin >> rowm >> colm;
            Matrix *M2 = new Matrix(rowm, colm); // 创建第二个矩阵
            cout << "M1: " << endl;
            M1->printMatrix();
            cout << "M2: " << endl;
            M2->printMatrix();
            M1->multiplyMatrix(M2); // 乘法运算
            cout << "M1 * M2: " << endl;
            M1->printMatrix();
            delete M1; // 释放内存
            break;
        }
        case 'd': // 矩阵的行列式
        {
            int row;
            cout << "Please input the dimension of the matrix: "; // 输入矩阵的维度
            cin >> row;
            Matrix *M = new Matrix(row, row); // 创建矩阵
            cout << "M: " << endl;
            M->printMatrix();
            cout << "det(M): " << M->determinant() << endl;
            delete M; // 释放内存
            break;
        }
        case 't': // 矩阵转置
        {
            int row, col;
            cout << "Please input the dimension of the matrix(rows cols): "; // 输入矩阵的维度
            cin >> row >> col;
            Matrix *M = new Matrix(row, col); // 创建矩阵
            cout << "M: " << endl;
            M->printMatrix();
            M->T(); // 转置矩阵
            cout << "M^T: " << endl;
            M->printMatrix();
            delete M; // 释放内存
            break;
            break;
        }
        case 'e': // 矩阵的特征值
        {
            int row;
            cout << "Please input the dimension of the matrix: "; // 输入矩阵的维度
            cin >> row;
            Matrix *M = new Matrix(row, row); // 创建矩阵
            cout << "M: " << endl;
            M->printMatrix();
            M->eigenValue();
            cout << "Eigenvalues (results have been rounded to five decimal places): " << endl;
            for (int i = 0; i < row; i++)
            {
                cout << fixed << setprecision(5) << M->eigenVal[i] << " ";
            }
            cout << endl;
            delete M; // 释放内存
            break;
        }
        case 'q': // 退出程序
        {
            cout << "Exiting PolynCalculator..." << endl;
            return;
        }
        default: // 输入错误
        {
            cout << "Invalid input!" << endl;
            break;
        }
        }
    }
}

/*
 * @brief 科学计算器的菜单函数
 * @return char 选择的选项
 */
char SciCalcMenu()
{
    char mode;
    cout << "--------MENU--------" << endl;
    cout << "1. Calculate no-variable expressions" << endl;
    cout << "2. Allocate storage space for parameterized expressions" << endl;
    cout << "3. Assign values to stored variables" << endl;
    cout << "4. Calculate expressions with variables" << endl;
    cout << "5. Help" << endl;
    cout << "q. Exit" << endl;
    cout << "Please select an option: ";
    cin >> mode;
    return mode;
}

/*
 * @brief 科学计算器的主函数
 * @return 函数无返回值
 */
void ScienceCalculator()
{
    cout << "-------------------" << endl;
    cout << "Welcome to ScienceCalculator!" << endl;
    Expression *M = new Expression(0); // 创建一个空的表达式用于存储参数化表达式
    while (true)
    {
        char mode = SciCalcMenu(); // 显示菜单并获取用户选择
        switch (mode)
        {
        case '1': // 计算无变量表达式
        {
            Expression *E = new Expression();
            if (E->hasVar())
            {
                cout << "Expression has variables!" << endl;
            }
            else
            {
                cout << "Result: " << E->calculate() << endl;
            }
            delete E;
            break;
        }
        case '2': // 分配存储空间储存参数化表达式
        {
            Expression *E = new Expression();
            if (!E->hasVar()) // 表达式没有变量
            {
                cout << "Expression has no variables! Sure to calculate? (y/[n])" << endl;
                char ans;
                cin >> ans;
                if (ans == 'y' || ans == 'Y')
                {
                    cout << "Result: " << E->calculate() << endl;
                }
                else
                {
                    cout << "Operation cancelled." << endl;
                }
            }
            else
            {
                *M = *E; // 将参数化表达式赋值给 M
            }

            delete E;
            E = nullptr; // 将指针设置为 nullptr，防止悬空指针
            break;
        }
        case '3': // 给储存的变量赋值
        {
            string variable;
            double value;
            cout << "Please enter the variable and its value (split by <Space>): "; // 输入变量和值
            cin >> variable >> value;
            M->varAssign(variable, value); // 给 M 中的变量赋值
            break;
        }
        case '4': // 计算带变量表达式
        {
            Expression *E = new Expression(*M); // 复制 M 作为临时表达式
            cout << "Result: " << E->calculate() << endl;
            delete E;
            break;
        }
        case '5': // 帮助信息
        {
            cout << "ScienceCalculator is a simple calculator for scientific calculations." << endl;
            cout << "You can calculate expressions with and without variables." << endl;
            cout << "For more detail, please read our instructions." << endl;
            break;
        }
        case 'q': // 退出程序
        {
            cout << "Exiting ScienceCalculator..." << endl;
            delete M;
            return;
        }
        default: // 输入错误
        {
            cout << "Invalid input!" << endl;
            break;
        }
        }
    }
}

/*
 * @brief 向量计算器的主函数
 * @return 函数无返回值
 */
void Vectorcalculator()
{
    cout << "-------------------" << endl;
    cout << "Welcome to VectorCalculator!" << endl;
    while (true)
    {
        char mode = menu('V'); // 显示菜单并获取用户选择
        switch (mode)
        {
        case '1': // 向量加法
        {
            int n;
            cout << "Input the degree of the two vectors: "; // 输入向量的维度
            cin >> n;
            Vector *V1 = new Vector(n); // 创建两个向量
            Vector *V2 = new Vector(n);
            cout << "V1: ";
            V1->printVector();
            cout << "V2: ";
            V2->printVector();
            V1->addVector(V2);
            cout << "V1 + V2: ";
            V1->printVector();
            delete V1; // 释放内存
            break;
        }
        case '2':
        {
            int n;
            cout << "Input the degree of the two vectors: "; // 输入向量的维度
            cin >> n;
            Vector *V1 = new Vector(n); // 创建两个向量
            Vector *V2 = new Vector(n);
            cout << "V1: ";
            V1->printVector();
            cout << "V2: ";
            V2->printVector();
            V1->subtractVector(V2);
            cout << "V1 - V2: ";
            V1->printVector();
            delete V1; // 释放内存
            break;
        }
        case '3': // 帮助信息
        {
            cout << "VectorCalculator is a simple calculator for vectors." << endl;
            cout << "You can add/subtract two vectors by inputting their degrees and elements." << endl;
            cout << "For more detail, please read our instructions." << endl;
            break;
        }
        case 'c': // 向量的余弦值
        {
            int n;
            cout << "Input the degree of the two vectors: "; // 输入向量的维度
            cin >> n;
            Vector *V1 = new Vector(n); // 创建两个向量
            Vector *V2 = new Vector(n);
            cout << "V1: ";
            V1->printVector();
            cout << "V2: ";
            V2->printVector();
            double cosine = V1->cosine(V2);
            cout << "cos<V1, V2>: " << cosine << endl;
            delete V1; // 释放内存
            break;
        }
        case 'q': // 退出程序
        {
            cout << "Exiting VectorCalculator..." << endl;
            return;
        }
        default: // 输入错误
        {
            cout << "Invalid input!" << endl;
            break;
        }
        }
    }
}

/*
 * @brief 多项式计算器的主函数
 * @return 函数无返回值
 */
void Polyncalculator()
{
    cout << "-------------------" << endl;
    cout << "Welcome to PolynCalculator!" << endl;
    while (true)
    {
        char mode = menu('P'); // 显示菜单并获取用户选择
        switch (mode)
        {
        case '1': // 多项式加法
        {
            int n, m;
            cout << "Input the higest degree of the first Polynomial: "; // 输入多项式的最高次数
            cin >> n;
            Polyn *P1 = new Polyn(n);                                     // 创建多项式
            cout << "Input the higest degree of the second Polynomial: "; // 输入多项式的最高次数
            cin >> m;
            Polyn *P2 = new Polyn(m); // 创建另一个多项式
            cout << "P1: ";
            P1->printPolyn();
            cout << "P2: ";
            P2->printPolyn();
            P1->addPolyn(P2);
            cout << "P1 + P2: ";
            P1->printPolyn();
            delete P1; // 释放内存
            break;
        }
        case '2': // 多项式减法
        {
            int n, m;
            cout << "Input the higest degree of the first Polynomial: "; // 输入多项式的最高次数
            cin >> n;
            Polyn *P1 = new Polyn(n);                                     // 创建第一个多项式
            cout << "Input the higest degree of the second Polynomial: "; // 输入多项式的最高次数
            cin >> m;
            Polyn *P2 = new Polyn(m); // 创建另一个多项式
            cout << "P1: ";
            P1->printPolyn();
            cout << "P2: ";
            P2->printPolyn();
            P1->subtractPolyn(P2);
            cout << "P1 - P2: ";
            P1->printPolyn();
            delete P1; // 释放内存
            break;
        }
        case '3': // 帮助信息
        {
            cout << "PolynCalculator is a simple calculator for polynomials." << endl;
            cout << "You can add/subtract two polynomials by inputting their degrees and coefficients." << endl;
            cout << "For more detail, please read our instructions." << endl;
            break;
        }
        case 'm': // 多项式乘法
        {
            int n, m;
            cout << "Input the higest degree of the first Polynomial: "; // 输入多项式的最高次数
            cin >> n;
            Polyn *P1 = new Polyn(n);                                     // 创建第一个多项式
            cout << "Input the higest degree of the second Polynomial: "; // 输入多项式的最高次数
            cin >> m;
            Polyn *P2 = new Polyn(m); // 创建另一个多项式
            cout << "P1: ";
            P1->printPolyn();
            cout << "P2: ";
            P2->printPolyn();
            P1->multiplyPolyn(P2);
            cout << "P1 * P2: ";
            P1->printPolyn();
            delete P1; // 释放内存
            break;
        }
        case 'd': // 多项式导数
        {
            int n, m;
            cout << "Input the higest degree of the first Polynomial: "; // 输入多项式的最高次数
            cin >> n;
            Polyn *P = new Polyn(n);                               // 创建多项式
            cout << "Please input the degree of the derivative: "; // 输入求导次数
            cin >> m;
            cout << "P: ";
            P->printPolyn();
            P->derivative(m); // 求导
            cout << "The " << m << "-th derivative of P is: ";
            P->printPolyn();
            delete P; // 释放内存
            break;
        }
        case 'q': // 退出程序
        {
            cout << "Exiting PolynCalculator..." << endl;
            return;
        }
        default: // 输入错误
        {
            cout << "Invalid input!" << endl;
            break;
        }
        }
    }
}

/*
 * @brief 三个计算器的模板菜单函数
 * @return char 选择的选项
 */
char menu(char cal)
{
    char mode;
    cout << "--------MENU--------" << endl;
    cout << "1. Addition" << endl;
    cout << "2. Subtraction" << endl;
    cout << "3. Help" << endl;
    if (cal == 'V')
        cout << "c. Cosine(Only for vectors)" << endl; // 向量的余弦值
    if (cal == 'P' || cal == 'M')
        cout << "m. Multiply(Only for Polyn and Matrix)" << endl; // 多项式乘法
    if (cal == 'P')
        cout << "d. Derivative(Only for Polyn)" << endl; // 多项式导数
    if (cal == 'M')
    {
        cout << "d. Determinant(Only for Matrix)" << endl; // 矩阵行列式
        cout << "t. Transpose(Only for Matrix)" << endl;   // 矩阵转置
        cout << "e. Eigenvalues(Only for Matrix)" << endl; // 矩阵特征值
    }
    cout << "q. Exit" << endl;
    cout << "Please select an option: ";
    cin >> mode;
    return mode;
}

/*
 * @brief 链表实现的多项式计算器的主函数
 * @return 函数无返回值
 */
void Polyncalculator_ListNode()
{
    cout << "-------------------" << endl;
    cout << "Welcome to PolynCalculator!" << endl;
    while (true)
    {
        char mode = menu('P'); // 显示菜单并获取用户选择
        switch (mode)
        {
        case '1': // 多项式加法
        {
            int n, m;
            cout << "Input the higest degree of the first Polynomial: "; // 输入多项式的最高次数
            cin >> n;
            Polyn_LN *P1 = new Polyn_LN(n);                               // 创建第一个多项式
            cout << "Input the higest degree of the second Polynomial: "; // 输入多项式的最高次数
            cin >> m;
            Polyn_LN *P2 = new Polyn_LN(m); // 创建另一个多项式
            cout << "P1: ";
            P1->printPolyn();
            cout << "P2: ";
            P2->printPolyn();
            P1->addPolyn(P2); // 加法运算
            cout << "P1 + P2: ";
            P1->printPolyn();
            delete P1; // 释放内存
            break;
        }
        case '2': // 多项式减法
        {
            int n, m;
            cout << "Input the higest degree of the first Polynomial: "; // 输入多项式的最高次数
            cin >> n;
            Polyn_LN *P1 = new Polyn_LN(n);                               // 创建第一个多项式
            cout << "Input the higest degree of the second Polynomial: "; // 输入多项式的最高次数
            cin >> m;
            Polyn_LN *P2 = new Polyn_LN(m); // 创建另一个多项式
            cout << "P1: ";
            P1->printPolyn();
            cout << "P2: ";
            P2->printPolyn();
            P1->subtractPolyn(P2); // 减法运算
            cout << "P1 - P2: ";
            P1->printPolyn();
            delete P1; // 释放内存
            break;
        }
        case '3': // 帮助信息
        {
            cout << "PolynCalculator_ListNode is a simple calculator for polynomials." << endl;
            cout << "This version uses ListNodes to implement the same functionality." << endl;
            cout << "You can add/subtract two polynomials by inputting their degrees and coefficients." << endl;
            cout << "For more detail, please read our instructions." << endl;
            break;
        }
        case 'm': // 多项式乘法
        {
            int n, m;
            cout << "Input the higest degree of the first Polynomial: "; // 输入多项式的最高次数
            cin >> n;
            Polyn_LN *P1 = new Polyn_LN(n);                               // 创建第一个多项式
            cout << "Input the higest degree of the second Polynomial: "; // 输入多项式的最高次数
            cin >> m;
            Polyn_LN *P2 = new Polyn_LN(m); // 创建另一个多项式
            cout << "P1: ";
            P1->printPolyn();
            cout << "P2: ";
            P2->printPolyn();
            P1->multiplyPolyn(P2); // 乘法运算
            cout << "P1 * P2: ";
            P1->printPolyn();
            delete P1; // 释放内存
            break;
        }
        case 'd': // 多项式导数
        {
            int n, m;
            cout << "Input the higest degree of the first Polynomial: "; // 输入多项式的最高次数
            cin >> n;
            Polyn_LN *P = new Polyn_LN(n); // 创建多项式
            cout << "P: ";
            P->printPolyn();
            cout << "Please input the degree of the derivative: "; // 输入求导次数
            cin >> m;
            P->derivative(m); // 求导
            cout << "The " << m << "-th derivative of P is: ";
            P->printPolyn();
            delete P; // 释放内存
            break;
        }
        case 'q': // 退出程序
        {
            cout << "Exiting PolynCalculator..." << endl;
            return;
        }
        default: // 输入错误
        {
            cout << "Invalid input!" << endl;
            break;
        }
        }
    }
}

/*
 * @brief 函数计算器的主函数
 * @return 函数无返回值
 */
void FunctionCalculator()
{
    cout << "-------------------" << endl;
    cout << "Welcome to FunctionCalculator!" << endl;
    while (true)
    {
        char mode = FunctionMenu(); // 显示菜单并获取用户选择
        switch (mode)
        {
        case '1': // 定义一个函数
        {
            Function *F = new Function();
            functions[F->name] = F;
            break;
        }
        case '2': // 通过给定自变量的值计算函数值
        {
            cout << "Please enter the function name: ";
            string name;
            cin >> name;
            if (functions.find(name) == functions.end()) // 函数未定义
            {
                cout << "Function not defined!" << endl;
            }
            else
            {
                Function *F = functions[name];
                F->calAndShowValue();
            }
            break;
        }
        case '3': // 查看所有已定义的函数
        {
            cout << "All defined functions: " << endl;
            for (auto it = functions.begin(); it != functions.end(); it++)
            {
                Function *F = it->second;
                F->showFunction();
            }
            break;
        }
        case '4': // 帮助信息
        {
            cout << "FunctionCalculator is a calculator for function calculations." << endl;
            cout << "You can define functions and calculate with given variable values." << endl;
            cout << "For more detail, please read our instructions." << endl;
            break;
        }
        case 'q': // 退出程序
        {
            cout << "Exiting ScienceCalculator..." << endl;
            for (auto it = functions.begin(); it != functions.end(); it++)
            {
                delete it->second;
            }
            return;
        }
        default: // 输入错误
        {
            cout << "Invalid input!" << endl;
            break;
        }
        }
    }
}

/*
 * @brief 函数计算器的菜单函数
 * @return char 选择的选项
 */
char FunctionMenu()
{
    char mode;
    cout << "--------MENU--------" << endl;
    cout << "1. Define a function" << endl;
    cout << "2. Calculate function value with given independent variable values" << endl;
    cout << "3. View all function defined" << endl;
    cout << "4. Help" << endl;
    cout << "q. Exit" << endl;
    cout << "Please select an option: ";
    cin >> mode;
    return mode;
}

// Calculations.cpp