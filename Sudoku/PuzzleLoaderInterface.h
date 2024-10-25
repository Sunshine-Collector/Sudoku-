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
    virtual void load(Sudoku& sudoku, const std::string& filename,int sernum) = 0;//serΪ������
    virtual void save(Sudoku& sudoku, const std::string& filename) = 0;
    virtual ~PuzzleLoaderInterface() = default;
};

class DatabasePuzzleLoader : public PuzzleLoaderInterface {
public:
    void load(Sudoku& sudoku, const std::string& filename, int sernum) override {
        // �����ݿ��м���������Ŀ
    }
    void save(Sudoku& sudoku, const std::string& filename) override {
        // ��������Ŀ���浽���ݿ�
    }
    // ��������ʵ��...
};

class TxtPuzzleLoader : public PuzzleLoaderInterface 
{
public:
    // ��ȡ�����ļ�
    void load(Sudoku& sudoku, const std::string& filename, int randnum) override
    {
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cerr << "�ļ�����ʧ��: " << filename << std::endl;
            return;
        }

        int numofboard = randnum;  // �����ȡһ��������//��ȡĳ����ŵ�������
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
                    break;  // ��ǰ���̽���
                }

                for (int i = 0; i < strlen(data); ++i) {
                    if ('0' <= data[i] && data[i] <= '9') {
                        row.push_back(data[i] - '0');
                    }
                }

                tmp.push_back(row);  // ����ǰ��������ʱ����
                row.clear();
            }

            if (!numofboard) {
                for (int i = 0; i < 9; ++i) {
                    for (int j = 0; j < 9; ++j) {
                        sudoku.getCell(i,j).setValue(tmp[i][j]);  // �����������ӵ�ֵ
                    }
                }
                break;
            }
            --numofboard;
        }

        infile.close();
    }



    //����������
    virtual int getnum(Sudoku& sudoku, const std::string& filename) {
        std::ifstream infile(filename);


        if (!infile.is_open()) {
            std::cerr << "�ļ�����ʧ��: " << filename << std::endl;
            return -1;
        }

        int numofboard = 0;
        int currentboard = 0;
        std::vector<int> row;



        while (true)
        {
            std::vector<std::vector<int>> tmp;

            bool issame = false;//�����ж������Ƿ��ҵ��Ĳ���
            int isa = 0;
            while (true)
            {
                char data[300];
                infile.getline(data, 300);

                

                if (data[0] == '-') {
                    break;  // ��ǰ���̽���
                }

                for (int i = 0; i < strlen(data); ++i) {
                    if ('1' <= data[i] && data[i] <= '9') {
                        row.push_back(data[i] - '0');
                    }
                }

                tmp.push_back(row);  // ����ǰ��������ʱ����
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
        std::cout << "δ�ҵ�����" <<std:: endl;
        return -1;
    }



    // �洢�����ļ�
    void save(Sudoku& sudoku, const std::string& filename) {
        //std::ofstream outfile(filename);
        std::ofstream outfile(filename, std::ios::out | std::ios::app);
        if (!outfile.is_open()) {
            std::cerr << "�ļ�д��ʧ��: " << filename << std::endl;
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

    //����ļ�����
    void clear(const std::string& filename)  {
        std::ofstream file(filename, std::ofstream::out | std::ofstream::trunc);
        if (!file.is_open()) {
            std::cerr << "�޷����ļ����������: " << filename << std::endl;
            return;
        }
        file.close();
    }

    int countLinesInFile(const std::string& filename) {//��ȡ��Ŀ����
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "�޷����ļ�: " << filename << std::endl;
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
        // �������ļ������߼�
    }
    void save(Sudoku& sudoku, const std::string& filename) override {
        // ��������Ŀ���浽���ݿ�
    }
    // ��������ʵ��...
};


#endif
