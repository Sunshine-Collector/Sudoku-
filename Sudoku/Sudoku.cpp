#include "Sudoku.h"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include<random>
#include <windows.h>
// ���캯��
Sudoku::Sudoku() 
{
    for (int i = 0; i < 9; ++i)
    {
        std::vector<Cell> row; // ����һ���µ�������
        for (int j = 0; j < 9; ++j)
        {
            row.push_back(Cell()); // ��������� 9 �� Cell ����
        }
        grid.push_back(row); // ��������ӵ� grid ��
    }

    // ��ʼ���С��С���
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
            int blockIndex = (i / 3) * 3 + (j / 3); //���㵱ǰ��Ԫ�������ĸ���
            blocks[blockIndex].addCellPointer(&grid[i][j]);
        }
    }
}


void Sudoku::initialize()//������ʼ��
{
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            // ��ȡ��ǰ��Ԫ��
            // ���õ�Ԫ���ֵ
            grid[row][col].setValue(0);
            // ��յ�Ԫ��ĺ�ѡ��
            grid[row][col].clearCandidates();
        }
    }
}
// ��ȡ�����ļ�
/*
void Sudoku::readSudoku(const std::string& filename)
{
    std::ifstream infile;
    infile.open("easy.txt");
    if (!infile.is_open())
    {
        std::cerr << "�ļ�����ʧ��:" << filename << std::endl;
        return;
    }
    else
    {
        int numofboard = rand() % (15 - 1 + 1) + 1;
        int currentboard = 0;
        std::vector<int>row;//������
        while (true)
        {
            std::vector<std::vector<int>> tmp;//��ʱ���̵�����
            while (true)
            {
                char data[300];

                infile.getline(data, 300);
                if (data[0] == '-')//һ�����������
                {

                    break;
                }
                for (int i = 0;i < strlen(data);i++)
                {
                    if (('1' <= data[i] && data[i] <= '9'))
                        row.push_back(data[i] - '0');

                }
                tmp.push_back(row);//��ʽ��������
                row.clear();
            }
            if (!numofboard)
            {
                for (int i = 0; i < 9; ++i)
                {
                    for (int j = 0; j < 9; ++j)
                    {
                        grid[i][j].setValue(tmp[i][j]);  //��ֵ���õ���Ӧ�� Cell ������
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

// ���õ�Ԫ���ֵ
void Sudoku::setValue(int row, int col, int value) {
    if (row >= 0 && row < 9 && col >= 0 && col < 9) {
        grid[row][col].setValue(value);
    }
}



// �����Ѷȼ�������
/*
* void Sudoku::loadPuzzleBasedOnDifficulty(int difficulty) 
{
    int digcount=0;
    switch (difficulty)
    {
    case 1://��
        digcount = rand() % (30 - 20 + 1) + 20;
    case 2://�е�
        digcount = rand() % (40 - 30 + 1) + 30;
    case 3://����
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
        grid[x][y].addCandidate(answer);//�Ѵ�������ѡ����
        grid[x][y].setValue(0);

        int numCandidates = rand() % 8 + 1;  //���� 1 �� 8 ����ѡ��
        
        while (numCandidates)
        {
            int candidate = rand() % 9 + 1;
            if (std::find(grid[x][y].getCandidates().begin(), grid[x][y].getCandidates().end(), candidate) != grid[x][y].getCandidates().end()) {
                continue; //�����ѡ�����Ѿ����ڣ�������
            }
            grid[x][y].addCandidate(candidate);
            numCandidates--;
        }
        
        if (grid[x][y].getCandidates().size() < 9)
        {
            grid[x][y].getCandidates().resize(9, 0); // ��0���ֱ��������СΪ9
            
        }
        digcount--;
        //����������������Ψһ��solveSudoku����
        //
    }
}
*/



void Sudoku::display()
{
     printf("      C1       C2       C3       C4       C5       C6       C7       C8       C9    \n");//////////////////////��������ã���
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
                         // ����ѡ��������3x3����
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
                         WORD originalColorAttrs = consoleInfo.wAttributes; // ����ԭʼ��ɫ����

                         // �����ı���ɫΪ��ɫ
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

