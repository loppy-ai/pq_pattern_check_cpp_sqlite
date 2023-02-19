#include <param_info.h>
#include <param.h>

Param_Info::Param_Info(char** argv)
{
    next_color              = atoi(argv[1]);
    board_pattern           = atoi(argv[2]);
    max_trace               = atoi(argv[3]);
    elimination_coefficient = atof(argv[4]);
    chain_coefficient       = atof(argv[5]);
    max_color               = atoi(argv[6]);
    max_connection          = (board_pattern < 100) ? 3 : 4;
    process_print_flag      = false;
    max_trace_print_flag    = true;
    chain_coefficient_list  = chain_coefficient_list_entity;
    setChainCoefficientList();
}

Param_Info::Param_Info(const std::string file_name)
{
    param::parameter param(file_name);
    next_color              = param.get<int>("next_color");
    board_pattern           = param.get<int>("board_pattern");
    max_trace               = 0;
    elimination_coefficient = param.get<double>("elimination_coefficient");
    chain_coefficient       = param.get<double>("chain_coefficient");
    max_color               = 0;
    max_connection          = (board_pattern < 100) ? 3 : 4;
    process_print_flag      = param.get<bool>("process_print_flag");
    max_trace_print_flag    = false;
    chain_coefficient_list  = chain_coefficient_list_entity;
    setChainCoefficientList();
}

Param_Info::~Param_Info()
{

}

// �l�N�X�g�̐F���擾
int Param_Info::getNextColor() const
{
    return next_color;
}

// �Ֆʃp�^�[�����擾
int Param_Info::getBoardPattern() const
{
    return board_pattern;
}

// �ő�Ȃ�����������擾
int Param_Info::getMaxTrace() const
{
    return max_trace;
}

// ���������W�����擾
double Param_Info::getEliminationCoefficient() const
{
    return elimination_coefficient;
}

// �A���W���{�����擾
double Param_Info::getChainCoefficient() const
{
    return chain_coefficient;
}

// ���߂����F���擾
int Param_Info::getMaxColor() const
{
    return max_color;
}

// �Ղ悪������ő匋�������擾
int Param_Info::getMaxConnection() const
{
    return max_connection;
}

// �A���{�����擾
double Param_Info::getChainMagnification(const int chain_count) const
{
    return chain_coefficient_list[chain_count];
}

// �A���{�����擾
double Param_Info::getChainMagnification(const int chain_count, const double chain_coefficient) const
{
    return 1 + basic_chain_coefficient[chain_count] * chain_coefficient;
}

// �A���W�������X�g�Ƃ��Đݒ�
void Param_Info::setChainCoefficientList()
{
    for (int i = 0; i < MAX_NUM_OF_CHAIN; ++i) {
        chain_coefficient_list_entity[i] = 1 + basic_chain_coefficient[i] * getChainCoefficient();
    }
}

// �A���ߒ���\�����邩����
bool Param_Info::isProcessPrint() const
{
    return process_print_flag;
}

// ���\��
void Param_Info::print() const
{
    std::string ipp = isProcessPrint() ? "�\������" : "�\�����Ȃ�";
    std::cout << "---------------------�ݒ���---------------------" << std::endl;
    std::cout << "�l�N�X�g�̐F       : " << getNextColor() << std::endl;
    std::cout << "�Ֆʃp�^�[��       : " << getBoardPattern() << std::endl;
    if (max_trace_print_flag) {
        std::cout << "�ő�Ȃ��������   : " << getMaxTrace() << std::endl;
    }
    std::cout << "���������W��       : " << getEliminationCoefficient() << std::endl;
    std::cout << "�A���W��           : " << getChainCoefficient() << std::endl;
    if (max_trace_print_flag) {
        std::cout << "���߂����F         : " << getMaxColor() << std::endl;
    }
    std::cout << "�����鎞�̌�����   : " << getMaxConnection() << std::endl;
    std::cout << "�A���ߒ��̕\��     : " << ipp << std::endl;
}