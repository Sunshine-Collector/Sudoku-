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
        if (sscanf_s(input.c_str(), "set R%dC%d=%d", &row, &col, &value) == 3 ||
            sscanf_s(input.c_str(), "set %d%d=%d", &row, &col, &value) == 3) {
            // У�����з�Χ
            if (row >= 1 && row <= 9 && col >= 1 && col <= 9 && value >= 1 && value <= 9) {
                sudoku.setValue(row - 1, col - 1, value);  // ����ֵ��ת����0����
                ui.displayMessage("���óɹ���");
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
}; #pragma once
