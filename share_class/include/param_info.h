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
	int next_color;						// �l�N�X�g�̐F
	int board_pattern;					// �Ֆʃp�^�[��
	int max_trace;						// �ő�Ȃ��������
	double elimination_coefficient;		// ���������W��
	double chain_coefficient;			// �A���W���{��
	int max_color;						// �ő�l�����߂����F
	int max_connection;					// �ő匋����
	bool max_trace_print_flag;			// �ő�Ȃ���������\���t���O
	bool process_print_flag;			// �A���ߒ��\���t���O
	bool next_color_print_flag;			// �l�N�X�g�̐F�\���t���O
	double chain_coefficient_list_entity[MAX_NUM_OF_CHAIN] = { 0.0 };	// �A���W�����X�g�̎���
	double *chain_coefficient_list;										// �A���W�����X�g�̃A�h���X
	int next_color_any_entity[NEXT_SIZE] = { 0 };						// �C�Ӄl�N�X�g�̎���
	int *next_color_any;												// �C�Ӄl�N�X�g�̃A�h���X
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