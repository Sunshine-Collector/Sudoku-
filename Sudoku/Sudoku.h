#ifndef SUDOKU_H
#define SUDOKU_H

#include "Cell.h"
#include "Row.h"
#include "Col.h"
#include "Block.h"
#include <vector>
#include <iostream>
#include <algorithm>

class Sudoku 
{
public:
    Sudoku();
    void setValue(int row, int col, int value);
    void initialize();
    void display();

    void removeCandidates(int row, int col, int candidate) 
    {
        grid[row][col].removeCandidate(candidate);
    }

    Cell& getCell(int row,int col)
    {
        return grid[row][col];
    }
    Row getRow(int row)
    {
        return rows[row];
    }
    Col getCol(int col)
    {
        return cols[col];
    }
    Block getBlock(int bl)
    {
        return blocks[bl];
    }


private:
    std::vector<std::vector<Cell>> grid;
    std::vector<Row> rows;
    std::vector<Col> cols;
    std::vector<Block> blocks;
};

#endif // SUDOKU_H