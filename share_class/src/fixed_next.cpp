#include <fixed_next.h>

Fixed_Next::Fixed_Next(const int next_color)
{
	setFixedNext(next_color);
}

Fixed_Next::Fixed_Next(int* next_color_any)
{
	setFixedNext(next_color_any);
}

Fixed_Next::~Fixed_Next()
{

}

// 指定ネクストをセット
void Fixed_Next::setFixedNext(const int next_color)
{
	switch (next_color) {
	case 1:	setNext(next_color_1);	break;
	case 2:	setNext(next_color_2);	break;
	case 3: setNext(next_color_3);	break;
	case 4:	setNext(next_color_4);	break;
	case 5:	setNext(next_color_5);	break;
	case 9:	setNext(next_color_9);	break;
	default:
		std::cout << "Error : next_colorの設定に誤りがあります" << std::endl;
		std::cout << std::endl;
		exit(1);
		break;
	}
}

// 任意ネクストをセット
void Fixed_Next::setFixedNext(int* next_color_any)
{
	for (int i = 0; i < NEXT_SIZE; ++i) {
		setNextElement(i, next_color_any[i]);
	}
}