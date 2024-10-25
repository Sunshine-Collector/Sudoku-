#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H
#include "Sudoku.h" // 引入Sudoku类的定义
#include "MenuInterface.h"
#include"SudokuPlayer.h"
/// <summary>
/// 使用策略模式解耦显示逻辑
/// </summary>
class UIInterface {
public:
    virtual ~UIInterface() = default;

    // 显示信息
    virtual void displayMessage(const std::string& message) = 0;

    // 显示游戏网格
    virtual void displayGrid(Sudoku &suduku) = 0;

    // 从用户获取输入
    virtual std::string getInput() = 0;

    virtual void displayMenu() = 0;
    virtual void displaySolutions(Board& board) = 0;
    std::unique_ptr<MenuInterface> currentMenu;  // 当前菜单

};



#endif 
