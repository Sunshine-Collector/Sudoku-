#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H
#include "Sudoku.h" // ����Sudoku��Ķ���
#include "MenuInterface.h"
#include"SudokuPlayer.h"
/// <summary>
/// ʹ�ò���ģʽ������ʾ�߼�
/// </summary>
class UIInterface {
public:
    virtual ~UIInterface() = default;

    // ��ʾ��Ϣ
    virtual void displayMessage(const std::string& message) = 0;

    // ��ʾ��Ϸ����
    virtual void displayGrid(Sudoku &suduku) = 0;

    // ���û���ȡ����
    virtual std::string getInput() = 0;

    virtual void displayMenu() = 0;
    virtual void displaySolutions(Board& board) = 0;
    std::unique_ptr<MenuInterface> currentMenu;  // ��ǰ�˵�

};



#endif 
