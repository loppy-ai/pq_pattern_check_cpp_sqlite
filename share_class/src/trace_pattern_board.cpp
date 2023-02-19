#include <trace_pattern_board.h>

Trace_Pattern_Board::Trace_Pattern_Board(const std::string file_name)
{
    error_flag = false;
	loadFromFile(file_name);
    if (isError()) exit(1);
}

Trace_Pattern_Board::~Trace_Pattern_Board()
{

}

// �t�@�C���ǂݍ��ݏ���
void Trace_Pattern_Board::loadFromFile(const std::string file_name)
{
    std::ifstream is(file_name);
    if (!is) {
        std::cout << "Error : �Ȃ�������p�^�[���t�@�C��������܂���" << std::endl;
        std::cout << std::endl;
        error_flag = true;
    }
    readFromStream(is);
}

// �t�@�C�����e�ǂݍ��ݏ���
void Trace_Pattern_Board::readFromStream(std::istream& is)
{
    std::string line;
    int i;
    int line_count = 0;
    while (getline(is, line)) {
        if (line.length() > 0 && line[0] == '#') {
            continue;
        }
        if (line.length() != COLUMN_SIZE && !error_flag) {
            std::cout << "Error : �Ȃ�������p�^�[���t�@�C���̗񐔂��Ⴂ�܂�" << std::endl;
            std::cout << std::endl;
            error_flag = true;
        }
        else {
            for (i = 0; i < COLUMN_SIZE; ++i) {
                setBoardElement(line_count * COLUMN_SIZE + i, line[i] - 48);
            }
            line_count++;
            if (line_count == ROW_SIZE) {
                break;
            }
        }
    }
    if (line_count != ROW_SIZE && !error_flag) {
        std::cout << "Error : �Ȃ�������p�^�[���t�@�C���̍s�����Ⴂ�܂�" << std::endl;
        std::cout << std::endl;
        error_flag = true;
    }
}

// �G���[����
bool Trace_Pattern_Board::isError()
{
    return error_flag;
}