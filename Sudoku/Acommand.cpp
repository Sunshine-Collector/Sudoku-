#pragma once
#include "Acommand.h"
// 命令工厂
class CommandFactory //如果以后新增指令：1.新写一个command 2.命令工厂搞一下   其他地方都不用动
{
public:
    static std::unique_ptr<Command> createCommand(const std::string& input, Sudoku& sudoku, UIInterface& ui, Sudoku initialsudoku, Sudoku& tmpsudoku) {
        // 通过命令类型创建对应的 Command 对象
        if (input == "help") {
            return std::make_unique<HelpCommand>(sudoku, ui);
        }
        else if (input == "save") {
            TxtPuzzleLoader loader; //记录当前进度
            return std::make_unique<SaveCommand>(sudoku, ui, loader, "randomsave.txt");
        }
        else if (input == "auto") {
            return std::make_unique<AutoCommand>(sudoku, ui);
        }
        else if (input.rfind("set", 0) == 0) {
            return std::make_unique<SetCommand>(sudoku, ui, input);  // 解析并处理 `set` 指令
        }
        else if (input.rfind("rm", 0) == 0) {
            return std::make_unique<RemoveCommand>(sudoku, ui, input);  // 解析并处理 `rm` 指令
        }
        else if (input == "replay") {
            return std::make_unique<ReplayCommand>(sudoku, ui, initialsudoku);  // 处理 `replay` 可能需要在 PlayCommand 内部重置游戏状态
        }
        else if (input == "back") {
            return std::make_unique<BackCommand>(sudoku, ui, tmpsudoku);  // 处理 `back` 可能需要额外的状态记录
        }
        else if (input == "over") {
            bool gameRunning = true;
            return std::make_unique<OverCommand>(sudoku, ui, gameRunning);  // 传入游戏状态
        }
        else if (input == "record") {
            return std::make_unique<RecordCommand>(sudoku, ui, tmpsudoku);  // 处理 `record` 可能需要额外的状态记录
        }
        else {
            ui.displayMessage("无效指令，请输入有效的指令或输入 help 获取帮助。");
        }

        return nullptr;  // 无效输入返回空指针
    }
};

// 命令解析器
class CommandParser
{
public:
    static std::unique_ptr<Command> parseCommand(const std::string& input, Sudoku& sudoku, UIInterface& ui, Sudoku initialsudoku, Sudoku& tmpsudoku) {

        return CommandFactory::createCommand(input, sudoku, ui, initialsudoku, tmpsudoku);  // 用工厂创建命令
    }
};



//命令组织器
class CompositeCommand : public Command
{
public:
    // 添加命令
    void addCommand(std::unique_ptr<Command> cmd) {
        commands.push_back(std::move(cmd));
    }//如果不用move，可能发生拷贝构造，资源复制。
     //用move，为移动构造，资源转移。
     //这里的设计是想让command的资源转移到容器中，所有权归容器管。


    void execute() override
    {
        for (auto& cmd : commands) {
            cmd->execute();  // 执行每个子命令
        }
    }

private:
    std::vector<std::unique_ptr<Command>> commands;  // 存储多个命令

    //1.动态管理内存，避免手动管理
    //2.多态(避免对象切割)

};