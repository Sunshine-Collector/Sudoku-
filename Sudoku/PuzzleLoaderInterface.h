#pragma once
// PuzzleRepositoryInterface.h
#ifndef PUZZLEREPOSITORYINTERFACE_H
#define PUZZLEREPOSITORYINTERFACE_H

#include <vector>
#include <string>
#include"Sudoku.h"
#include<iostream>
#include<fstream>

class PuzzleLoaderInterface 
{
public:
    virtual void load(Sudoku& sudoku, const std::string& filename,int sernum) = 0;//ser为数组编号
    virtual void save(Sudoku& sudoku, const std::string& filename) = 0;
    virtual ~PuzzleLoaderInterface() = default;
};

class DatabasePuzzleLoader : public PuzzleLoaderInterface {
public:
    void load(Sudoku& sudoku, const std::string& filename, int sernum) override {
        // 从数据库中加载数独题目
    }
    void save(Sudoku& sudoku, const std::string& filename) override {
        // 将数独题目保存到数据库
    }
    // 其他方法实现...
};

class TxtPuzzleLoader : public PuzzleLoaderInterface 
{
public:
    // 读取数独文件
    void load(Sudoku& sudoku, const std::string& filename, int randnum) override
    {
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cerr << "文件读入失败: " << filename << std::endl;
            return;
        }

        int numofboard = randnum;  // 随机读取一个数独题//读取某个编号的数独题
        int currentboard = 0;
        std::vector<int> row;

        while (true) 
        {
            std::vector<std::vector<int>> tmp;

            while (true) 
            {
                char data[300];
                infile.getline(data, 300);

                if (data[0] == '-') {
                    break;  // 当前棋盘结束
                }

                for (int i = 0; i < strlen(data); ++i) {
                    if ('0' <= data[i] && data[i] <= '9') {
                        row.push_back(data[i] - '0');
                    }
                }

                tmp.push_back(row);  // 将当前行推入临时棋盘
                row.clear();
            }

            if (!numofboard) {
                for (int i = 0; i < 9; ++i) {
                    for (int j = 0; j < 9; ++j) {
                        sudoku.getCell(i,j).setValue(tmp[i][j]);  // 设置数独格子的值
                    }
                }
                break;
            }
            --numofboard;
        }

        infile.close();
    }



    //获得数独编号
    virtual int getnum(Sudoku& sudoku, const std::string& filename) {
        std::ifstream infile(filename);


        if (!infile.is_open()) {
            std::cerr << "文件读入失败: " << filename << std::endl;
            return -1;
        }

        int numofboard = 0;
        int currentboard = 0;
        std::vector<int> row;



        while (true)
        {
            std::vector<std::vector<int>> tmp;

            bool issame = false;//用于判断数独是否找到的参数
            int isa = 0;
            while (true)
            {
                char data[300];
                infile.getline(data, 300);

                

                if (data[0] == '-') {
                    break;  // 当前棋盘结束
                }

                for (int i = 0; i < strlen(data); ++i) {
                    if ('1' <= data[i] && data[i] <= '9') {
                        row.push_back(data[i] - '0');
                    }
                }

                tmp.push_back(row);  // 将当前行推入临时棋盘
                row.clear();
            }

            for (int i = 0; i < 9; ++i) {
                for (int j = 0; j < 9; ++j) {
                    if (sudoku.getCell(i, j).getValue() != tmp[i][j]) {
                        isa = 1;
                        break;
                    }
                }
            }

            if (isa == 0) {
                issame = true;
            }

            if (issame) {
                return numofboard;
                break;
            }
            ++numofboard;
        }
        std::cout << "未找到数组" <<std:: endl;
        return -1;
    }



    // 存储数独文件
    void save(Sudoku& sudoku, const std::string& filename) {
        //std::ofstream outfile(filename);
        std::ofstream outfile(filename, std::ios::out | std::ios::app);
        if (!outfile.is_open()) {
            std::cerr << "文件写入失败: " << filename << std::endl;
            return;
        }
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                outfile << sudoku.getCell(i,j).getValue() << " ";
            }
            outfile << std::endl;
        }
        outfile << "------- 0 -------" << std::endl;
        outfile.close();
    }

    //清除文件数据
    void clear(const std::string& filename)  {
        std::ofstream file(filename, std::ofstream::out | std::ofstream::trunc);
        if (!file.is_open()) {
            std::cerr << "无法打开文件以清除内容: " << filename << std::endl;
            return;
        }
        file.close();
    }

    int countLinesInFile(const std::string& filename) {//获取题目行数
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "无法打开文件: " << filename << std::endl;
            return -1;
        }

        int lineCount = 0;
        std::string line;
        while (std::getline(file, line)) {
            ++lineCount;
        };
        file.close();
        return lineCount;
    }


};

    




class BinaryPuzzleLoader : public PuzzleLoaderInterface {
public:
    void load(Sudoku& sudoku, const std::string& filename, int sernum) override {
        // 二进制文件加载逻辑
    }
    void save(Sudoku& sudoku, const std::string& filename) override {
        // 将数独题目保存到数据库
    }
    // 其他方法实现...
};


#endif
