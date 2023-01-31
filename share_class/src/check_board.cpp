#include "../include/check_board.h"

Check_Board::Check_Board()
{

}

Check_Board::~Check_Board()
{

}

// �m�F�ς�
bool Check_Board::isConfirmed(const int no) const
{
	switch (getBoardElement(no))
	{
	case Combined:		return true;	break;
	case Uncombined:	return true;	break;
	default:			return false;	break;
	}
	return false;
}

// �`�F�b�N����
bool Check_Board::isChecking(const int no) const
{
	if (getBoardElement(no) == Checking)	return true;
	return false;
}

// �����ς�
bool Check_Board::isCombined(const int no) const
{
	if (getBoardElement(no) == Combined)	return true;
	return false;
}

// ����v�f���`�F�b�N��Ԃɂ���
void Check_Board::setBoardElementChecking(const int no)
{
	setBoardElement(no, Checking);
}

// ����v�f��������Ԃɂ���
void Check_Board::setBoardElementCombined(const int no)
{
	setBoardElement(no, Combined);
}

// ����v�f�𖢌�����Ԃɂ���
void Check_Board::setBoardElementUncombined(const int no)
{
	setBoardElement(no, Uncombined);
}

// �オelement�Ɠ�����Ԃ�
bool Check_Board::checkUpper(const int no, const int element) const
{
	if (getBoardElement(no - column_size) == element)	return true;
	return false;
}

// �E��element�Ɠ�����Ԃ�
bool Check_Board::checkRight(const int no, const int element) const
{
	if (getBoardElement(no + 1) == element)	return true;
	return false;
}

// ����element�Ɠ�����Ԃ�
bool Check_Board::checkLower(const int no, const int element) const
{
	if (getBoardElement(no + column_size) == element)	return true;
	return false;
}

// ����element�Ɠ�����Ԃ�
bool Check_Board::checkLeft(const int no, const int element) const
{
	if (getBoardElement(no - 1) == element)	return true;
	return false;
}