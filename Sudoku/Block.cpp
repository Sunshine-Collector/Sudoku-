#include "Block.h"
#include <set>

// 构造函数实现
Block::Block() 
{
    // 初始化 cells 向量，预先分配 9 个单元格的空间
    cells.reserve(9);
}

// 向块中添加一个单元格
void Block::addCell(Cell& cell) 
{
    cells.push_back(&cell);
}
void Block::addCellPointer(Cell* cellPtr)
{
    cells.push_back(cellPtr);
}
// 检查块中的数字是否有效
bool Block::isValid() const {
    std::set<int> seen;
    for (const Cell* cell : cells) {
        int value = cell->getValue();
        if (value != 0) {
            if (seen.count(value)) {
                return false; //存在重复的值
            }
            seen.insert(value);
        }
    }
    return true;
}