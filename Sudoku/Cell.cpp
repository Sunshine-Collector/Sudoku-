#include "Cell.h"
#include <algorithm>

// 构造函数
Cell::Cell() : value(0) {
    // 初始化时将值设置为0
}

// 设置单元格的值
void Cell::setValue(int val) 
{
    value = val;
}

// 获取单元格的值
int Cell::getValue() const 
{

    return value;
}

// 添加候选数到集合中
void Cell::addCandidate(int candidate) 
{
        candidates.push_back(candidate);
        std::sort(candidates.begin(), candidates.end());  //保持候选数有序
}

// 移除候选数
void Cell::removeCandidate(int candidate) {
    auto it = std::find(candidates.begin(), candidates.end(), candidate);
    if (it != candidates.end()) {
        *it = 0; // 将找到的元素的值改为零
    }
}

// 检查某个数是否是候选数
bool Cell::isCandidate(int candidate) const 
{
    return std::find(candidates.begin(), candidates.end(), candidate) != candidates.end();
}

// 获取候选数集合
std::vector<int>& Cell::getCandidates(){
    return candidates;
}

// 打印单元格信息
void Cell::print() const {
    if (value != 0) {
        std::cout << value;
    }
    else {
        std::cout << ".";
    }
}