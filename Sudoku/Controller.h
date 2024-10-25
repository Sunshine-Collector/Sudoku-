#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include "UIInterface.h"
#include "Sudoku.h"
#include "MenuInterface.h"
#include "Command.h"


class Controller {
public:
    Controller(UIInterface& uiRef, Sudoku& sudokuRef)
        : ui(uiRef), sudoku(sudokuRef) {}

    virtual ~Controller() = default; 

    // 处理用户输入并执行相应的命令
    virtual void handleInput(int option, bool& running) = 0;//纯虚函数的声明。
    //它告诉编译器，这个函数是一个纯虚函数，包含这个函数声明的类是一个抽象类。
    //不能实例化这个类，它只能作为基类来使用。
                                                        
    // 设置菜单
    virtual void setMenu(UIInterface&ui,std::unique_ptr<MenuInterface> menu) = 0;

    // 执行命令
    virtual void executeCommand(std::unique_ptr<Command> command) = 0;
    
    // 更新 UI
    virtual void updateUI() = 0;

protected:  //子类可访问，外界不可
    UIInterface& ui;  //当前界面状态
    Sudoku& sudoku;   //当前数独状态
};



class ConsoleController : public Controller //命令台控制器
{
public:
    ConsoleController(UIInterface& uiRef, Sudoku& sudokuRef)
        : Controller(uiRef, sudokuRef) {}

    void handleInput(int option, bool& running) 
    {
        
        switch (option)
            {
        case 1:
            // 执行随机选题命令
            executeCommand(std::make_unique<RandomPuzzleCommand>(sudoku, ui));
            break;
        case 2:
            // 执行按题号选题命令
            executeCommand(std::make_unique<SelectPuzzleCommand>(sudoku, ui));
            break;
        case 3:
            // 执行自定义题命令
            executeCommand(std::make_unique<CustomPuzzleCommand>(sudoku, ui));
            break;
        case 4:
        {
            // 执行载入存档命令
            std::string savefile= "randomsave.txt";
            //std::cout << "请输入存档文件名（例如：randomsave.txt）: ";
            //savefile = ui.getInput(); // 获取用户输入的存档文件名
            TxtPuzzleLoader loader;   //这一步有解耦空间，可以加一个选择用什么加载器类
            executeCommand(std::make_unique<LoadCommand>(sudoku, ui, loader, savefile));
            break;
        }
        case 5:
        {
            std::string savefile = "game.txt";
            TxtPuzzleLoader loader;
            executeCommand(std::make_unique<GeneratePuzzleCommand>(sudoku, ui, loader, savefile));
        }
        case 0:
            ui.displayMessage("退出游戏...");
            running = false;  // 退出游戏循环
            break;
        default:
            ui.displayMessage("无效选择，请输入0到5之间的数字。");
            break;
            }
        
    }

    void setMenu(UIInterface &ui,std::unique_ptr<MenuInterface> menu) override {
        ui.currentMenu = std::move(menu);
        //if (ui.currentMenu) printf("Yes");
    }

    void executeCommand(std::unique_ptr<Command> command) override {
        command->execute();  // 执行具体命令
    }

    void updateUI() override 
    {
        ui.displayGrid(sudoku);  // 更新数独网格
    }
};





#endif // CONTROLLER_H
