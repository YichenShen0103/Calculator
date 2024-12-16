/*
 * Project:    Calculator06
 * Author:     Yichen Shen
 * Date:       2024-12-9
 * Language:   C++
 * Version:    V6.0
 * Scale:      about 3900 lines in total
 */

#include "Calculators.h" // 包含所有计算器和分菜单的头文件
#include "Function.h"    // 全局变量声明所需的头文件
#include <iostream>
#include <unordered_map>
using namespace std;
unordered_map<string, Function *> functions; // 定义一个变量哈希表
bool change_since_save = true;               // 定义一个标志变量，用于判断是否有修改并需要保存

int main()
{
    char mode; // 选择的模式
    while (true)
    {
        // 总目录
        cout << "--------Main Menu--------" << endl;
        cout << "This Program is a integration of several calculators. Here are the menu: " << endl;
        cout << "1. Polynomial Calculator" << endl;
        cout << "2. Vector Calculator" << endl;
        cout << "3. Polynomial Calculator with Linked List" << endl;
        cout << "4. Science Calculator supporting variable" << endl;
        cout << "5. Function Calculator" << endl;
        cout << "6. Matrix Calculator" << endl;
        cout << "q. Exit" << endl;
        cout << "Please select an option: ";
        cin >> mode;
        switch (mode)
        {
        case '1':
        {
            // 多项式计算器
            Polyncalculator();
            break;
        }
        case '2':
        {
            // 向量计算器
            Vectorcalculator();
            break;
        }
        case '3':
        {
            // 多项式计算器（链表实现）
            Polyncalculator_ListNode();
            break;
        }
        case '4':
        {
            // 科学计算器（支持变量）
            ScienceCalculator();
            break;
        }
        case '5':
        {
            // 函数计算器
            FunctionCalculator();
            break;
        }
        case '6':
        {
            // 矩阵计算器
            MatrixCalculator();
            break;
        }
        case 'q':
        {
            // 退出程序
            cout << "Exiting Program..." << endl;
            return 0;
        }
        default:
        {
            // 输入错误
            cout << "Invalid input!" << endl;
            break;
        }
        }
    }
}

// main.cpp