#include "Controller.h"
#include "MenuInterface.h"
void Controller ::handleInput(int option, bool& running) 
{
    switch (option) 
    {
    case 1:
        // ִ�����ѡ������
        executeCommand(std::make_unique<RandomPuzzleCommand>(sudoku, ui));
        break;
    case 2:
        // ִ���Զ���������
        executeCommand(std::make_unique<CustomPuzzleCommand>(sudoku, ui));
        break;
    case 3:
        // ִ���Ѷ�ѡ������
        setMenu(std::make_unique<DifficultyOptionsCommand>());
        break;
    case 0:
        ui.displayMessage("�˳���Ϸ...");
        running = false;  // �˳���Ϸѭ��
        break;
    default:
        ui.displayMessage("��Чѡ��������0��3֮������֡�");
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
    command->execute();  // ִ�о�������
    updateUI();          // ����ִ����Ϻ����UI
}

void Controller::updateUI() 
{
    ui.displayGrid(sudoku);  // ������������
}
