/*
 * Project:    Calculator
 * Author:     Yichen Shen
 * Date:       2024-10-14
 * Language:   C++
 * Version:    V2.1
 * Scale:      about 1685 lines in total
 */

#include "Calculators.h" // 包含所有计算器和分菜单的头文件
#include <iostream>
using namespace std;

int main()
{
    // 总目录
    cout << "This Program is a integration of several calculators. Here are the menu: " << endl;
    cout << "1. Polynomial Calculator" << endl;
    cout << "2. Vector Calculator" << endl;
    cout << "3. Polynomial Calculator with Linked List" << endl;
    cout << "4. Science Calculator supporting variable" << endl;
    cout << "q. Exit" << endl;
    cout << "Please select an option: ";
    char mode; // 选择的模式
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

// main.cpp