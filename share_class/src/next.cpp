#include "../include/next.h"

Next::Next()
{
	next = next_entity;
}

Next::~Next()
{

}

// �l�N�X�g�S�Ă�����F�ɐݒ�
void Next::setNext(const int* input_next)
{
	std::memcpy(next, input_next, next_size * 4);	// int:4byte
}

// �l�N�X�g�̗v�f���擾
int Next::getNextElement(const int no) const
{
	return next[no];
}

// �l�N�X�g�̗v�f��ݒ�
void Next::setNextElement(const int no, const int val)
{
	next[no] = val;
}

// �l�N�X�g�����邩
bool Next::isNone(const int no) const
{
	if (getNextElement(no) == None)	return true;
	return false;
}

// �Ֆʕ\��
void Next::print() const
{
	std::string str_next[column_size];
	for (int i = 0; i < column_size; ++i) {
		if (getNextElement(i) == None) {
			str_next[i] = ".";
		}
		else {
			str_next[i] = std::to_string(getNextElement(i));
		}
	}
	std::cout
		<< str_next[0] << " "
		<< str_next[1] << " "
		<< str_next[2] << " "
		<< str_next[3] << " "
		<< str_next[4] << " "
		<< str_next[5] << " "
		<< str_next[6] << " "
		<< str_next[7] << " "
		<< std::endl;
}