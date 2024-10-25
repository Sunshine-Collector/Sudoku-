#include "Cell.h"
#include <algorithm>

// ���캯��
Cell::Cell() : value(0) {
    // ��ʼ��ʱ��ֵ����Ϊ0
}

// ���õ�Ԫ���ֵ
void Cell::setValue(int val) 
{
    value = val;
}

// ��ȡ��Ԫ���ֵ
int Cell::getValue() const 
{

    return value;
}

// ��Ӻ�ѡ����������
void Cell::addCandidate(int candidate) 
{
        candidates.push_back(candidate);
        std::sort(candidates.begin(), candidates.end());  //���ֺ�ѡ������
}

// �Ƴ���ѡ��
void Cell::removeCandidate(int candidate) {
    auto it = std::find(candidates.begin(), candidates.end(), candidate);
    if (it != candidates.end()) {
        *it = 0; // ���ҵ���Ԫ�ص�ֵ��Ϊ��
    }
}

// ���ĳ�����Ƿ��Ǻ�ѡ��
bool Cell::isCandidate(int candidate) const 
{
    return std::find(candidates.begin(), candidates.end(), candidate) != candidates.end();
}

// ��ȡ��ѡ������
std::vector<int>& Cell::getCandidates(){
    return candidates;
}

// ��ӡ��Ԫ����Ϣ
void Cell::print() const {
    if (value != 0) {
        std::cout << value;
    }
    else {
        std::cout << ".";
    }
}