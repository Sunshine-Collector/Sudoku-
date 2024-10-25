#include "UIInterface.h"
#include "ConsoleUI.h"
#include "Controller.h"
#include "Sudoku.h"
#include "MenuInterface.h"
#include <string>
int main() {
    // 创建数独游戏的核心逻辑模型
    Sudoku sudoku;
    // 创建UI对象
    ConsoleUI ui;
    //创建控制器，传入数独模型和UI
    ConsoleController controller(ui, sudoku);
    //创建一个MainMenu类型的新对象,返回一个指向该对象的std::unique_ptr,mainMenu是这个MainMenu对象的唯一所有者。
    std::unique_ptr<MenuInterface> mainMenu = std::make_unique<MainMenu>();
    // 将菜单加载到UI中，供UI后续使用菜单。
    controller.setMenu(ui, std::move(mainMenu));



    bool running = true;
    int option;
    // 启动游戏循环
    while (running)
    {
        sudoku.initialize();//清除模型中数据
        ui.displayMenu();  //显示当前菜单菜单
        std::cin >> option;//option = atoi(ui.getinput());
        controller.handleInput(option, running);  //控制器处理用户选择
    }

    return 0;
}
