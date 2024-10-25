#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include "UIInterface.h"
#include "Sudoku.h"
#include "MenuInterface.h"
#include "Command.h"


class Controller {
public:
    Controller(UIInterface& uiRef, Sudoku& sudokuRef)
        : ui(uiRef), sudoku(sudokuRef) {}

    virtual ~Controller() = default; 

    // �����û����벢ִ����Ӧ������
    virtual void handleInput(int option, bool& running) = 0;//���麯����������
    //�����߱����������������һ�����麯�������������������������һ�������ࡣ
    //����ʵ��������࣬��ֻ����Ϊ������ʹ�á�
                                                        
    // ���ò˵�
    virtual void setMenu(UIInterface&ui,std::unique_ptr<MenuInterface> menu) = 0;

    // ִ������
    virtual void executeCommand(std::unique_ptr<Command> command) = 0;
    
    // ���� UI
    virtual void updateUI() = 0;

protected:  //����ɷ��ʣ���粻��
    UIInterface& ui;  //��ǰ����״̬
    Sudoku& sudoku;   //��ǰ����״̬
};



class ConsoleController : public Controller //����̨������
{
public:
    ConsoleController(UIInterface& uiRef, Sudoku& sudokuRef)
        : Controller(uiRef, sudokuRef) {}

    void handleInput(int option, bool& running) 
    {
        
        switch (option)
            {
        case 1:
            // ִ�����ѡ������
            executeCommand(std::make_unique<RandomPuzzleCommand>(sudoku, ui));
            break;
        case 2:
            // ִ�а����ѡ������
            executeCommand(std::make_unique<SelectPuzzleCommand>(sudoku, ui));
            break;
        case 3:
            // ִ���Զ���������
            executeCommand(std::make_unique<CustomPuzzleCommand>(sudoku, ui));
            break;
        case 4:
        {
            // ִ������浵����
            std::string savefile= "randomsave.txt";
            //std::cout << "������浵�ļ��������磺randomsave.txt��: ";
            //savefile = ui.getInput(); // ��ȡ�û�����Ĵ浵�ļ���
            TxtPuzzleLoader loader;   //��һ���н���ռ䣬���Լ�һ��ѡ����ʲô��������
            executeCommand(std::make_unique<LoadCommand>(sudoku, ui, loader, savefile));
            break;
        }
        case 5:
        {
            std::string savefile = "game.txt";
            TxtPuzzleLoader loader;
            executeCommand(std::make_unique<GeneratePuzzleCommand>(sudoku, ui, loader, savefile));
        }
        case 0:
            ui.displayMessage("�˳���Ϸ...");
            running = false;  // �˳���Ϸѭ��
            break;
        default:
            ui.displayMessage("��Чѡ��������0��5֮������֡�");
            break;
            }
        
    }

    void setMenu(UIInterface &ui,std::unique_ptr<MenuInterface> menu) override {
        ui.currentMenu = std::move(menu);
        //if (ui.currentMenu) printf("Yes");
    }

    void executeCommand(std::unique_ptr<Command> command) override {
        command->execute();  // ִ�о�������
    }

    void updateUI() override 
    {
        ui.displayGrid(sudoku);  // ������������
    }
};





#endif // CONTROLLER_H
