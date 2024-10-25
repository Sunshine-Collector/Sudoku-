#include "Row.h"
#include "set"
// Ĭ�Ϲ��캯��
Row::Row() {
}

void Row::addCellPointer(Cell* cellPtr) 
{
    cells.push_back(cellPtr);
}

// ������Ƿ�Ϸ�
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
                return false; //�����ظ���ֵ
            }
            seen.insert(value);
        }
    }
    return true;
}