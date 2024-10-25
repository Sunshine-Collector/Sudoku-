#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <map>
using namespace std;
const int N = 9;
typedef vector<vector<char>> Board;



class SudokuPlayer
{
private:
    // 使用位运算来表示某个数是否出现过
    int rowUsed[N];
    int columnUsed[N];
    int blockUsed[N];

public:
    vector<Board> result;
    vector<pair<int, int> > spaces;//挖空坐标

public:
    SudokuPlayer()
    {
        initState();
    }

    void initState()
    {
        memset(rowUsed, 0, sizeof(rowUsed));
        memset(columnUsed, 0, sizeof(columnUsed));
        memset(blockUsed, 0, sizeof(blockUsed));
        spaces.clear();
        result.clear();
    }

    void addResult(Board& board)
    {
        vector<vector<char> > obj(board);
        result.push_back(obj);
    }

    void flip(int i, int j, int digit)
    {
        rowUsed[i] ^= (1 << digit);
        columnUsed[j] ^= (1 << digit);
        blockUsed[(i / 3) * 3 + j / 3] ^= (1 << digit);
    }

    vector<Board> solveSudoku(Board board)
    {
        initState();
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (board[i][j] == '0')
                {
                    spaces.push_back(pair<int, int>(i, j));
                }
                else
                {
                    int digit = board[i][j] - '1';
                    flip(i, j, digit);
                }
            }
        }
        DFS(board, 0);
        return result;
    }

    void DFS(Board& board, int pos)
    {
        if (pos == spaces.size())
        {
            addResult(board);
            return;
        }
        int i = spaces[pos].first;
        int j = spaces[pos].second;
        int mask = ~(rowUsed[i] | columnUsed[j] | blockUsed[(i / 3) * 3 + j / 3]) & 0x1ff;
        int digit = 0;
        while (mask)
        {
            if (mask & 1)
            {
                flip(i, j, digit);
                board[i][j] = '1' + digit;
                DFS(board, pos + 1);
                flip(i, j, digit);
            }
            mask = mask >> 1;
            digit++;
        }
    }

    void getResult()
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            Board board = result[i];
            printBoard(board);
        }
    }

    bool checkBoard(Board& board)
    {
        initState();
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] != '0')
                {
                    int digit = board[i][j] - '1';
                    if ((rowUsed[i] | columnUsed[j] | blockUsed[(i / 3) * 3 + j / 3]) & (1 << digit))
                    {
                        return false;
                    }
                    flip(i, j, digit);
                }
            }
        }
        return true;
    }

    void printBoard(Board& board)
    {
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                cout << board[i][j] << " ";
            }
            cout << "\n";
        }
    }

    Board generateBoard(int digCount)
    {
        vector<vector<char> > board(N, vector<char>(N, '0'));
        vector<int> row = getRand9();
        for (int i = 0; i < 3; i++)
        {
            board[3][i + 3] = row[i] + '1';
            board[4][i + 3] = row[i + 3] + '1';
            board[5][i + 3] = row[i + 6] + '1';
        }
        copySquare(board, 3, 3, true);
        copySquare(board, 3, 3, false);
        copySquare(board, 3, 0, false);
        copySquare(board, 3, 6, false);

        while (digCount)
        {
            int x = rand() % 9;
            int y = rand() % 9;
            if (board[x][y] == '0')
                continue;
            char tmp = board[x][y];
            board[x][y] = '0';

            solveSudoku(board);
            if (result.size() == 1)
            {
                digCount--;
            }
            else
            {
                board[x][y] = tmp;
            }
        }
        // printBoard(board);
        // cout << "spaces " << player.spaces.size() << "\n";
        if (!checkBoard(board))
        {
            cout << "wrong board" << endl;
        }

        return board;
    }

    vector<int> getRand9()
    {
        vector<int> result;
        int digit = 0;
        while (result.size() != 9)
        {
            int num = rand() % 9;
            if ((1 << num) & digit)
            {
                continue;
            }
            else
            {
                result.push_back(num);
                digit ^= (1 << num);
            }
        }
        return result;
    }

    void copySquare(Board& board, int src_x, int src_y, bool isRow)
    {
        int rand_tmp = rand() % 2 + 1;
        int order_first[3] = { 1, 2, 0 };
        int order_second[3] = { 2, 0, 1 };
        if (rand_tmp == 2)
        {
            order_first[0] = 2;
            order_first[1] = 0;
            order_first[2] = 1;
            order_second[0] = 1;
            order_second[1] = 2;
            order_second[2] = 0;
        }
        for (int i = 0; i < 3; i++)
        {
            if (isRow)
            {
                board[src_x][i] = board[src_x + order_first[0]][src_y + i];
                board[src_x + 1][i] = board[src_x + order_first[1]][src_y + i];
                board[src_x + 2][i] = board[src_x + order_first[2]][src_y + i];
                board[src_x][i + 6] = board[src_x + order_second[0]][src_y + i];
                board[src_x + 1][i + 6] = board[src_x + order_second[1]][src_y + i];
                board[src_x + 2][i + 6] = board[src_x + order_second[2]][src_y + i];
            }
            else
            {
                board[i][src_y] = board[src_x + i][src_y + order_first[0]];
                board[i][src_y + 1] = board[src_x + i][src_y + order_first[1]];
                board[i][src_y + 2] = board[src_x + i][src_y + order_first[2]];
                board[i + 6][src_y] = board[src_x + i][src_y + order_second[0]];
                board[i + 6][src_y + 1] = board[src_x + i][src_y + order_second[1]];
                board[i + 6][src_y + 2] = board[src_x + i][src_y + order_second[2]];
            }
        }
    }



    vector<Board> readFile(string filePath)
    {
        ifstream infile;
        vector<Board> boards;
        infile.open(filePath);
        char data[100];
        Board tmp;
        vector<char> row;
        while (!infile.eof())
        {
            infile.getline(data, 100);
            if (data[0] == '-')
            {
                boards.push_back(Board(tmp));
                tmp.clear();
                continue;
            }
            for (int i = 0; i < strlen(data); i++)
            {
                if (('1' <= data[i] && data[i] <= '9') || data[i] == '0')
                {
                    row.push_back(data[i]);
                }
            }
            tmp.push_back(vector<char>(row));
            row.clear();
        }
        infile.close();
        return boards;
    }

    void writeFile(vector<Board> boards, ofstream& f)
    {
        for (int k = 0; k < boards.size(); k++)
        {
            for (int i = 0; i < boards[k].size(); i++)
            {
                for (int j = 0; j < boards[k][i].size(); j++)
                {
                    f << boards[k][i][j] << " ";
                }
                f << "\n";
            }
            f << "------- " << k << " -------" << endl;
        }
    }

    void generateGame(int gameNumber, int gameLevel, vector<int> digCount, ofstream& outfile, SudokuPlayer& player)
    {
        for (int i = 0; i < gameNumber; i++)
        {
            int cnt = 0;
            if (digCount.size() == 1)
            {
                cnt = digCount[0];
            }
            else
            {
                cnt = rand() % (digCount[1] - digCount[0] + 1) + digCount[0];
            }
            Board b = player.generateBoard(cnt);
            vector<Board> bs;
            bs.push_back(b);
            writeFile(bs, outfile);
        }
        outfile.close();
    }
};