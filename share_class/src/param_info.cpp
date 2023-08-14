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
    next_color_print_flag   = true;
    chain_coefficient_list  = chain_coefficient_list_entity;
    setChainCoefficientList();
}

Param_Info::Param_Info(const string file_name, Caller caller)
{
    param::parameter param(file_name);
    switch (caller)
    {
    case DISPLAY:
        next_color = param.get<int>("next_color");
        board_pattern = param.get<int>("board_pattern");
        max_trace = 0;
        elimination_coefficient = param.get<double>("elimination_coefficient");
        chain_coefficient = param.get<double>("chain_coefficient");
        max_color = 0;
        max_connection = (board_pattern < 100) ? 3 : 4;
        process_print_flag = param.get<bool>("process_print_flag");
        max_trace_print_flag = false;
        next_color_print_flag = true;
        chain_coefficient_list = chain_coefficient_list_entity;
        setChainCoefficientList();
        break;
    case ANY_NEXT:
        next_color = 0;
        max_trace = param.get<int>("max_trace");
        board_pattern = 0;
        elimination_coefficient = param.get<double>("elimination_coefficient");
        chain_coefficient = 0.0;
        max_color = param.get<int>("max_color");
        max_connection = (board_pattern < 100) ? 3 : 4;
        process_print_flag = false;
        max_trace_print_flag = true;
        next_color_print_flag = false;
        chain_coefficient_list = chain_coefficient_list_entity;
        next_color_any = next_color_any_entity;
        break;
    default:
        break;
    }
}

Param_Info::~Param_Info()
{

}

// ネクストの色を取得
int Param_Info::getNextColor() const
{
    return next_color;
}

// 盤面パターンを設定
void Param_Info::setBoardPattern(const int no)
{
    board_pattern = no;
}

// 盤面パターンを取得
int Param_Info::getBoardPattern() const
{
    return board_pattern;
}

// 最大なぞり消し数を取得
int Param_Info::getMaxTrace() const
{
    return max_trace;
}

// 同時消し係数を取得
double Param_Info::getEliminationCoefficient() const
{
    return elimination_coefficient;
}

// 連鎖係数倍率を設定
void Param_Info::setChainCoefficient(const int no)
{
    if (no < 10) {
        // あんどうりんご・スペエコ
        chain_coefficient = 7.0;
    }
    else if (no > 200 && no < 210) {
        // しろいマール
        chain_coefficient = 10.0;
    }
    else if (no > 300 && no < 310) {
        // あたり＆プーボ
        chain_coefficient = 10.5;
    }
    else if (no > 400 && no < 410) {
        // なつぞらのアマノネ
        chain_coefficient = 10.5;
    }
    setChainCoefficientList();
}

// 連鎖係数倍率を取得
double Param_Info::getChainCoefficient() const
{
    return chain_coefficient;
}

// 求めたい色を取得
int Param_Info::getMaxColor() const
{
    return max_color;
}

// ぷよが消える最大結合数を取得
int Param_Info::getMaxConnection() const
{
    return max_connection;
}

// 最大結合数を設定
void Param_Info::setMaxConnection(const int no)
{
    max_connection = (no < 100) ? 3 : 4;
}

// 連鎖倍率を取得
double Param_Info::getChainMagnification(const int chain_count) const
{
    return chain_coefficient_list[chain_count];
}

// 連鎖倍率を取得
double Param_Info::getChainMagnification(const int chain_count, const double chain_coefficient) const
{
    return 1 + basic_chain_coefficient[chain_count] * chain_coefficient;
}

// 任意ネクストを設定
void Param_Info::setNextColorAny(const int* next)
{
    for (int i = 0; i < NEXT_SIZE; ++i) {
        next_color_any_entity[i] = next[i];
    }
}

// 設定された任意ネクストの色を取得
int* Param_Info::getNextColorAny() const
{
    return next_color_any;
}

// 連鎖係数をリストとして設定
void Param_Info::setChainCoefficientList()
{
    for (int i = 0; i < MAX_NUM_OF_CHAIN; ++i) {
        chain_coefficient_list_entity[i] = 1 + basic_chain_coefficient[i] * getChainCoefficient();
    }
}

// 連鎖過程を表示するか判定
bool Param_Info::isProcessPrint() const
{
    return process_print_flag;
}

// 情報表示
void Param_Info::print() const
{
    string ipp = isProcessPrint() ? "表示する" : "表示しない";
    cout << "-----------------設定情報-----------------" << endl;
    if (next_color_print_flag) {
        cout << "ネクストの色       : " << getNextColor() << endl;
    }
    else {
        cout << "入力したネクスト   : " << 
            next_color_any_entity[0] << 
            next_color_any_entity[1] << 
            next_color_any_entity[2] << 
            next_color_any_entity[3] << 
            next_color_any_entity[4] << 
            next_color_any_entity[5] <<
            next_color_any_entity[6] <<
            next_color_any_entity[7] << 
            endl;
    }
    cout << "盤面パターン       : " << getBoardPattern() << endl;
    if (max_trace_print_flag) {
        cout << "最大なぞり消し数   : " << getMaxTrace() << endl;
    }
    cout << "同時消し係数       : " << getEliminationCoefficient() << endl;
    cout << "連鎖係数           : " << getChainCoefficient() << endl;
    if (max_trace_print_flag) {
        cout << "求めたい色         : " << getMaxColor() << endl;
    }
    cout << "消える時の結合数   : " << getMaxConnection() << endl;
    cout << "連鎖過程の表示     : " << ipp << endl;
    cout << "------------------------------------------" << endl;
}