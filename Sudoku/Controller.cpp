#include "Controller.h"
#include "MenuInterface.h"
void Controller ::handleInput(int option, bool& running) 
{
    switch (option) 
    {
    case 1:
        // 执行随机选题命令
        executeCommand(std::make_unique<RandomPuzzleCommand>(sudoku, ui));
        break;
    case 2:
        // 执行自定义题命令
        executeCommand(std::make_unique<CustomPuzzleCommand>(sudoku, ui));
        break;
    case 3:
        // 执行难度选择命令
        setMenu(std::make_unique<DifficultyOptionsCommand>());
        break;
    case 0:
        ui.displayMessage("退出游戏...");
        running = false;  // 退出游戏循环
        break;
    default:
        ui.displayMessage("无效选择，请输入0到3之间的数字。");
        break;
    }
}


void Controller::setMenu(UIInterface& ui, std::unique_ptr<MenuInterface> menu)
{
    ui.currentMenu = std::move(menu);
    ui.currentMenu->displayMenu();
}

void Controller::executeCommand(std::unique_ptr<Command> command) 
{
    command->execute();  // 执行具体命令
    updateUI();          // 命令执行完毕后更新UI
}

void Controller::updateUI() 
{
    ui.displayGrid(sudoku);  // 更新数独网格
}
