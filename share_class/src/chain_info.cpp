#include <chain_info.h>

Chain_Info::Chain_Info(const Param_Info* pi, Next* next, Board* board, const Board* trace_pattern_board)
{
	chain(pi, next, board, trace_pattern_board);
}

Chain_Info::~Chain_Info()
{

}

// �A������
void Chain_Info::chain(const Param_Info* pi, Next* next, Board* board, const Board* trace_pattern_board)
{
	bool chaining_flag = true;
#ifdef SW_NEXT_FELL_END
	bool next_fell_flag = false;
#endif // SW_NEXT_FELL_END
#ifdef SW_DISP_RESULT
	if (pi->isProcessPrint()) {
	    std::cout << "---------------------�A���ߒ�---------------------" << std::endl;
	}
	debugPrint(pi, next, board, "default");
	debugPrint(pi, trace_pattern_board, "tracePattern");
#endif	// SW_DISP_RESULT
	if ((pi->getBoardPattern() > 200) && (pi->getBoardPattern() < 300)) {
		// ���낢�}�[���Ֆ�
		applyTracePatternBlue(board, trace_pattern_board);
	}
	else if ((pi->getBoardPattern() > 300) && (pi->getBoardPattern() < 400)) {
		// �����聕�v�[�{�Ֆ�
		applyTracePatternYellow(board, trace_pattern_board);
	}
	else if ((pi->getBoardPattern() > 400) && (pi->getBoardPattern() < 500)) {
		// �����聕�v�[�{�Ֆ�
		applyTracePatternPurple(board, trace_pattern_board);
	}
	else {
		// �Ֆʂɑ΂��ĂȂ�������p�^�[����K�p
		applyTracePattern(board, trace_pattern_board);
	}
#ifdef SW_DISP_RESULT
	debugPrint(pi, next, board, "applyedTracePattern");
#endif	// SW_DISP_RESULT
	// �����������𗎂Ƃ�
	dropBoard(board);
#ifdef SW_DISP_RESULT
	debugPrint(pi, next, board, "dropBoard");
#endif	// SW_DISP_RESULT

	// �A���������[�v
	for (int chain_count = 0; chain_count <= MAX_NUM_OF_CHAIN; /* no-increment */ ) {
		// �����`�F�b�N�p�ՖʃC���X�^���X�̐���
		Check_Board check_board;
		// �����`�F�b�N
		checkConnection(chain_count, pi, board, &check_board);
		if (board->isEliminationHappened()) {
			// �Ղ悪�������玟�̘A��
			++chain_count;
#ifdef SW_DISP_RESULT
			debugPrint(pi, next, board, "elimination");
			debugChain(pi, chain_count);
#endif	// SW_DISP_RESULT
			dropBoard(board);
#ifdef SW_DISP_RESULT
			debugPrint(pi, next, board, "dropBoard");
#endif	// SW_DISP_RESULT
#ifdef SW_NEXT_FELL_END
			// next�����������Ƃɂ��Ղ�����ł���ΏI���Ƃ���
			if (next_fell_flag) {
				num_of_chain = chain_count;
				break;
			}
#endif // SW_NEXT_FELL_END
		}
		else {
			// �Ղ悪�����Ȃ�������next�𗎂Ƃ�
			if (!dropNext(next, board)) {
				// next�������Ȃ��Ȃ�����A���I��
				chaining_flag = false;
			}
#ifdef SW_DISP_RESULT
			debugPrint(pi, next, board, "dropNext");
#endif	// SW_DISP_RESULT
#ifdef SW_NEXT_FELL_END
			// next��������
			next_fell_flag = true;
#endif // SW_NEXT_FELL_END
		}
		if (chaining_flag == false) {
			num_of_chain = chain_count;
			break;
		}
	}
}

// �Ȃ�������p�^�[����K�p
void Chain_Info::applyTracePattern(Board* board, const Board* trace_pattern_board) {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (trace_pattern_board->getBoardElement(i) == 1) {
			board->setBoardElement(i, Elimination);
		}
	}
}

// �Ȃ�������p�^�[����K�p�i���낢�}�[���p�j
void Chain_Info::applyTracePatternBlue(Board* board, const Board* trace_pattern_board) {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (trace_pattern_board->getBoardElement(i) == 1) {
			board->setBoardElement(i, Blue);
		}
	}
}

// �Ȃ�������p�^�[����K�p�i�����聕�v�[�{�p�j
void Chain_Info::applyTracePatternYellow(Board* board, const Board* trace_pattern_board) {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (trace_pattern_board->getBoardElement(i) == 1) {
			board->setBoardElement(i, Yellow);
		}
	}
}

// �Ȃ�������p�^�[����K�p�i�Ȃ���̃A�}�m�l�p�j
void Chain_Info::applyTracePatternPurple(Board* board, const Board* trace_pattern_board) {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (trace_pattern_board->getBoardElement(i) == 1) {
			board->setBoardElement(i, Purple);
		}
	}
}

// �������Ղ�̏�ɂ�����̂𗎂Ƃ�
void Chain_Info::dropBoard(Board* board)
{
	// 0:�Ȃ�����or�������ď����� 9:�����ď�����
	// �Ֆʑ���
	for (int i = 0; i < BOARD_SIZE; ++i) {
		// 0�ȊO�͎�������
		if (board->getBoardElement(END_OF_BOARD - i) != Elimination) {
			continue;
		}
		// 0��������1�������
		for (int target = END_OF_BOARD - i - COLUMN_SIZE; target >= 0; target -= COLUMN_SIZE) {
			if (board->getBoardElement(target) != Elimination) {
				// 1�オ0�ȊO�������痎�Ƃ��āA1���0�ɂ���
				board->setBoardElement(END_OF_BOARD - i, board->getBoardElement(target));
				board->setBoardElement(target, Elimination);
				break;
			}
		}
	}
	// �����ď������Ƃ����9�ɂ���
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (board->getBoardElement(i) == 0) {
			board->setBoardElement(i, None);
		}
	}
}

// �����`�F�b�N
void Chain_Info::checkConnection(const int chain_count, const Param_Info* pi, Board* board, Check_Board* check_board)
{
	const int max_connection = pi->getMaxConnection();

	// �F�Ղ�ȊO�̓`�F�b�N��(������)�ɂ���
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (!(board->isColorPuyo(i))) {
			check_board->setBoardElementUncombined(i);
		}
	}
	// �����`�F�b�N
	for (int i = 0; i < BOARD_SIZE; ++i) {
		// �m�肵�Ă������΂�
		if (check_board->isConfirmed(i)) {
			continue;
		}
		// ������
		int count = 0;
		// �ċA�����`�F�b�N
		recursionCheckConnection(i, board, check_board, &count);
		// i�Ԗڂ̂Ղ�͉��q�����Ă��邩���Ԃ��Ă���
		// �����鐔�����q�����Ă���ꍇ
		if (count >= pi->getMaxConnection()) {
			// ���i�[
			setElementCount(board->getBoardElement(i), chain_count, count);
			setSeparateCount(board->getBoardElement(i), chain_count);
			for (int j = 0; j < BOARD_SIZE; ++j) {
				if (check_board->isChecking(j)) {
					check_board->setBoardElementCombined(j);
				}
			}
		}
		// �����鐔�����q�����Ă��Ȃ������ꍇ
		else {
			for (int j = 0; j < BOARD_SIZE; ++j) {
				if (check_board->isChecking(j)) {
					check_board->setBoardElementUncombined(j);
				}
			}
		}
	}
	// �������Ă����Ƃ���̔Ֆʂ�0�ɂ���
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (check_board->isCombined(i)) {
			board->setBoardElement(i, Elimination);
		}
	}
	// ���͂̉e�����󂯂���̂̏���
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (board->isInfluenced(i)) {
			if ((board->canGetUpperRow(i) && check_board->checkUpper(i, Combined))
				|| (board->canGetRightColumn(i) && check_board->checkRight(i, Combined))
				|| (board->canGetLowerRow(i) && check_board->checkLower(i, Combined))
				|| (board->canGetLeftColumn(i) && check_board->checkLeft(i, Combined))) {
				checkConnectionOther(i, chain_count, board);
			}
		}
	}
}

// �����`�F�b�N�i�ċA�p�j
void Chain_Info::recursionCheckConnection(const int i, Board* board, Check_Board* check_board, int* count)
{
	// �m�F��
	check_board->setBoardElementChecking(i);
	// �����J�E���g+1
	++(*count);
	// �オ����
	if (check_board->canGetUpperRow(i)
		&& check_board->checkUpper(i, NoCheck)
		&& board->isSameUpper(i)) {
		recursionCheckConnection(i - COLUMN_SIZE, board, check_board, count);
	}
	// �E������
	if (check_board->canGetRightColumn(i)
		&& check_board->checkRight(i, NoCheck)
		&& board->isSameRight(i)) {
		recursionCheckConnection(i + 1, board, check_board, count);
	}
	// ��������
	if (check_board->canGetLowerRow(i)
		&& check_board->checkLower(i, NoCheck)
		&& board->isSameLower(i)) {
		recursionCheckConnection(i + COLUMN_SIZE, board, check_board, count);
	}
	// ��������
	if (check_board->canGetLeftColumn(i)
		&& check_board->checkLeft(i, NoCheck)
		&& board->isSameLeft(i)) {
		recursionCheckConnection(i - 1, board, check_board, count);
	}
}

// �������܂�ď�������̂̏���
void Chain_Info::checkConnectionOther(const int i, const int chain_count, Board* board)
{
	int color = board->getBoardElement(i);
	switch (color)
	{
	case Ojama:	board->setBoardElement(i, Elimination);	break;
	case Kata:	board->setBoardElement(i, Ojama);		break;	// �����Ղ�͏�����Ƃ�����܂Ղ�ɂȂ�
	case Heart:	board->setBoardElement(i, Elimination);	break;
	case Prism:	board->setBoardElement(i, Elimination);	break;
	default:											break;
	}
	setElementCount(color, chain_count, 1);
}

// �l�N�X�g�𗎂Ƃ�
bool Chain_Info::dropNext(Next* next, Board* board)
{
	bool drop_next_flag = false;
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (!board->isNone(END_OF_BOARD - i)) {
			continue;
		}
		if (!next->isNone((END_OF_BOARD - i) % COLUMN_SIZE)) {
			board->setBoardElement(END_OF_BOARD - i, next->getNextElement((END_OF_BOARD - i) % COLUMN_SIZE));
			next->setNextElement((END_OF_BOARD - i) % COLUMN_SIZE, None);
			drop_next_flag = true;
		}
	}
	return drop_next_flag;
}

// ����F�E����A���ł̏�������o�^
void Chain_Info::setElementCount(const int color, const int chain_count, const int count)
{
	switch (color)
	{
	case Red:		all_chain_info[chain_count].num_r += count;		break;
	case Blue:		all_chain_info[chain_count].num_b += count;		break;
	case Green:		all_chain_info[chain_count].num_g += count;		break;
	case Yellow:	all_chain_info[chain_count].num_y += count;		break;
	case Purple:	all_chain_info[chain_count].num_p += count;		break;
	case Ojama:		all_chain_info[chain_count].num_ojama += count;	break;
	case Kata:		all_chain_info[chain_count].num_kata += count;	break;
	case Heart:		all_chain_info[chain_count].num_heart += count;	break;
	case Prism:		all_chain_info[chain_count].num_prism += count;	break;
	default:														break;
	}
}

// ����F�E����A���ł̕�������o�^
void Chain_Info::setSeparateCount(const int color, const int chain_count)
{
	switch (color)
	{
	case Red:		all_chain_info[chain_count].sep_r += 1;		break;
	case Blue:		all_chain_info[chain_count].sep_b += 1;		break;
	case Green:		all_chain_info[chain_count].sep_g += 1;		break;
	case Yellow:	all_chain_info[chain_count].sep_y += 1;		break;
	case Purple:	all_chain_info[chain_count].sep_p += 1;		break;
	default:													break;
	}
}

// �Ֆʕ\��
void Chain_Info::debugPrint(const Param_Info* pi, const Next* next, const Board* board, const std::string str) const
{
	if (pi->isProcessPrint()) {
		std::cout << str << std::endl;
		next->print();
		std::cout << "---------------" << std::endl;
		board->print();
		std::cout << std::endl;
	}
}

// �Ֆʕ\��
void Chain_Info::debugPrint(const Param_Info* pi, const Board* board, const std::string str) const
{
	if (pi->isProcessPrint()) {
		std::cout << str << std::endl;
		std::cout << "0 0 0 0 0 0 0 0" << std::endl;
		std::cout << "---------------" << std::endl;
		board->print();
		std::cout << std::endl;
	}
}

// �A�������Ƃ̏��\��
void Chain_Info::debugChain(const Param_Info* pi, const int chain_count) const
{
	if (pi->isProcessPrint()) {
		int cc = chain_count - 1;
		std::cout << chain_count << "�A����" << std::endl;
		std::cout << "�Ԍ�:" << getElementCountPerColorAndChain(Red, cc) << " �ԕ���:" << getSeparateCountPerColorAndChain(Red, cc) << " �Ԕ{��:" << getMagnificationPerColorAndChain(pi, Red, cc) << std::endl;
		std::cout << "��:" << getElementCountPerColorAndChain(Blue, cc) << " ����:" << getSeparateCountPerColorAndChain(Blue, cc) << " �{��:" << getMagnificationPerColorAndChain(pi, Blue, cc) << std::endl;
		std::cout << "�Ό�:" << getElementCountPerColorAndChain(Green, cc) << " �Ε���:" << getSeparateCountPerColorAndChain(Green, cc) << " �Δ{��:" << getMagnificationPerColorAndChain(pi, Green, cc) << std::endl;
		std::cout << "����:" << getElementCountPerColorAndChain(Yellow, cc) << " ������:" << getSeparateCountPerColorAndChain(Yellow, cc) << " ���{��:" << getMagnificationPerColorAndChain(pi, Yellow, cc) << std::endl;
		std::cout << "����:" << getElementCountPerColorAndChain(Purple, cc) << " ������:" << getSeparateCountPerColorAndChain(Purple, cc) << " ���{��:" << getMagnificationPerColorAndChain(pi, Purple, cc) << std::endl;
		std::cout << "����:" << getElementCountPerChain(cc) << " ������:" << getSeparateCountPerChain(cc) << " ���{��:" << getMagnificationPerColorAndChain(pi, None, cc) << std::endl;
		std::cout << "�׌�:" << getElementCountPerColorAndChain(Ojama, cc) << " �Ō�:" << getElementCountPerColorAndChain(Kata, cc) << " �n��:" << getElementCountPerColorAndChain(Heart, cc) << " �v��:" << getElementCountPerColorAndChain(Prism, cc) << std::endl;
		std::cout << std::endl;
	}
}

// ����F�E����A���ł̏��������擾
int Chain_Info::getElementCountPerColorAndChain(const int color, const int chain_count) const
{
	switch (color)
	{
	case Red:		return all_chain_info[chain_count].num_r;		break;
	case Blue:		return all_chain_info[chain_count].num_b;		break;
	case Green:		return all_chain_info[chain_count].num_g;		break;
	case Yellow:	return all_chain_info[chain_count].num_y;		break;
	case Purple:	return all_chain_info[chain_count].num_p;		break;
	case Ojama:		return all_chain_info[chain_count].num_ojama;	break;
	case Kata:		return all_chain_info[chain_count].num_kata;	break;
	case Heart:		return all_chain_info[chain_count].num_heart;	break;
	case Prism:		return all_chain_info[chain_count].num_prism;	break;
	default:														break;
	}
	return 0;
}

// ����F�E����A���ł̕��������擾
int Chain_Info::getSeparateCountPerColorAndChain(const int color, const int chain_count) const
{
	switch (color)
	{
	case Red:		return all_chain_info[chain_count].sep_r;	break;
	case Blue:		return all_chain_info[chain_count].sep_b;	break;
	case Green:		return all_chain_info[chain_count].sep_g;	break;
	case Yellow:	return all_chain_info[chain_count].sep_y;	break;
	case Purple:	return all_chain_info[chain_count].sep_p;	break;
	default:													break;
	}
	return 0;
}


// ����A�����ł̑S���������擾
int Chain_Info::getSeparateCountPerChain(const int chain_count) const
{
	return getSeparateCountPerColorAndChain(Red, chain_count)
		+ getSeparateCountPerColorAndChain(Blue, chain_count)
		+ getSeparateCountPerColorAndChain(Green, chain_count)
		+ getSeparateCountPerColorAndChain(Yellow, chain_count)
		+ getSeparateCountPerColorAndChain(Purple, chain_count);
}

// ����F�E����A���ł̔{�����擾
double Chain_Info::getMagnificationPerColorAndChain(const Param_Info* pi, const int color, const int chain_count) const
{
	switch (color)
	{
	case Red:
	case Blue:
	case Green:
	case Yellow:
	case Purple:
		// (�A���W�� * (1 + (�����ɏ������� - 3or4) * 0.15 * ���������W��)) * ������ + 3 * �v���{�̐�
		return (pi->getChainMagnification(chain_count) * (1 + (getElementCountPerChain(chain_count) - pi->getMaxConnection()) * 0.15 * pi->getEliminationCoefficient())) * getSeparateCountPerColorAndChain(color, chain_count) + 3 * getElementCountPerColorAndChain(Prism, chain_count);
		break;
	case None:	// ���C���h
		return (pi->getChainMagnification(chain_count) * (1 + (getElementCountPerChain(chain_count) - pi->getMaxConnection()) * 0.15 * pi->getEliminationCoefficient())) * getSeparateCountPerChain(chain_count) + 3 * getElementCountPerColorAndChain(Prism, chain_count);
		break;
	default:
		break;
	}
	return 0.0;
}

// ����F�E����A���ł̔{�����擾
double Chain_Info::getMagnificationPerColorAndChain(const Param_Info* pi, const double elimination_coefficient, const double chain_coefficient, const int color, const int chain_count) const
{
	switch (color)
	{
	case Red:
	case Blue:
	case Green:
	case Yellow:
	case Purple:
		// (�A���W�� * (1 + (�����ɏ������� - 3or4) * 0.15 * ���������W��)) * ������ + 3 * �v���{�̐�
		return (pi->getChainMagnification(chain_count, chain_coefficient) * (1 + (getElementCountPerChain(chain_count) - pi->getMaxConnection()) * 0.15 * elimination_coefficient)) * getSeparateCountPerColorAndChain(color, chain_count) + 3 * getElementCountPerColorAndChain(Prism, chain_count);
		break;
	case None:	// ���C���h
		return (pi->getChainMagnification(chain_count, chain_coefficient) * (1 + (getElementCountPerChain(chain_count) - pi->getMaxConnection()) * 0.15 * elimination_coefficient)) * getSeparateCountPerChain(chain_count) + 3 * getElementCountPerColorAndChain(Prism, chain_count);
		break;
	default:
		break;
	}
	return 0.0;
}

// �ő�A�������擾
int Chain_Info::getNumOfChain() const
{
	return num_of_chain;
}

// ����F�̑S���������擾
int Chain_Info::getElementCountPerColor(const int color) const
{
	int sum = 0;
	for (int i = 0; i < getNumOfChain(); ++i) {
		sum += getElementCountPerColorAndChain(color, i);
	}
	return sum;
}

// ����A���̑S���������擾
int Chain_Info::getElementCountPerChain(const int chain_count) const
{
	return getElementCountPerColorAndChain(Red, chain_count)
		+ getElementCountPerColorAndChain(Blue, chain_count)
		+ getElementCountPerColorAndChain(Green, chain_count)
		+ getElementCountPerColorAndChain(Yellow, chain_count)
		+ getElementCountPerColorAndChain(Purple, chain_count)
		+ getElementCountPerColorAndChain(Ojama, chain_count)
		+ getElementCountPerColorAndChain(Kata, chain_count)
		+ getElementCountPerColorAndChain(Prism, chain_count);
}

// ����F�̍��v�{�����擾
double Chain_Info::getMagnificationPerColor(const Param_Info* pi, const int color) const
{
	double sum = 0.0;
	for (int i = 0; i < getNumOfChain(); ++i) {
		sum += getMagnificationPerColorAndChain(pi, color, i);
	}
	return sum;
}

// ����F�̍��v�{�����擾
double Chain_Info::getMagnificationPerColor(const Param_Info* pi, const double elimination_coefficient, const double chain_coefficient, const int color) const
{
	double sum = 0.0;
	for (int i = 0; i < getNumOfChain(); ++i) {
		sum += getMagnificationPerColorAndChain(pi, elimination_coefficient, chain_coefficient, color, i);
	}
	return sum;
}