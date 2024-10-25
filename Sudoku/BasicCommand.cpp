#include "BasicCommand.h"

void PlayCommand::execute()
{
    std::cin.ignore(1);  // 忽略换行符
    bool gameRunning = true;
    while (gameRunning) {
        std::string input = ui.getInput();  // 获取用户输入
        auto command = CommandParser::parseCommand(input, sudoku, ui, initialsudoku, tmpsudoku);  //解析命令

        if (command) {
            command->execute();  // 执行解析到的命令
        }
        else if (input == "exit") {
            gameRunning = false;  // 退出游戏循环
        }
        else {
            ui.displayMessage("无效指令，请输入有效的指令或输入 help 获取帮助。");
        }
    }
}