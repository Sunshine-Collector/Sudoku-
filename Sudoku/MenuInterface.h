
#ifndef MENUINTERFACE_H
#define MENUINTERFACE_H

#include <vector>
#include <string>
#include <iostream>
#include <map>



class MenuInterface
{
public:
    // չʾ�˵�
    virtual void displayMenu() const = 0;
    virtual ~MenuInterface() {}
};


class BaseMenu : public MenuInterface {
public:
    // չʾ�˵���ͨ�ò���
    virtual void displayMenuHeader() const {
        std::cout << "        ������Ϸ�˵�        \n" << std::endl;
    }

    // չʾ�˵���ͨ��ѡ��
    virtual void displayCommonOptions() const {
        std::cout << "      1. ���ѡ��         " << std::endl;
        std::cout << "      2. �����ѡ��         " << std::endl;
        std::cout << "      3. �Զ�����         " << std::endl;
        std::cout << "      4. �����ϴδ浵         " << std::endl;
        std::cout << "      5. ѡ��             " << std::endl;
        std::cout << "      0. �˳�             " << std::endl;
        std::cout << "\n      ��ѡ��(0-5): ";
    }

    // չʾ�˵����˳�ѡ��
    virtual void displayExitOption() const {
        std::cout << "      0. �˳�             " << std::endl;
    }

    // չʾ�˵�����ʾ��Ϣ
    virtual void displayPrompt() const {
        std::cout << "\n      ��ѡ��(0-5): ";
    }

    // չʾ�����Ĳ˵�
    virtual void displayMenu() const override {
        displayMenuHeader();
        displayCommonOptions();
        displayExitOption();
        displayPrompt();
    }
};
class MainMenu : public BaseMenu
{
public:
    // չʾ�˵�
    void displayMenu() const {
        std::cout << "        �������˵�        \n" << std::endl;
        std::cout << "      1. ���ѡ��         " << std::endl;
        std::cout << "      2. �����ѡ��         " << std::endl;
        std::cout << "      3. �Զ�����         " << std::endl;
        std::cout << "      4. �����ϴδ浵         " << std::endl;
        std::cout << "      5. ��������������     " << std::endl;
        std::cout << "      0. �˳�             " << std::endl;
        std::cout << "\n      ��ѡ��(0-5): ";
    }
};


class DifficultyMenu : public MenuInterface
{
    public:
        void displayMenu()const
        {
            std::cout << "ѡ���Ѷ�: \n";
            std::cout << "1. ��\n";
            std::cout << "2. �е�\n";
            std::cout << "3. ����\n";
            std::cout << "      0. �˳�             " << std::endl;
            std::cout << "\n      ��ѡ��(0-3): ";
        }
};


#endif