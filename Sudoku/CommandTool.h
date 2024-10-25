#pragma once
#include "UIInterface.h"
#include "Sudoku.h"
#include <string>
#include "MenuInterface.h"
#include "PuzzleLoaderInterface.h"
#include <sstream>
#include <iostream>
#include <regex>
#include "Command.h"
// �����
class CommandFactory //����Ժ�����ָ�1.��дһ��command 2.�������һ��   �����ط������ö�
{
public:
    static std::unique_ptr<Command> createCommand(const std::string& input, Sudoku& sudoku, UIInterface& ui, Sudoku initialsudoku, Sudoku& tmpsudoku) {
        // ͨ���������ʹ�����Ӧ�� Command ����
        if (input == "help") {
            return std::make_unique<HelpCommand>(sudoku, ui);
        }
        else if (input == "save") {
            TxtPuzzleLoader loader;
            loader.clear("randomsave.txt");
            return std::make_unique<SaveCommand>(sudoku, ui,  "randomsave.txt");
        }
        else if (input == "auto") {
            return std::make_unique<AutoCommand>(sudoku, ui);
        }
        else if (input.rfind("set", 0) == 0) {
            return std::make_unique<SetCommand>(sudoku, ui, input, initialsudoku);  // ���������� `set` ָ��
        }
        else if (input.rfind("rm", 0) == 0) {
            return std::make_unique<RemoveCommand>(sudoku, ui, input);  // ���������� `rm` ָ��
        }
        else if (input == "replay") {
            return std::make_unique<ReplayCommand>(sudoku, ui, initialsudoku);  // ���� `replay` ������Ҫ�� PlayCommand �ڲ�������Ϸ״̬
        }
        else if (input == "back") {
            return std::make_unique<BackCommand>(sudoku, ui, tmpsudoku);  // ���� `back` ������Ҫ�����״̬��¼
        }
        else if (input == "over") {
            return std::make_unique<OverCommand>(sudoku, ui);  // ������Ϸ״̬
        }
        else if (input == "record") {
            return std::make_unique<RecordCommand>(sudoku, ui, tmpsudoku);  // ���� `record` ������Ҫ�����״̬��¼
        }

        return nullptr;  // ��Ч���뷵�ؿ�ָ��
    }
};

// ���������
class CommandParser
{
public:
    static std::unique_ptr<Command> parseCommand(const std::string& input, Sudoku& sudoku, UIInterface& ui, Sudoku initialsudoku, Sudoku& tmpsudoku) {

        return CommandFactory::createCommand(input, sudoku, ui, initialsudoku, tmpsudoku);  // �ù�����������
    }
};


//������֯��
class CompositeCommand : public Command
{
public:
    // �������
    void addCommand(std::unique_ptr<Command> cmd) {
        commands.push_back(std::move(cmd));
    }//�������move�����ܷ����������죬��Դ���ơ�
     //��move��Ϊ�ƶ����죬��Դת�ơ�
     //��������������command����Դת�Ƶ������У�����Ȩ�������ܡ�


    void execute() override
    {
        for (auto& cmd : commands) {
            cmd->execute();  // ִ��ÿ��������
        }
    }

private:
    std::vector<std::unique_ptr<Command>> commands;  // �洢�������

    //1.��̬�����ڴ棬�����ֶ�����
    //2.��̬(��������и�)

};

