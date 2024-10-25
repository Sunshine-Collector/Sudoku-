#ifndef CELL_H
#define CELL_H

#include <vector>
#include <iostream>

class Cell {
public:
    // Ĭ�Ϲ��캯��
    Cell();
   
    // ���õ�Ԫ���ֵ
    void setValue(int val);
    // ��ȡ��Ԫ���ֵ
    int getValue() const;
    // ��Ӻ�ѡ��
    void addCandidate(int candidate);
    // �Ƴ���ѡ��
    void removeCandidate(int candidate);
    // ���ĳ�����Ƿ��Ǻ�ѡ��
    bool isCandidate(int candidate) const;
    // ��ȡ��ѡ������
    std::vector<int>& getCandidates();
    void clearCandidates() 
    {
        candidates.clear();  // ��պ�ѡ��������
    }
    int getvalue()
    {
        return value;
    }
    std::vector<int> getcandidates()
    {
        return candidates;
    }
    void print() const;
    bool operator==(const Cell& other) const {
        // ���ȱȽ� value ��Ա����
        if (value != other.value) {
            return false;
        }
        // Ȼ��Ƚ� candidates ����
        if (candidates.size() != other.candidates.size()) {
            return false;
        }
        for (size_t i = 0; i < candidates.size(); ++i) {
            if (candidates[i] != other.candidates[i]) {
                return false;
            }
        }
        return true;
    }
private:
    int value;  // ��Ԫ��ĵ�ǰֵ
    std::vector<int> candidates;  // ��ѡ������

};
#endif
