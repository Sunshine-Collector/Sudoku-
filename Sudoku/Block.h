#ifndef BLOCK_H
#define BLOCK_H

#include "Cell.h"
#include <vector>

class Block {
public:
    Block();
    void addCell(Cell& cell);
    bool isValid() const;
    void addCellPointer(Cell* cellPtr);
private:
    std::vector<Cell*> cells;
    int index;
};

#endif // BLOCK_H