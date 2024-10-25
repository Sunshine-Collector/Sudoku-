#ifndef CELL_H
#define CELL_H

#include <vector>
#include <iostream>

class Cell {
public:
    // 默认构造函数
    Cell();
   
    // 设置单元格的值
    void setValue(int val);
    // 获取单元格的值
    int getValue() const;
    // 添加候选数
    void addCandidate(int candidate);
    // 移除候选数
    void removeCandidate(int candidate);
    // 检查某个数是否是候选数
    bool isCandidate(int candidate) const;
    // 获取候选数集合
    std::vector<int>& getCandidates();
    void clearCandidates() 
    {
        candidates.clear();  // 清空候选数的向量
    }
    int getvalue()
    {
        return value;
    }
    std::vector<int> getcandidates()
    {
        return candidates;
    }
    void print() const;
    bool operator==(const Cell& other) const {
        // 首先比较 value 成员变量
        if (value != other.value) {
            return false;
        }
        // 然后比较 candidates 向量
        if (candidates.size() != other.candidates.size()) {
            return false;
        }
        for (size_t i = 0; i < candidates.size(); ++i) {
            if (candidates[i] != other.candidates[i]) {
                return false;
            }
        }
        return true;
    }
private:
    int value;  // 单元格的当前值
    std::vector<int> candidates;  // 候选数集合

};
#endif
