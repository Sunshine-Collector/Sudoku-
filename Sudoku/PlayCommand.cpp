#include "Command.h"
#include "CommandTool.h"
void PlayCommand::execute()
{
    std::cin.ignore(1); //����һ�����з�
    bool gameRunning = true;
    while (gameRunning) {
        std::string input = ui.getInput();
        auto command = CommandParser::parseCommand(input, sudoku, ui, initialsudoku, tmpsudoku);  //��������
        if (input == "exit") {
            gameRunning = false;  //�˳���Ϸѭ��
        }
        else {
            if (command) {
                command->execute();  //ִ�н�����������
            }
            else {
                ui.displayMessage("��Чָ���������Ч��ָ������� help ��ȡ������");
            }
        }
    }
}
