#include "Sudoku.h"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include<random>
#include <windows.h>
// 构造函数
Sudoku::Sudoku() 
{
    for (int i = 0; i < 9; ++i)
    {
        std::vector<Cell> row; // 创建一个新的行向量
        for (int j = 0; j < 9; ++j)
        {
            row.push_back(Cell()); // 在行中添加 9 个 Cell 对象
        }
        grid.push_back(row); // 将这行添加到 grid 中
    }

    // 初始化行、列、块
    for (int i = 0; i < 9; ++i) 
    {
        rows.push_back(Row());
        cols.push_back(Col());
        blocks.push_back(Block());
    }
    for (int i = 0;i < 9;i++)
    {
        for (int j = 0;j < 9;j++)
        {
            rows[i].addCellPointer(&grid[i][j]);
        }
    }
    for (int i = 0;i < 9;i++)
    {
        for (int j = 0;j < 9;j++)
        {
            cols[i].addCellPointer(&grid[j][i]);
        }
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int blockIndex = (i / 3) * 3 + (j / 3); //计算当前单元格属于哪个块
            blocks[blockIndex].addCellPointer(&grid[i][j]);
        }
    }
}


void Sudoku::initialize()//数独初始化
{
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            // 获取当前单元格
            // 重置单元格的值
            grid[row][col].setValue(0);
            // 清空单元格的候选数
            grid[row][col].clearCandidates();
        }
    }
}
// 读取数独文件
/*
void Sudoku::readSudoku(const std::string& filename)
{
    std::ifstream infile;
    infile.open("easy.txt");
    if (!infile.is_open())
    {
        std::cerr << "文件读入失败:" << filename << std::endl;
        return;
    }
    else
    {
        int numofboard = rand() % (15 - 1 + 1) + 1;
        int currentboard = 0;
        std::vector<int>row;//行向量
        while (true)
        {
            std::vector<std::vector<int>> tmp;//临时棋盘的数字
            while (true)
            {
                char data[300];

                infile.getline(data, 300);
                if (data[0] == '-')//一个数独板结束
                {

                    break;
                }
                for (int i = 0;i < strlen(data);i++)
                {
                    if (('1' <= data[i] && data[i] <= '9'))
                        row.push_back(data[i] - '0');

                }
                tmp.push_back(row);//显式拷贝构造
                row.clear();
            }
            if (!numofboard)
            {
                for (int i = 0; i < 9; ++i)
                {
                    for (int j = 0; j < 9; ++j)
                    {
                        grid[i][j].setValue(tmp[i][j]);  //将值设置到对应的 Cell 对象中
                    }
                }
                break;
            }
            numofboard--;
        }
        infile.close();
    }
}
*/

// 设置单元格的值
void Sudoku::setValue(int row, int col, int value) {
    if (row >= 0 && row < 9 && col >= 0 && col < 9) {
        grid[row][col].setValue(value);
    }
}



// 根据难度加载数独
/*
* void Sudoku::loadPuzzleBasedOnDifficulty(int difficulty) 
{
    int digcount=0;
    switch (difficulty)
    {
    case 1://简单
        digcount = rand() % (30 - 20 + 1) + 20;
    case 2://中等
        digcount = rand() % (40 - 30 + 1) + 30;
    case 3://困难
        digcount = rand() % (50 - 40 + 1) + 40;
    default:
        break;
    }
    while (digcount)
    {
        int x = rand() % 9;
        int y = rand() % 9;
        if (grid[x][y].getValue() == 0)
            continue;
        int answer = grid[x][y].getValue();
        grid[x][y].addCandidate(answer);//把答案塞到侯选数里
        grid[x][y].setValue(0);

        int numCandidates = rand() % 8 + 1;  //生成 1 到 8 个候选数
        
        while (numCandidates)
        {
            int candidate = rand() % 9 + 1;
            if (std::find(grid[x][y].getCandidates().begin(), grid[x][y].getCandidates().end(), candidate) != grid[x][y].getCandidates().end()) {
                continue; //如果候选数字已经存在，则跳过
            }
            grid[x][y].addCandidate(candidate);
            numCandidates--;
        }
        
        if (grid[x][y].getCandidates().size() < 9)
        {
            grid[x][y].getCandidates().resize(9, 0); // 用0填充直到向量大小为9
            
        }
        digcount--;
        //后期这里加数独检测唯一解solveSudoku函数
        //
    }
}
*/



void Sudoku::display()
{
     printf("      C1       C2       C3       C4       C5       C6       C7       C8       C9    \n");//////////////////////输出（暂用）。
     for (int m = 0; m < 9; m++)
     {
         for (int i = 0; i < 3; i++)
         {
             int numvalue[3][3] = {};
             int numcand[3][3] = {};
             for (int n = 0; n < 9; n++)
             {
                 if (grid[m][n].getValue() != 0)
                 {
                     numvalue[1][1] = grid[m][n].getValue();
                 }
                 else
                 {
                     if (grid[m][n].getCandidates().size() <= 9) {
                         // 将候选数字填入3x3数组
                         for (size_t i = 0; i < grid[m][n].getCandidates().size(); ++i)
                         {
                             int index = grid[m][n].getCandidates()[i];
                             numcand[i / 3][i % 3] = grid[m][n].getCandidates()[i];
                         }
                     }
                 }
                 if (i == 0 && n == 0)
                     printf("   -------  -------  -------  -------  -------  -------  -------  -------  ------- \n");
                 if (i == 1 && n == 0)
                     printf("R%d", m + 1);
                 if (i != 1 && n == 0)
                     printf("  ");
                 printf("|");
                 for (int j = 0; j < 3; j++)
                 {
                     if (grid[m][n].getValue() != 0)
                     {
                         HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                         CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
                         GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
                         WORD originalColorAttrs = consoleInfo.wAttributes; // 保存原始颜色属性

                         // 设置文本颜色为绿色
                         SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                         if (i == 1 && j == 1) printf(" %d", numvalue[i][j]);
                         else printf("  ");
                         SetConsoleTextAttribute(hConsole, originalColorAttrs);
                     }
                     else
                     {
                         if (numcand[i][j] != 0)
                             printf(" %d", numcand[i][j]);
                         else
                             printf("  ");
                     }
                 }
                 printf(" |");
             }
             if (i != 2)
                 printf("\n");

         }
         printf("\n");
     }
     printf("   -------  -------  -------  -------  -------  -------  -------  -------  ------- \n");
};

