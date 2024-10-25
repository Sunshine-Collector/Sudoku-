#include "Col.h"
#include <set>

// ���캯��ʵ��
Col::Col() {
}

// ���������һ����Ԫ��
void Col::addCell(Cell& cell) {
    cells.push_back(&cell);
}

// ������Ƿ�Ϸ�
bool Col::isValid() const {
    std::set<int> seen;
    for (auto cell : cells) {
        int value = cell->getValue();
        if (value != 0) {
            if (seen.count(value)) {
                return false; // �����ظ���ֵ
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