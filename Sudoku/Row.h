#ifndef ROW_H
#define ROW_H

#include "Cell.h"
#include <vector>

class Row {
public:
    Row();  // Ĭ�Ϲ��캯��
    void addCellPointer(Cell* cellPtr);
    bool isValid() const;  // ������Ƿ�Ϸ�
private:
    std::vector<Cell*> cells;  // �洢���еĵ�Ԫ��ָ��
};

#endif // ROW_H