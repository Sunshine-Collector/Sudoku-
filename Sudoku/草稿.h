class SetCommand : public Command //set 置数
{
private:
    Sudoku& sudoku;
    UIInterface& ui;
    std::string input;

public:
    SetCommand(Sudoku& sudokuRef, UIInterface& uiRef, const std::string& inputCommand)
        : sudoku(sudokuRef), ui(uiRef), input(inputCommand) {}

    void execute() override {
        // 解析 `set RxCy=z` 或 `set xy=z`
        int row, col, value;
        if (sscanf_s(input.c_str(), "set R%dC%d=%d", &row, &col, &value) == 3 ||
            sscanf_s(input.c_str(), "set %d%d=%d", &row, &col, &value) == 3) {
            // 校验行列范围
            if (row >= 1 && row <= 9 && col >= 1 && col <= 9 && value >= 1 && value <= 9) {
                sudoku.setValue(row - 1, col - 1, value);  // 设置值，转换成0索引
                ui.displayMessage("设置成功！");
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
}; #pragma once
