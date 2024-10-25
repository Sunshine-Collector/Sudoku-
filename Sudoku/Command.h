#pragma once
#include "UIInterface.h"
#include "Sudoku.h"
#include <string>
#include "MenuInterface.h"
#include "PuzzleLoaderInterface.h"
#include <sstream>
#include <iostream>
#include <regex>
#include <vector>
#include "SudokuPlayer.h"
class Command
{
public:
    virtual ~Command() = default;
    virtual void execute() = 0;  // 每个派生类都必须实现这个方法
};

//在cpp中
class PlayCommand : public Command  //游戏操作
{
public:
    PlayCommand(Sudoku& sudokuRef, UIInterface& uiRef, Sudoku initialsudokuRef, Sudoku &tmpsudokuRef)
        : sudoku(sudokuRef), ui(uiRef), initialsudoku(initialsudokuRef), tmpsudoku(tmpsudokuRef) {}
    void execute() override;

private:
    Sudoku& sudoku;  // 对应的数独实例
    UIInterface& ui; // 用于与用户交互
    Sudoku initialsudoku;//用以记录初始创造的数组
    Sudoku tmpsudoku;//用以记录游戏过程中保存的数组
};


class AddCandidateCommand : public Command   //填充候选数
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
                    // 如果单元格已被填入，则移除同一行、同一列和同一宫格的候选数
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
    Sudoku& sudoku;  // 目标数独实例
};



class LoadCommand : public Command //载入上次进度
{
private:   //LoadCommand拥有：模型 界面 文件路径 加载器
    Sudoku& sudoku;
    UIInterface& ui;
    PuzzleLoaderInterface& storage;  // 文件读写接口
    std::string filename;

public:
    LoadCommand(Sudoku& sudokuRef, UIInterface& uiRef, PuzzleLoaderInterface& storageRef, const std::string& filenameRef)
        : sudoku(sudokuRef), ui(uiRef), storage(storageRef), filename(filenameRef) {}

    void execute() override
    {
        //加载数独游戏数据
        storage.load(sudoku, filename, 0);
        ui.displayMessage("上次游戏数据已从 " + filename + " 加载.");


        // 将各个小命令依次加入到组合命令中
        AddCandidateCommand AddCandidateCommand(sudoku);
        AddCandidateCommand.execute();
        ui.displayGrid(sudoku);  // 更新UI显示加载后的数独棋盘
        ui.displayMessage("上次游戏数据已从 " + filename + " 加载.");
        Sudoku initialsudoku = sudoku;
        Sudoku tmpsudoku = sudoku;
        PlayCommand PlayCommand(sudoku, ui, initialsudoku, tmpsudoku);
        PlayCommand.execute();

        //更新UI
        ui.displayGrid(sudoku);
    }
};



class AutoCommand : public Command  //自动置数
{
private:
    Sudoku& sudoku;
    UIInterface& ui;

public:
    AutoCommand(Sudoku& sudokuRef, UIInterface& uiRef)
        : sudoku(sudokuRef), ui(uiRef) {}

    void execute() override {


        bool changed = false;
        // 遍历数独的每个格子
        for (int row = 0; row < 9; ++row)
        {
            for (int col = 0; col < 9; ++col)
            {

                Cell& cell = sudoku.getCell(row, col);
                int isright = 0;
                // 如果该格子为空（value 为 0）并且候选数只有一个不为零1
                for (size_t i = 0; i < cell.getcandidates().size(); ++i)
                {
                    if (cell.getcandidates()[i] != 0)
                    {
                        isright++;
                    }
                }
                if (cell.getValue() == 0 && isright == 1) {
                    // 将唯一候选数设置为该格子的值
                    for (size_t i = 0; i < cell.getcandidates().size(); ++i)
                    {
                        if (cell.getcandidates()[i] != 0)
                        {
                            cell.setValue(cell.getcandidates()[i]);
                            cell.removeCandidate(cell.getcandidates()[i]);  // 清空候选数
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
        // 输出结果
        if (changed) {
            ui.displayMessage("自动置数完成...");
        }
        else {
            ui.displayMessage("没有可以自动置数的单元...");
        }

        // 显示更新后的数独网格
        ui.displayGrid(sudoku);
    }
};



class ReplayCommand : public Command //载入上次进度
{
private:   
    Sudoku& sudoku;
    UIInterface& ui;
    Sudoku initialsudoku;

public:
    ReplayCommand(Sudoku& sudokuRef, UIInterface& uiRef, Sudoku initialsudokuRef)
        : sudoku(sudokuRef), ui(uiRef), initialsudoku(initialsudokuRef) {}

    void execute() override
    {
        sudoku = initialsudoku;
        ui.displayMessage("已重新开始本局");
        ui.displayGrid(sudoku);  // 显示重置后的数独
    }
};

class DigPuzzleCommand : public Command   //选择难度
{
public:
    DigPuzzleCommand(Sudoku& sudokuRef, int difficultyLevel)
        : sudoku(sudokuRef), difficulty(difficultyLevel) {}

    void execute() override
    {
        int digcount = 0;
        switch (difficulty) {
        case 1:  // 简单
            digcount = rand() % (30 - 20 + 1) + 20;
            break;
        case 2:  // 中等
            digcount = rand() % (40 - 30 + 1) + 30;
            break;
        case 3:  // 困难
            digcount = rand() % (50 - 40 + 1) + 40;
            break;
        default:
            std::cerr << "无效的难度级别！" << std::endl;
            return;
        }

        while (digcount) {
            int x = rand() % 9;
            int y = rand() % 9;

            if (sudoku.getCell(x, y).getValue() == 0) continue;

            int answer = sudoku.getCell(x, y).getValue();
            sudoku.getCell(x, y).setValue(0);  // 挖空


            digcount--;
            // 可在此处加入唯一解检测逻辑，如 solveSudoku
        }
        AddCandidateCommand AddCandidateCommand(sudoku);
        AddCandidateCommand.execute();
    }

private:
    Sudoku& sudoku;  // 目标数独实例
    int difficulty;  // 挖空的难度
};

class SetCommand : public Command //set 置数
{
private:
    Sudoku& sudoku;
    UIInterface& ui;
    std::string input;
    Sudoku initialsudoku;

public:
    SetCommand(Sudoku& sudokuRef, UIInterface& uiRef, const std::string& inputCommand, Sudoku initialsudoku)
        : sudoku(sudokuRef), ui(uiRef), input(inputCommand) , initialsudoku(initialsudoku){}

    void execute() override {



        // 解析 `set RxCy=z` 或 `set xy=z`
        int row, col, value;
        std::regex pattern(R"(set\s*R?\s*(\d+)\s*C?\s*(\d+)\s*=\s*(\d+))");
        std::smatch match;
        if (std::regex_match(input, match, pattern)) {
            row = std::stoi(match[1].str());
            col = std::stoi(match[2].str());
            value = std::stoi(match[3].str());
            // 校验行列范围
            if (row >= 1 && row <= 9 && col >= 1 && col <= 9 && value >= 1 && value <= 9) {
                sudoku.setValue(row - 1, col - 1, value);  // 设置值，转换成0索引
                ui.displayMessage("设置R" + std::to_string(row) + "C" + std::to_string(col) + "为" + std::to_string(value) + "成功!");
                for (int row = 0; row < 9; ++row) {
                    for (int col = 0; col < 9; ++col) {
                        sudoku.getCell(row, col).clearCandidates();
                    }
                }
                AddCandidateCommand AddCandidateCommand(sudoku);
                AddCandidateCommand.execute();
            }
            else {
                ui.displayMessage("输入值超出范围！");
            }
        }
        else {
            ui.displayMessage("指令格式错误！");
        }

        // 显示更新后的数独网格
        ui.displayGrid(sudoku);
    }
};

class RemoveCommand : public Command  //rm 移除候选数
{
private:
    Sudoku& sudoku;
    UIInterface& ui;
    std::string input;

public:
    RemoveCommand(Sudoku& sudokuRef, UIInterface& uiRef, const std::string& inputCommand)
        : sudoku(sudokuRef), ui(uiRef), input(inputCommand) {}

    void execute() override {
        // 解析 `rm RxCy=z` 或 `rm xy=z`
        int row, col, i = 0;
        std::vector<int> buffer;

        std::regex regex("\\d");
        std::smatch result;
        std::sregex_iterator pos(input.begin(), input.end(), regex);//存放每一个数字
        std::sregex_iterator end;
        std::regex pattern(R"(rm\s*R?(\d)\s*C?\s*(\d)=\s*(\d(?:,\d)*))");
        std::smatch match;

        while (pos != end)
        {
            std::string match = (*pos).str(); // 获取匹配的字符串
            buffer.push_back(std::stoi(match)); // 将字符串转换为整数并存储
            pos++; // 递增迭代器
            i++;
        }

        if (std::regex_match(input, match, pattern))
        {
            row = std::stoi(match[1].str());
            col = std::stoi(match[2].str());
            // 校验行列范围
            if (row >= 1 && row <= 9 && col >= 1 && col <= 9)
            {
                int i = 2;
                for (size_t i = 2; i < buffer.size(); ++i)
                {
                    sudoku.removeCandidates(row - 1, col - 1, buffer[i]);  // 移除单个候选数
                    ui.displayMessage("移除候选数 " + std::to_string(buffer[i]) + " 成功");
                }
                //用以检查输出 后期可以删
                //Cell C = sudoku.getCell(row - 1, col - 1);
                //for (size_t i = 0; i < C.getcandidates().size(); ++i)
                //{
                  //  std::cout << C.getcandidates()[i] << " ";
                //}
                std::cout << std::endl;
            }
            else
            {
                ui.displayMessage("输入行列超出范围！");
            }
        }
        else
        {
            ui.displayMessage("指令格式错误！");
        }

        // 显示更新后的数独网格
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
            "help - 显示所有指令\n"
            "exit - 返回主菜单\n"
            "replay - 重新开始本局\n"
            "save - 存档\n"
            "record - 记录当前步数\n"
            "back - 返回上次记录步数\n"
            "auto - 唯一候选数自动置数\n"
            "set RxCy=z - 置数\n"
            "set xy=z - 置数的简写\n"
            "rm RxCy=z1,z2,... - 移除候选数\n"
            "rm xy=z1,z2,... - 移除候选数的简写\n"
            "over - 判断数独是否成功完成";
        ui.displayMessage(helpMessage);//根据ui不同，输出形式不同，比如gui和控制台就不同。
        std::cout << "按任意键继续..." << std::endl;
        std::cin.ignore(1);//忽略一个换行符  // 等待用户输入

        // 显示数独表格
        ui.displayGrid(sudoku);
    }
};




class OverCommand : public Command
{
public:
    OverCommand(Sudoku& sudokuRef, UIInterface& uiRef, bool& gameRunning)
        : sudoku(sudokuRef), ui(uiRef), gameRunning(gameRunning) {}
    OverCommand(Sudoku& sudokuRef, UIInterface& uiRef)
        : sudoku(sudokuRef), ui(uiRef), gameRunning(true) {}
    void execute() override
    {

        int isover = 0;//判断游戏是否结束
        //std::cout << gameRunning <<std::endl;
        for (int i = 0; i < 9 && isover == 0; i++)
        {
            for (int j = 0; j < 9 && isover == 0; j++)
            {
                if (sudoku.getCell(i, j).getvalue() == 0)
                {
                    //isover = 1;
                    gameRunning = false;
                }
            }
        }
        //std::cout << isover << "!!!" << gameRunning << std::endl;

        for (int row = 0; row < 9 && isover == 0; row++)
        {
            if (sudoku.getRow(row).isValid() == false)
            {
                gameRunning = false;
                isover = 1;
            }
        }
        //std::cout << isover << "!!!" << gameRunning << std::endl;

        for (int col = 0; col < 9 && isover == 0; col++)
        {
            if (sudoku.getRow(col).isValid() == false)
            {
                gameRunning = false;
                isover = 1;
            }
        }
        //std::cout << isover << "!!!" << gameRunning << std::endl;

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                int blockIndex = (i / 3) * 3 + (j / 3); //计算当前单元格属于哪个块
                if (sudoku.getBlock(blockIndex).isValid() == false)
                {
                    gameRunning = false;
                    isover = 1;
                }
            }
        }
        //std::cout << isover << "!!!" << gameRunning << std::endl;
        if (gameRunning)
        {
            ui.displayMessage("恭喜 游戏成功！");
        }
        else
        {
            ui.displayMessage("很遗憾 你这次挑战失败！");
        }
    }
private:
    Sudoku& sudoku;  // 对应的数独实例
    UIInterface& ui; // 用于与用户交互
    bool gameRunning;
};



class SaveCommand : public Command   //记录当前进度
{
private:
    Sudoku& sudoku;
    UIInterface& ui;
    std::string filename;
public:
    SaveCommand(Sudoku& sudokuRef, UIInterface& uiRef, std::string filenameRef)
        : sudoku(sudokuRef), ui(uiRef),  filename(filenameRef) {}

    void execute() override {
        TxtPuzzleLoader storage;// 新增文件读写接口
        //storage.clear(filename);
        storage.save(sudoku, filename);  // 使用存储接口保存当前进度
        ui.displayMessage("当前进度已保存...");
    }
};




class BackCommand : public Command //载入上次步数
{
private:   
    Sudoku& sudoku;
    UIInterface& ui;
    Sudoku tmpsudoku;

public:
    BackCommand(Sudoku& sudokuRef, UIInterface& uiRef, Sudoku tmpsudokuRef)
        : sudoku(sudokuRef), ui(uiRef), tmpsudoku(tmpsudokuRef) {}

    void execute() override
    {
        sudoku = tmpsudoku;
        ui.displayMessage("已返回上次记录步数");
        ui.displayGrid(sudoku);  // 显示重置后的数独
    }
};



class RecordCommand : public Command //载入上次进度
{
private:   //LoadCommand拥有：模型 界面 文件路径 加载器
    Sudoku& sudoku;
    UIInterface& ui;
    Sudoku& tmpsudoku;

public:
    RecordCommand(Sudoku& sudokuRef, UIInterface& uiRef, Sudoku& tmpsudokuRef)
        : sudoku(sudokuRef), ui(uiRef), tmpsudoku(tmpsudokuRef) {}

    void execute() override
    {
        tmpsudoku = sudoku ;
        ui.displayMessage("已记录当前步数");
        ui.displayGrid(sudoku);  // 显示重置后的数独
    }
};

class RandomPuzzleCommand : public Command  //随机选题
{
public:
    RandomPuzzleCommand(Sudoku& sudokuRef, UIInterface& uiRef)
        : sudoku(sudokuRef), ui(uiRef) {}

    void execute() override
    {


        std::string loadfile = "easy.txt";
        std::string savefile = "randomsave.txt";

        TxtPuzzleLoader loader;

        int randmnum = rand() % (loader.countLinesInFile(loadfile) / 10 - 1 + 1); //随机题目编号
        loader.load(sudoku, loadfile, randmnum);//如果要变更存储模式，只需要改文件名+派生类类型，loader这个名字不要改
        std::cout << "您正在游玩编号为" << loader.getnum(sudoku, loadfile) << "的数组" << std::endl;

        Sudoku tmpinitialsudoku = sudoku;
        // 存储初始棋盘和挖空后的棋盘
        int ini[9][9] = {};
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                ini[i][j] = sudoku.getCell(i, j).getValue();
        // 挖空操作，使用中等难度
        DigPuzzleCommand digCommand(sudoku, 3);
        digCommand.execute();
        ui.displayGrid(sudoku); // 更新UI显示
        Sudoku initialsudoku = sudoku;
        Sudoku tmpsudoku = sudoku;
        PlayCommand PlayCommand(sudoku, ui, initialsudoku, tmpsudoku);
        PlayCommand.execute();

    }

private:
    Sudoku& sudoku;  // 对应的数独实例
    UIInterface& ui; // 用于与用户交互
};


class SelectPuzzleCommand : public Command  //自定义选题
{
public:
    SelectPuzzleCommand(Sudoku& sudokuRef, UIInterface& uiRef)
        : sudoku(sudokuRef), ui(uiRef) {}

    void execute() override
    {


        std::string loadfile = "easy.txt";
        std::string savefile = "randomsave.txt";

        TxtPuzzleLoader loader;

        int num = 0; //题目编号
        std::cout << "输入题目编号" << "(0到" << loader.countLinesInFile(loadfile) / 10 - 1 << "之间)" << std::endl;
        std::cin >> num;

        std::cout << "编号为：" << num << std::endl;
        loader.load(sudoku, loadfile, num);//如果要变更存储模式，只需要改文件名+派生类类型，loader这个名字不要改
        //std::cout << "您正在游玩编号为" << loader.getnum(sudoku, loadfile) << "的数组" << std::endl;

        Sudoku tmpinitialsudoku = sudoku;
        // 存储初始棋盘和挖空后的棋盘
        int ini[9][9] = { 0 };
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                ini[i][j] = sudoku.getCell(i, j).getValue();
        // 挖空操作，使用中等难度
        DigPuzzleCommand digCommand(sudoku, 3);
        digCommand.execute();

        ui.displayGrid(sudoku); // 更新UI显示2

        Sudoku initialsudoku = sudoku;
        Sudoku tmpsudoku = sudoku;
        PlayCommand PlayCommand(sudoku, ui, initialsudoku, tmpsudoku);
        PlayCommand.execute();

    }

private:
    Sudoku& sudoku;  // 对应的数独实例
    UIInterface& ui; // 用于与用户交互
};
class SolvePuzzleCommand : public Command {
private:
    Sudoku& sudoku;
    UIInterface& ui;
    TxtPuzzleLoader& storage;
    std::string filename;

    SudokuPlayer player;

public:
    SolvePuzzleCommand(Sudoku& sudokuRef, UIInterface& uiRef, TxtPuzzleLoader& storageRef, const std::string& filenameRef)
        : sudoku(sudokuRef), ui(uiRef), storage(storageRef), filename(filenameRef) {}

    void execute() override {
        // 从文件中读取数独游戏
        vector<Board> boards = player.readFile(filename);
        // 解决每个游戏
        /*for (const auto& board : boards)
        {
            vector<Board> solutions = player.solveSudoku(board);
            // 存储或显示解决方案
            ui.displaySolutions(solutions[0]);
        }*/
        vector<Board> solutions = player.solveSudoku(boards[storage.countLinesInFile(filename) / 10 - 1]);
        ui.displaySolutions(solutions[0]);
        //storage.countLinesInFile(filename)/10-1
    }
};

class CustomPuzzleCommand : public Command//自定义题目
{
public:
    CustomPuzzleCommand(Sudoku& sudokuRef, UIInterface& uiRef)
        : sudoku(sudokuRef), ui(uiRef) {}

    void execute() override
    {

        std::string savefile = "randomsave.txt";
        std::string loadfile = "custom.txt";
        TxtPuzzleLoader loader;

        std::vector<std::vector<int>> tmp;//用以获得输入的数独
        tmp.resize(9, std::vector<int>(9, 0));

        int option = 0;
        bool right = true;
        int ex = 0;
        std::cout << "1.粘贴包含81个数字\n" << "2.手动输入\n" << "0.退出\n";
        std::cin >> option;
        if (option == 1)
        {
            int number;
            std::cout << "请粘贴包含81个数字的数独网格，每个数字之间用空格分隔：\n";
            int count = 0;
            while (count < 81 && std::cin >> number) {
                int row = count / 9;
                int col = count % 9;
                tmp[row][col] = number;
                sudoku.getCell(row, col).setValue(tmp[row][col]);
                ++count;
            }

            if (count < 81) {
                std::cerr << "错误：输入的数字不足81个。\n";
            }

            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; ++j)
                {
                    if (tmp[i][j] > 9 && tmp[i][j] < 0)
                    {
                        std::cout << "输入存在不在0至9之间的数";
                        right = false;
                        break;
                    }
                }
            }


        }
        else if (option == 2)
        {
            int con = 1;
            std::cout << "输入-1则退出" << std::endl;
            for (int i = 0; i < 9 && con == 1; i++)
            {
                for (int j = 0; j < 9 && con == 1; ++j) {
                    while (1)
                    {
                        std::cout << "输入数独的第" << i + 1 << "行,第" << j + 1 << "列的数字：";
                        std::cin >> tmp[i][j]; // 读取每个数字并存储在向量中
                        sudoku.getCell(i, j).setValue(tmp[i][j]);
                        if (tmp[i][j] <= 9 && tmp[i][j] >= 0)
                        {
                            ui.displayGrid(sudoku); // 更新UI显示
                            break;
                        }
                        if (tmp[i][j] == -1)
                        {
                            con = 0;
                            break;
                        }
                        else
                        {
                            std::cout << "输入不在0至9之间";
                        }
                        if (std::cin.fail()) {
                            std::cin.clear(); // 清除错误标志
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略错误输入
                            std::cerr << "无效输入" << std::endl;
                        }
                    }
                }
            }
        }
        else if (option == 0)
        {
            right = false;
            ex = 1;
        }
        else
        {
            std::cout << "输入错误\n";
            right = false;

        }
        //bool isover = true;
        //OverCommand overcommand(sudoku, ui, isover);  // 解析并处理 `over` 指令
        //overcommand.execute();
        //if (isover) {
        //    std::cout << "数独满足要求\n";
        //}
        /*else {
            if (ex == 0)
            {
                std::cout << "数独不满足要求\n";
            }
            right = isover;
        }*/
        if (right)
        {
            SaveCommand saveCommand(sudoku, ui,  loadfile);//////////////////
            saveCommand.execute();
            std::cout << "填充的数独网格如下：\n";
            //std::cout << "数独设置成功，该数独编号为：" << loader.getnum(sudoku, loadfile) << std::endl;
            ui.displayGrid(sudoku); // 更新UI显示
            int sh = 0;
            std::cout << "是否需要求解该数独(是则输入1.否则输入2)"<< std::endl;
            std::cin >> sh;
            if(sh == 1){
                std::cout << "数独求解器得到结果为\n";
                TxtPuzzleLoader x;
                SolvePuzzleCommand solve(sudoku, ui, x, "custom.txt");
                solve.execute();
            }
            
        };
    }


private:
    Sudoku& sudoku;  // 对应的数独实例
    UIInterface& ui; // 用于与用户交互
};




//数独生成命令        可以生成挖空的  也可以生成不挖空的  当前写的是不挖空的
class GeneratePuzzleCommand : public Command
{
private:
    Sudoku& sudoku;
    UIInterface& ui;
    PuzzleLoaderInterface& storage;
    std::string filename;

    int gameNumber;
    int gameLevel;
    ofstream outfile;
    SudokuPlayer player;

public:
    GeneratePuzzleCommand(Sudoku& sudokuRef, UIInterface& uiRef, PuzzleLoaderInterface& storageRef, const std::string& filenameRef)
        : sudoku(sudokuRef), ui(uiRef), storage(storageRef), filename(filenameRef) {}

    vector<int> getEmptyRange()
    {
        int min_empty, max_empty;
        cout << "请输入数独游戏的挖空数范围（例如 20 30）: ";
        cin >> min_empty >> max_empty;

        // 简单的输入验证
        while (min_empty < 0 || max_empty > 55 || min_empty > max_empty) {
            cout << "无效的输入，请输入一个范围在0到55之间的两个数字，且第一个数字不大于第二个数字: ";
            cin >> min_empty >> max_empty;
        }

        vector<int> range = { min_empty, max_empty };
        return range;
    }
    void execute() override {
        cout << "请输入要生成的数独游戏数量: ";
        cin >> gameNumber;
        // 使用 getEmptyRange 函数获取挖空数范围
        vector<int> range = getEmptyRange();

        // 打开文件以写入
        outfile.open(filename, ios::out | ios::trunc);

        // 生成游戏
        player.generateGame(gameNumber, 0, range, outfile, player);

        // 清空范围，为下一次生成准备（如果需要）
        range.clear();

        // 更新UI
        ui.displayMessage("游戏生成成功");
    }
};