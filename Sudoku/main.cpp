#include "UIInterface.h"
#include "ConsoleUI.h"
#include "Controller.h"
#include "Sudoku.h"
#include "MenuInterface.h"
#include <string>
int main() {
    // ����������Ϸ�ĺ����߼�ģ��
    Sudoku sudoku;
    // ����UI����
    ConsoleUI ui;
    //��������������������ģ�ͺ�UI
    ConsoleController controller(ui, sudoku);
    //����һ��MainMenu���͵��¶���,����һ��ָ��ö����std::unique_ptr,mainMenu�����MainMenu�����Ψһ�����ߡ�
    std::unique_ptr<MenuInterface> mainMenu = std::make_unique<MainMenu>();
    // ���˵����ص�UI�У���UI����ʹ�ò˵���
    controller.setMenu(ui, std::move(mainMenu));



    bool running = true;
    int option;
    // ������Ϸѭ��
    while (running)
    {
        sudoku.initialize();//���ģ��������
        ui.displayMenu();  //��ʾ��ǰ�˵��˵�
        std::cin >> option;//option = atoi(ui.getinput());
        controller.handleInput(option, running);  //�����������û�ѡ��
    }

    return 0;
}
