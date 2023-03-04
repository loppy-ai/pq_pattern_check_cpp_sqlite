#pragma once
#include <iostream>
#include <string>
#include <size.h>

using namespace std;
constexpr double basic_chain_coefficient[MAX_NUM_OF_CHAIN] = { 0, 0.4, 0.7, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4 };

enum Caller
{
	DISPLAY,	// display_of_chain_results
	ANY_NEXT	// any_next
};

class Param_Info
{
private:
	int next_color;						// ネクストの色
	int board_pattern;					// 盤面パターン
	int max_trace;						// 最大なぞり消し数
	double elimination_coefficient;		// 同時消し係数
	double chain_coefficient;			// 連鎖係数倍率
	int max_color;						// 最大値を求めたい色
	int max_connection;					// 最大結合数
	bool max_trace_print_flag;			// 最大なぞり消し数表示フラグ
	bool process_print_flag;			// 連鎖過程表示フラグ
	bool next_color_print_flag;			// ネクストの色表示フラグ
	double chain_coefficient_list_entity[MAX_NUM_OF_CHAIN] = { 0.0 };	// 連鎖係数リストの実体
	double *chain_coefficient_list;										// 連鎖係数リストのアドレス
	int next_color_any_entity[NEXT_SIZE] = { 0 };						// 任意ネクストの実体
	int *next_color_any;												// 任意ネクストのアドレス
	void setChainCoefficientList();

public:
	Param_Info(char**);
	Param_Info(const std::string, Caller);
	~Param_Info();
	int getNextColor() const;
	void setBoardPattern(const int);
	int getBoardPattern() const;
	int getMaxTrace() const;
	double getEliminationCoefficient() const;
	void setChainCoefficient(const int);
	double getChainCoefficient() const;
	int getMaxColor() const;
	int getMaxConnection() const;
	double getChainMagnification(const int) const;
	double getChainMagnification(const int, const double) const;
	void setNextColorAny(const int*);
	int* getNextColorAny() const;
	bool isProcessPrint() const;
	void print() const;
};