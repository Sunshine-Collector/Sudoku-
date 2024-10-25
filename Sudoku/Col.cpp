#include "Col.h"
#include <set>

// 构造函数实现
Col::Col() {
}

// 向列中添加一个单元格
void Col::addCell(Cell& cell) {
    cells.push_back(&cell);
}

// 检查列是否合法
bool Col::isValid() const {
    std::set<int> seen;
    for (auto cell : cells) {
        int value = cell->getValue();
        if (value != 0) {
            if (seen.count(value)) {
                return false; // 存在重复的值
            }
            seen.insert(value);
        }
    }
    return true;
}
void Col::addCellPointer(Cell* cellPtr)
{
    cells.push_back(cellPtr);
}