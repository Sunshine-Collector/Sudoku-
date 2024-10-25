#include "Row.h"
#include "set"
// 默认构造函数
Row::Row() {
}

void Row::addCellPointer(Cell* cellPtr) 
{
    cells.push_back(cellPtr);
}

// 检查行是否合法
bool Row::isValid() const 
{
    std::set<int> seen;
    for (const Cell* cell : cells) 
    {
        int value = cell->getValue();
        if (value != 0) 
        {
            if (seen.count(value)) 
            {
                return false; //存在重复的值
            }
            seen.insert(value);
        }
    }
    return true;
}