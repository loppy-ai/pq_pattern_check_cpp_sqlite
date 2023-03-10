#pragma once
#include <iostream>
#include <string>
#include <size.h>
#include <element.h>

class Board
{
private:
	int board_entity[BOARD_SIZE] = { 0 };	// 盤面の実体
	int *board;								// 盤面アクセス用のアドレス

public:
	Board();
	~Board();

	int* getBoard();
	void setBoard(const int*);
	int getBoardElement(const int) const;
	void setBoardElement(const int, const int);
	bool isColorPuyo(const int) const;
	bool isInfluenced(const int) const;
	bool isNone(const int) const;
	bool isEliminationHappened() const;

	bool canGetUpperRow(const int) const;
	bool canGetRightColumn(const int) const;
	bool canGetLowerRow(const int) const;
	bool canGetLeftColumn(const int) const;

	bool isSameUpper(const int) const;
	bool isSameRight(const int) const;
	bool isSameLower(const int) const;
	bool isSameLeft(const int) const;

	void print() const;
	void print(const std::string) const;
};

