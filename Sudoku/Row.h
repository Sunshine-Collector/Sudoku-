#ifndef ROW_H
#define ROW_H

#include "Cell.h"
#include <vector>

class Row {
public:
    Row();  // 默认构造函数
    void addCellPointer(Cell* cellPtr);
    bool isValid() const;  // 检查行是否合法
private:
    std::vector<Cell*> cells;  // 存储行中的单元格指针
};

#endif // ROW_H