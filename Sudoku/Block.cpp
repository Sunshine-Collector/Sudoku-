#include "Block.h"
#include <set>

// ���캯��ʵ��
Block::Block() 
{
    // ��ʼ�� cells ������Ԥ�ȷ��� 9 ����Ԫ��Ŀռ�
    cells.reserve(9);
}

// ��������һ����Ԫ��
void Block::addCell(Cell& cell) 
{
    cells.push_back(&cell);
}
void Block::addCellPointer(Cell* cellPtr)
{
    cells.push_back(cellPtr);
}
// �����е������Ƿ���Ч
bool Block::isValid() const {
    std::set<int> seen;
    for (const Cell* cell : cells) {
        int value = cell->getValue();
        if (value != 0) {
            if (seen.count(value)) {
                return false; //�����ظ���ֵ
            }
            seen.insert(value);
        }
    }
    return true;
}