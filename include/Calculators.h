#ifndef CALCULATORS_H
#define CALCULATORS_H

#include <vector>
#include <string>
using namespace std;

// 各个计算器和菜单的函数声明
char menu(char cal);                                 // 菜单模板
char SciCalcMenu();                                  // 科学计算器菜单
void Polyncalculator();                              // 多项式计算器
void Vectorcalculator();                             // 向量计算器
void Polyncalculator_ListNode();                     // 多项式链表计算器
void ScienceCalculator();                            // 科学计算器
void MatrixCalculator();                             // 矩阵计算器
void FunctionCalculator();                           // 函数计算器
char FunctionMenu();                                 // 函数计算器菜单
void ask_sort(vector<vector<string>> &output_lines); // 排序函数

#endif

// Calculators.h