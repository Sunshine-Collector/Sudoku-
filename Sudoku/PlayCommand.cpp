#include "Command.h"
#include "CommandTool.h"
void PlayCommand::execute()
{
    std::cin.ignore(1); //忽略一个换行符
    bool gameRunning = true;
    while (gameRunning) {
        std::string input = ui.getInput();
        auto command = CommandParser::parseCommand(input, sudoku, ui, initialsudoku, tmpsudoku);  //解析命令
        if (input == "exit") {
            gameRunning = false;  //退出游戏循环
        }
        else {
            if (command) {
                command->execute();  //执行解析到的命令
            }
            else {
                ui.displayMessage("无效指令，请输入有效的指令或输入 help 获取帮助。");
            }
        }
    }
}
