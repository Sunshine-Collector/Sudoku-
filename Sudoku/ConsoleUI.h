#pragma once
#include "UIInterface.h"
#include <iostream>
#include <string>
#include <vector>
#include "UIInterface.h"
#include"SudokuPlayer.h"
class ConsoleUI : public UIInterface 
{
public:
    // 显示提示信息
    void displayMessage(const std::string& message) override 
    {
        std::cout << message << std::endl;
    }

    // 显示游戏网格
    void displayGrid(Sudoku& sudoku) override
    {
        sudoku.display();
        //这里用sudoku的方法，有失独立性，仅为了方便功能展示。
        //未来如果想改成其他display的格式，就通过对sudoku.getValue等函数来输出。这样更合理,因为 输出成怎样的格式 要由UI来决定
        //sudoku只提供数据
    }
    // 从用户获取输入
    std::string getInput() override 
    {
        std::string input;
        std::cout << "请输入指令: ";
        //input.clear();
        //std::cin >> input;
        std::getline(std::cin, input);
        return input;
    }
    void displaySolutions(Board& board)
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

  
    // 展示当前菜单
    void displayMenu() override 
    {
        if (currentMenu) 
        {
            currentMenu->displayMenu();
        }
        else 
        {
            std::cout << "没有可用的菜单..." << std::endl;
        }
    }

};

