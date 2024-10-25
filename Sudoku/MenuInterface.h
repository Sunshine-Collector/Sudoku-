
#ifndef MENUINTERFACE_H
#define MENUINTERFACE_H

#include <vector>
#include <string>
#include <iostream>
#include <map>



class MenuInterface
{
public:
    // 展示菜单
    virtual void displayMenu() const = 0;
    virtual ~MenuInterface() {}
};


class BaseMenu : public MenuInterface {
public:
    // 展示菜单的通用部分
    virtual void displayMenuHeader() const {
        std::cout << "        数独游戏菜单        \n" << std::endl;
    }

    // 展示菜单的通用选项
    virtual void displayCommonOptions() const {
        std::cout << "      1. 随机选题         " << std::endl;
        std::cout << "      2. 按题号选题         " << std::endl;
        std::cout << "      3. 自定义题         " << std::endl;
        std::cout << "      4. 返回上次存档         " << std::endl;
        std::cout << "      5. 选项             " << std::endl;
        std::cout << "      0. 退出             " << std::endl;
        std::cout << "\n      请选择(0-5): ";
    }

    // 展示菜单的退出选项
    virtual void displayExitOption() const {
        std::cout << "      0. 退出             " << std::endl;
    }

    // 展示菜单的提示信息
    virtual void displayPrompt() const {
        std::cout << "\n      请选择(0-5): ";
    }

    // 展示完整的菜单
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
    // 展示菜单
    void displayMenu() const {
        std::cout << "        数独主菜单        \n" << std::endl;
        std::cout << "      1. 随机选题         " << std::endl;
        std::cout << "      2. 按题号选题         " << std::endl;
        std::cout << "      3. 自定义题         " << std::endl;
        std::cout << "      4. 返回上次存档         " << std::endl;
        std::cout << "      5. 运行数独生成器     " << std::endl;
        std::cout << "      0. 退出             " << std::endl;
        std::cout << "\n      请选择(0-5): ";
    }
};


class DifficultyMenu : public MenuInterface
{
    public:
        void displayMenu()const
        {
            std::cout << "选择难度: \n";
            std::cout << "1. 简单\n";
            std::cout << "2. 中等\n";
            std::cout << "3. 困难\n";
            std::cout << "      0. 退出             " << std::endl;
            std::cout << "\n      请选择(0-3): ";
        }
};


#endif