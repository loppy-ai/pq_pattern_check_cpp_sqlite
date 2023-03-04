#pragma once
#include <next.h>

// ネクスト変換使用
constexpr int next_color_1[NEXT_SIZE] = { 1, 1, 1, 1, 1, 1, 1, 1 };
constexpr int next_color_2[NEXT_SIZE] = { 2, 2, 2, 2, 2, 2, 2, 2 };
constexpr int next_color_3[NEXT_SIZE] = { 3, 3, 3, 3, 3, 3, 3, 3 };
constexpr int next_color_4[NEXT_SIZE] = { 4, 4, 4, 4, 4, 4, 4, 4 };
constexpr int next_color_5[NEXT_SIZE] = { 5, 5, 5, 5, 5, 5, 5, 5 };
// ネクスト変換未使用
constexpr int next_color_9[NEXT_SIZE] = { 9, 9, 9, 9, 9, 9, 9, 9 };

class Fixed_Next : public Next
{
private:
	void setFixedNext(const int);
	void setFixedNext(int*);

public:
	Fixed_Next(const int);
	Fixed_Next(int*);
	~Fixed_Next();
};