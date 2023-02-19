#include <board.h>

Board::Board()
{
	board = board_entity;
}

Board::~Board()
{

}

// �Ֆʂ̎擾
int* Board::getBoard()
{
	return board;
}

// �Ֆʂ̐ݒ�
void Board::setBoard(const int* input_board)
{
	std::memcpy(board, input_board, BOARD_SIZE * 4);	// int:4byte
}

// �Ֆʂ̗v�f���擾
int Board::getBoardElement(const int no) const
{
	return board[no];
}

// �Ֆʂɗv�f��ݒ�
void Board::setBoardElement(const int no, const int val)
{
	board[no] = val;
}

// �F�Ղ悩
bool Board::isColorPuyo(const int no) const
{
	if (getBoardElement(no) <= Purple) {
		return true;
	}
	switch (getBoardElement(no))
	{
	case Ojama:	return false;	break;
	case Kata:	return false;	break;
	case Heart:	return false;	break;
	case None:	return false;	break;
	case Prism:	return false;	break;
	default:	return true;	break;
	}
	return true;
}

// ���͂Ɋ������܂�ď����邩
bool Board::isInfluenced(const int no) const
{
	if (getBoardElement(no) <= Purple) {
		return false;
	}
	switch (getBoardElement(no))
	{
	case Ojama:	return true;	break;
	case Kata:	return true;	break;
	case Heart:	return true;	break;
	case Prism:	return true;	break;
	default:	return false;	break;
	}
	return false;
}

// �Ղ悪���݂��Ȃ���
bool Board::isNone(const int no) const
{
	if (getBoardElement(no) == None)	return true;
	return false;
}

// �Ղ�̏������N��������
bool Board::isEliminationHappened() const
{
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (getBoardElement(i) == Elimination)	return true;
	}
	return false;
}

// ��i�����邩
bool Board::canGetUpperRow(const int no) const
{
	if (no >= COLUMN_SIZE)	return true;
	return false;
}

// �E�񂪂��邩
bool Board::canGetRightColumn(const int no) const
{
	if ((no & (COLUMN_SIZE - 1)) != COLUMN_SIZE - 1)	return true;
	return false;
}

// ���i�����邩
bool Board::canGetLowerRow(const int no) const
{
	if (no < BOARD_SIZE - COLUMN_SIZE)	return true;
	return false;
}

// ���񂪂��邩
bool Board::canGetLeftColumn(const int no) const
{
	if ((no & (COLUMN_SIZE - 1)) != 0)	return true;
	return false;
}

// ���݂̉ӏ�����̐F�Ɠ�����
bool Board::isSameUpper(const int no) const
{
	if (getBoardElement(no) == getBoardElement(no - COLUMN_SIZE))	return true;
	return false;
}

// ���݂̉ӏ����E�̐F�Ɠ�����
bool Board::isSameRight(const int no) const
{
	if (getBoardElement(no) == getBoardElement(no + 1))	return true;
	return false;
}

// ���݂̉ӏ������̐F�Ɠ�����
bool Board::isSameLower(const int no) const
{
	if (getBoardElement(no) == getBoardElement(no + COLUMN_SIZE))	return true;
	return false;
}

// ���݂̉ӏ������̐F�Ɠ�����
bool Board::isSameLeft(const int no) const
{
	if (getBoardElement(no) == getBoardElement(no - 1))	return true;
	return false;
}

// �Ֆʕ\��
void Board::print() const
{
	std::string str_board[COLUMN_SIZE];
	for (int i = 0; i < ROW_SIZE; ++i) {
		for (int j = 0; j < COLUMN_SIZE; ++j) {
			if (getBoardElement(i * COLUMN_SIZE + j) == None) {
				str_board[j] = ".";
			}
			else {
				str_board[j] = std::to_string(getBoardElement(i * COLUMN_SIZE + j));
			}
		}
		std::cout 
			<< str_board[0] << " "
			<< str_board[1] << " "
			<< str_board[2] << " "
			<< str_board[3] << " "
			<< str_board[4] << " "
			<< str_board[5] << " "
			<< str_board[6] << " "
			<< str_board[7] << " "
			<< std::endl;
	}
}

// �Ֆʕ\��
void Board::print(const std::string title) const
{
	std::cout << title << std::endl;
	Board::print();
	std::cout << std::endl;
}