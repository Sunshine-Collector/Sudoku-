#ifndef COL_H
#define COL_H

#include "Cell.h"
#include <vector>

class Col {
public:
    Col();
    void addCell(Cell& cell);
    bool isValid() const;
    void addCellPointer(Cell* cellPtr);
private:
    std::vector<Cell*> cells;
};

#endif // COL_H