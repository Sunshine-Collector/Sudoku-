#include "BasicCommand.h"

void PlayCommand::execute()
{
    std::cin.ignore(1);  // ���Ի��з�
    bool gameRunning = true;
    while (gameRunning) {
        std::string input = ui.getInput();  // ��ȡ�û�����
        auto command = CommandParser::parseCommand(input, sudoku, ui, initialsudoku, tmpsudoku);  //��������

        if (command) {
            command->execute();  // ִ�н�����������
        }
        else if (input == "exit") {
            gameRunning = false;  // �˳���Ϸѭ��
        }
        else {
            ui.displayMessage("��Чָ���������Ч��ָ������� help ��ȡ������");
        }
    }
}