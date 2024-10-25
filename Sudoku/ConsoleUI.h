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
    // ��ʾ��ʾ��Ϣ
    void displayMessage(const std::string& message) override 
    {
        std::cout << message << std::endl;
    }

    // ��ʾ��Ϸ����
    void displayGrid(Sudoku& sudoku) override
    {
        sudoku.display();
        //������sudoku�ķ�������ʧ�����ԣ���Ϊ�˷��㹦��չʾ��
        //δ�������ĳ�����display�ĸ�ʽ����ͨ����sudoku.getValue�Ⱥ��������������������,��Ϊ ����������ĸ�ʽ Ҫ��UI������
        //sudokuֻ�ṩ����
    }
    // ���û���ȡ����
    std::string getInput() override 
    {
        std::string input;
        std::cout << "������ָ��: ";
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

  
    // չʾ��ǰ�˵�
    void displayMenu() override 
    {
        if (currentMenu) 
        {
            currentMenu->displayMenu();
        }
        else 
        {
            std::cout << "û�п��õĲ˵�..." << std::endl;
        }
    }

};

