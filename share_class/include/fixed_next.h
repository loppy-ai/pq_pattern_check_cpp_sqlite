#pragma once
#include <next.h>

// �l�N�X�g�ϊ��g�p
constexpr int next_color_1[next_size] = { 1, 1, 1, 1, 1, 1, 1, 1 };
constexpr int next_color_2[next_size] = { 2, 2, 2, 2, 2, 2, 2, 2 };
constexpr int next_color_3[next_size] = { 3, 3, 3, 3, 3, 3, 3, 3 };
constexpr int next_color_4[next_size] = { 4, 4, 4, 4, 4, 4, 4, 4 };
constexpr int next_color_5[next_size] = { 5, 5, 5, 5, 5, 5, 5, 5 };
// �l�N�X�g�ϊ����g�p
constexpr int next_color_9[next_size] = { 9, 9, 9, 9, 9, 9, 9, 9 };

class Fixed_Next : public Next
{
private:
	void setFixedNext(const int);

public:
	Fixed_Next(const int);
	~Fixed_Next();
};