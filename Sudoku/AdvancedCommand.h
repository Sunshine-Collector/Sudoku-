#pragma once
#include "UIInterface.h"
#include "Sudoku.h"
#include <string>
#include "MenuInterface.h"
#include "PuzzleLoaderInterface.h"
#include <sstream>
#include <iostream>
#include <regex>
#include "BasicCommand.h"
/*
* ��save setvalue���ֶ������ıȽϻ��������ݲ�������ֱ����suduku������
��auto������Ҫ��ѡ�������Ҫsetvalue�͵������command��д�߼���
Ҳ����˵�Ժ���չ��command��һЩ���Ӳ���������sudukuһЩ�������ݲ����ϳɵģ�
��������command��������Ϻ�����Ե��߼�
*/
class Command
{
public:
    virtual ~Command() = default;
    virtual void execute() = 0;  // ÿ�������඼����ʵ���������
};



class AddCandidateCommand : public Command   //����ѡ��
{
public:
    AddCandidateCommand(Sudoku& sudokuRef)
        : sudoku(sudokuRef) {}

    void execute() override
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                for (int k = 1; k <= 9; k++)
                {
                    sudoku.getCell(i, j).addCandidate(k);
                }
            }
        }
        for (int row = 0; row < 9; ++row)
        {
            for (int col = 0; col < 9; ++col)
            {
                int value = sudoku.getCell(row, col).getValue();
                if (value != 0)
                {
                    // �����Ԫ���ѱ����룬���Ƴ�ͬһ�С�ͬһ�к�ͬһ����ĺ�ѡ��
                    for (int col_1 = 0; col_1 < 9; ++col_1)
                    {
                        sudoku.getCell(row, col_1).removeCandidate(value);
                    }
                    for (int row_1 = 0; row_1 < 9; ++row_1)
                    {
                        sudoku.getCell(row_1, col).removeCandidate(value);
                    }
                    int boxStartRow = row - row % 3;
                    int boxStartCol = col - col % 3;
                    for (int i = 0; i < 3; ++i)
                    {
                        for (int j = 0; j < 3; ++j)
                        {
                            sudoku.getCell(boxStartRow + i, boxStartCol + j).removeCandidate(value);
                        }
                    }
                }
            }
        }
    }

private:
    Sudoku& sudoku;  // Ŀ������ʵ��
};



class LoadCommand : public Command //�����ϴν���
{
private:   //LoadCommandӵ�У�ģ�� ���� �ļ�·�� ������
    Sudoku& sudoku;
    UIInterface& ui;
    PuzzleLoaderInterface& storage;  // �ļ���д�ӿ�
    std::string filename;

public:
    LoadCommand(Sudoku& sudokuRef, UIInterface& uiRef, PuzzleLoaderInterface& storageRef, const std::string& filenameRef)
        : sudoku(sudokuRef), ui(uiRef), storage(storageRef), filename(filenameRef) {}

    void execute() override
    {
        //����������Ϸ����
        storage.load(sudoku, filename, 0);
        ui.displayMessage("�ϴ���Ϸ�����Ѵ� " + filename + " ����.");


        // ������С�������μ��뵽���������
        AddCandidateCommand AddCandidateCommand(sudoku);
        AddCandidateCommand.execute();
        ui.displayGrid(sudoku);  // ����UI��ʾ���غ����������
        ui.displayMessage("�ϴ���Ϸ�����Ѵ� " + filename + " ����.");
        PlayCommand PlayCommand(sudoku, ui);
        PlayCommand.execute();

        //����UI
        ui.displayGrid(sudoku);
    }
};



class AutoCommand : public Command  //�Զ�����
{
private:
    Sudoku& sudoku;
    UIInterface& ui;

public:
    AutoCommand(Sudoku& sudokuRef, UIInterface& uiRef)
        : sudoku(sudokuRef), ui(uiRef) {}

    void execute() override {


        bool changed = false;
        // ����������ÿ������
        for (int row = 0; row < 9; ++row)
        {
            for (int col = 0; col < 9; ++col)
            {

                Cell& cell = sudoku.getCell(row, col);
                int isright = 0;
                // ����ø���Ϊ�գ�value Ϊ 0�����Һ�ѡ��ֻ��һ����Ϊ��1
                for (size_t i = 0; i < cell.getcandidates().size(); ++i)
                {
                    if (cell.getcandidates()[i] != 0)
                    {
                        isright++;
                    }
                }
                if (cell.getValue() == 0 && isright == 1) {
                    // ��Ψһ��ѡ������Ϊ�ø��ӵ�ֵ
                    for (size_t i = 0; i < cell.getcandidates().size(); ++i)
                    {
                        if (cell.getcandidates()[i] != 0)
                        {
                            cell.setValue(cell.getcandidates()[i]);
                            cell.removeCandidate(cell.getcandidates()[i]);  // ��պ�ѡ��
                        }
                    }
                    changed = true;
                }
            }
        }
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                sudoku.getCell(row, col).clearCandidates();
            }
        }
        AddCandidateCommand AddCandidateCommand(sudoku);
        AddCandidateCommand.execute();
        // ������
        if (changed) {
            ui.displayMessage("�Զ��������...");
        }
        else {
            ui.displayMessage("û�п����Զ������ĵ�Ԫ...");
        }

        // ��ʾ���º����������
        ui.displayGrid(sudoku);
    }
};



class ReplayCommand : public Command //�����ϴν���
{
private:   //LoadCommandӵ�У�ģ�� ���� �ļ�·�� ������
    Sudoku& sudoku;
    UIInterface& ui;
    Sudoku initialsudoku;

public:
    ReplayCommand(Sudoku& sudokuRef, UIInterface& uiRef, Sudoku initialsudoku)
        : sudoku(sudokuRef), ui(uiRef), initialsudoku(sudokuRef) {}

    void execute() override
    {
        sudoku = initialsudoku;
        ui.displayMessage("�����¿�ʼ����");
        ui.displayGrid(sudoku);  // ��ʾ���ú������
    }
};

class DigPuzzleCommand : public Command   //ѡ���Ѷ�
{
public:
    DigPuzzleCommand(Sudoku& sudokuRef, int difficultyLevel)
        : sudoku(sudokuRef), difficulty(difficultyLevel) {}

    void execute() override
    {
        int digcount = 0;
        switch (difficulty) {
        case 1:  // ��
            digcount = rand() % (30 - 20 + 1) + 20;
            break;
        case 2:  // �е�
            digcount = rand() % (40 - 30 + 1) + 30;
            break;
        case 3:  // ����
            digcount = rand() % (50 - 40 + 1) + 40;
            break;
        default:
            std::cerr << "��Ч���Ѷȼ���" << std::endl;
            return;
        }

        while (digcount) {
            int x = rand() % 9;
            int y = rand() % 9;

            if (sudoku.getCell(x, y).getValue() == 0) continue;

            int answer = sudoku.getCell(x, y).getValue();
            sudoku.getCell(x, y).setValue(0);  // �ڿ�


            digcount--;
            // ���ڴ˴�����Ψһ�����߼����� solveSudoku
        }
        AddCandidateCommand AddCandidateCommand(sudoku);
        AddCandidateCommand.execute();
    }

private:
    Sudoku& sudoku;  // Ŀ������ʵ��
    int difficulty;  // �ڿյ��Ѷ�
};

class SetCommand : public Command //set ����
{
private:
    Sudoku& sudoku;
    UIInterface& ui;
    std::string input;

public:
    SetCommand(Sudoku& sudokuRef, UIInterface& uiRef, const std::string& inputCommand)
        : sudoku(sudokuRef), ui(uiRef), input(inputCommand) {}

    void execute() override {



        // ���� `set RxCy=z` �� `set xy=z`
        int row, col, value;
        std::regex pattern(R"(set\s*R?\s*(\d+)\s*C?\s*(\d+)\s*=\s*(\d+))");
        std::smatch match;
        if (std::regex_match(input, match, pattern)) {
            row = std::stoi(match[1].str());
            col = std::stoi(match[2].str());
            value = std::stoi(match[3].str());
            // У�����з�Χ
            if (row >= 1 && row <= 9 && col >= 1 && col <= 9 && value >= 1 && value <= 9) {
                sudoku.setValue(row - 1, col - 1, value);  // ����ֵ��ת����0����
                ui.displayMessage("����R" + std::to_string(row) + "C" + std::to_string(col) + "Ϊ" + std::to_string(value) + "�ɹ�!");
                for (int row = 0; row < 9; ++row) {
                    for (int col = 0; col < 9; ++col) {
                        sudoku.getCell(row, col).clearCandidates();
                    }
                }
                AddCandidateCommand AddCandidateCommand(sudoku);
                AddCandidateCommand.execute();
            }
            else {
                ui.displayMessage("����ֵ������Χ��");
            }
        }
        else {
            ui.displayMessage("ָ���ʽ����");
        }

        // ��ʾ���º����������
        ui.displayGrid(sudoku);
    }
};

class RemoveCommand : public Command  //rm �Ƴ���ѡ��
{
private:
    Sudoku& sudoku;
    UIInterface& ui;
    std::string input;

public:
    RemoveCommand(Sudoku& sudokuRef, UIInterface& uiRef, const std::string& inputCommand)
        : sudoku(sudokuRef), ui(uiRef), input(inputCommand) {}

    void execute() override {
        // ���� `rm RxCy=z` �� `rm xy=z`
        int row, col, i = 0;
        std::vector<int> buffer;

        std::regex regex("\\d");
        std::smatch result;
        std::sregex_iterator pos(input.begin(), input.end(), regex);//���ÿһ������
        std::sregex_iterator end;
        std::regex pattern(R"(rm\s*R?(\d)\s*C?\s*(\d)=\s*(\d(?:,\d)*))");
        std::smatch match;

        while (pos != end)
        {
            std::string match = (*pos).str(); // ��ȡƥ����ַ���
            buffer.push_back(std::stoi(match)); // ���ַ���ת��Ϊ�������洢
            pos++; // ����������
            i++;
        }

        if (std::regex_match(input, match, pattern))
        {
            row = std::stoi(match[1].str());
            col = std::stoi(match[2].str());
            // У�����з�Χ
            if (row >= 1 && row <= 9 && col >= 1 && col <= 9)
            {
                int i = 2;
                for (size_t i = 2; i < buffer.size(); ++i)
                {
                    sudoku.removeCandidates(row - 1, col - 1, buffer[i]);  // �Ƴ�������ѡ��
                    ui.displayMessage("�Ƴ���ѡ�� " + std::to_string(buffer[i]) + " �ɹ�");
                }
                //���Լ����� ���ڿ���ɾ
                //Cell C = sudoku.getCell(row - 1, col - 1);
                //for (size_t i = 0; i < C.getcandidates().size(); ++i)
                //{
                  //  std::cout << C.getcandidates()[i] << " ";
                //}
                std::cout << std::endl;
            }
            else
            {
                ui.displayMessage("�������г�����Χ��");
            }
        }
        else
        {
            ui.displayMessage("ָ���ʽ����");
        }

        // ��ʾ���º����������
        ui.displayGrid(sudoku);
    }
};



class HelpCommand : public Command {
private:
    UIInterface& ui;
    Sudoku& sudoku;
public:
    HelpCommand(Sudoku& sudokuRef, UIInterface& uiRef) :sudoku(sudokuRef), ui(uiRef) {}
    void execute() override {
        std::string helpMessage =
            "help - ��ʾ����ָ��\n"
            "exit - �������˵�\n"
            "replay - ���¿�ʼ����\n"
            "save - �浵\n"
            "record - ��¼��ǰ����\n"
            "back - �����ϴμ�¼����\n"
            "auto - Ψһ��ѡ���Զ�����\n"
            "set RxCy=z - ����\n"
            "set xy=z - �����ļ�д\n"
            "rm RxCy=z1,z2,... - �Ƴ���ѡ��\n"
            "rm xy=z1,z2,... - �Ƴ���ѡ���ļ�д\n"
            "over - �ж������Ƿ�ɹ����";
        ui.displayMessage(helpMessage);//����ui��ͬ�������ʽ��ͬ������gui�Ϳ���̨�Ͳ�ͬ��
        std::cout << "�����������..." << std::endl;
        std::cin.ignore(1);//����һ�����з�  // �ȴ��û�����

        // ��ʾ�������
        ui.displayGrid(sudoku);
    }
};






class OverCommand : public Command
{
public:
    OverCommand(Sudoku& sudokuRef, UIInterface& uiRef, bool& gameRunning)
        : sudoku(sudokuRef), ui(uiRef), gameRunning(gameRunning) {}
    void execute() override
    {



        int isover = 0;//�ж���Ϸ�Ƿ����
        gameRunning = true;
        //std::cout << isover << gameRunning << std::endl;
        for (int i = 0; i < 9 && isover == 0; i++)
        {
            for (int j = 0; j < 9 && isover == 0; j++)
            {
                if (sudoku.getCell(i, j).getvalue() == 0)
                {
                    gameRunning = false;
                    isover = 1;
                }
            }
        }
        //std::cout << isover << gameRunning << std::endl;

        for (int row = 0; row < 9 && isover == 0; row++)
        {
            if (sudoku.getRow(row).isValid() == false)
            {
                gameRunning = false;
                isover = 1;
            }
        }
        //std::cout << isover << gameRunning << std::endl;

        for (int col = 0; col < 9 && isover == 0; col++)
        {
            if (sudoku.getRow(col).isValid() == false)
            {
                gameRunning = false;
                isover = 1;
            }
        }
        //std::cout << isover << gameRunning << std::endl;

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                int blockIndex = (i / 3) * 3 + (j / 3); //���㵱ǰ��Ԫ�������ĸ���
                if (sudoku.getBlock(blockIndex).isValid() == false)
                {
                    gameRunning = false;
                    isover = 1;
                }
            }
        }
        //std::cout << isover << gameRunning << std::endl;
    }
private:
    Sudoku& sudoku;  // ��Ӧ������ʵ��
    UIInterface& ui; // �������û�����
    bool& gameRunning;
};



class SaveCommand : public Command   //��¼��ǰ����
{
private:
    Sudoku& sudoku;
    UIInterface& ui;
    PuzzleLoaderInterface& storage;  // �����ļ���д�ӿ�
    std::string filename;
public:
    SaveCommand(Sudoku& sudokuRef, UIInterface& uiRef, PuzzleLoaderInterface& storageRef, std::string filenameRef)
        : sudoku(sudokuRef), ui(uiRef), storage(storageRef), filename(filenameRef) {}

    void execute() override {
        //storage.clear(filename);
        storage.save(sudoku, filename);  // ʹ�ô洢�ӿڱ��浱ǰ����
        ui.displayMessage("��ǰ�����ѱ���...");
    }
};




class BackCommand : public Command //�����ϴν���
{
private:   //LoadCommandӵ�У�ģ�� ���� �ļ�·�� ������
    Sudoku& sudoku;
    UIInterface& ui;
    Sudoku tmpsudoku;

public:
    BackCommand(Sudoku& sudokuRef, UIInterface& uiRef, Sudoku tmpsudokuRef)
        : sudoku(sudokuRef), ui(uiRef), tmpsudoku(tmpsudokuRef) {}

    void execute() override
    {
        sudoku = tmpsudoku;
        ui.displayMessage("�����¿�ʼ����");
        ui.displayGrid(sudoku);  // ��ʾ���ú������
    }
};



class RecordCommand : public Command //�����ϴν���
{
private:   //LoadCommandӵ�У�ģ�� ���� �ļ�·�� ������
    Sudoku& sudoku;
    UIInterface& ui;
    Sudoku& tmpsudoku;

public:
    RecordCommand(Sudoku& sudokuRef, UIInterface& uiRef, Sudoku& tmpsudokuRef)
        : sudoku(sudokuRef), ui(uiRef), tmpsudoku(tmpsudokuRef) {}

    void execute() override
    {
        sudoku = tmpsudoku;
        ui.displayMessage("�����¿�ʼ����");
        ui.displayGrid(sudoku);  // ��ʾ���ú������
    }
};






