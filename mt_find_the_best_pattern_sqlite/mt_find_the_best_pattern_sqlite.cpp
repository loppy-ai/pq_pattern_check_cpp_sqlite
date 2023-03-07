#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <sqlite3.h>
#include <param_info.h>
#include <board.h>
#include <fixed_next.h>
#include <fixed_board.h>
#include <chain_info.h>
#include <print.h>
#include <size.h>
#include <bitset>
#include <thread>

long long result_board[THREAD_COUNT] = {0};
double result_magnification[THREAD_COUNT] = {0.0};

void search(int, long long, long long, Param_Info*);
long long getTracePatternSize(const int);

int main(int argc, char** argv)
{
    // パラメータ設定読み込み
    Param_Info pi(argv);
    long long trace_pattern_count = getTracePatternSize(pi.getMaxTrace());          // なぞり消しパターンの総数
    long long split_arr[THREAD_COUNT + 1] = { 0 };
    double page = (double)trace_pattern_count / THREAD_COUNT;
    for (int i = 1; i <= THREAD_COUNT; ++i) {
        split_arr[i] = (long long)(page * i);
    }

    pi.print(); // ---設定情報---
    clock_t start_time = clock();

    // マルチスレッド処理としてsearch()を呼び出す
    thread threads[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; ++i) {
        threads[i] = thread(search, i, split_arr[i + 1] - split_arr[i], split_arr[i], &pi);
    }
    for (int i = 0; i < THREAD_COUNT; ++i) {
        threads[i].join();
    }

    // 各スレッドの最上位から全体の最上位を決定
    long long all_max_board = -1;
    double all_max_magnification = 0.0;
    for (int i = 0; i < THREAD_COUNT; ++i) {
        if (all_max_magnification < result_magnification[i]) {
            all_max_magnification = result_magnification[i];
            all_max_board = result_board[i];
        }
    }

    // 時間表示
    clock_t end_time = clock();
    cout << endl;
    const double time = (static_cast<double>(end_time) - static_cast<double>(start_time)) / CLOCKS_PER_SEC;
    cout << "処理時間 : " << time << endl;
    cout << endl;

    // ファイル出力
    stringstream file_name_stream;
    file_name_stream << pi.getNextColor() << "_" << pi.getBoardPattern() << "_" << pi.getMaxTrace() << "_" << pi.getEliminationCoefficient() << "_" << pi.getChainCoefficient() << "_" << pi.getMaxColor() << ".txt";

    ofstream outputfile(file_name_stream.str());
    outputfile << "ネクストの色       : " << pi.getNextColor() << "\n";
    outputfile << "盤面パターン       : " << pi.getBoardPattern() << "\n";
    outputfile << "最大なぞり消し数   : " << pi.getMaxTrace() << "\n";
    outputfile << "同時消し係数       : " << pi.getEliminationCoefficient() << "\n";
    outputfile << "連鎖係数           : " << pi.getChainCoefficient() << "\n";
    outputfile << "求めたい色         : " << pi.getMaxColor() << "\n";
    outputfile << "消える時の結合数   : " << pi.getMaxConnection() << "\n";
    outputfile << "\n";
    // 結果表示のためにもう一度計算
    Fixed_Next fnext(pi.getNextColor());
    Fixed_Board fboard(pi.getBoardPattern());
    bitset<BOARD_SIZE> bs(all_max_board);
    // なぞり消し盤面設定
    Board all_max_tpb;
    for (int j = 0; j < BOARD_SIZE; ++j) {
        all_max_tpb.setBoardElement(j, bs[j]);
    }
    Chain_Info ci(&pi, &fnext, &fboard, &all_max_tpb);
    for (int j = 0; j < ROW_SIZE; ++j) {
        outputfile
            << all_max_tpb.getBoardElement(j * COLUMN_SIZE)
            << all_max_tpb.getBoardElement(j * COLUMN_SIZE + 1)
            << all_max_tpb.getBoardElement(j * COLUMN_SIZE + 2)
            << all_max_tpb.getBoardElement(j * COLUMN_SIZE + 3)
            << all_max_tpb.getBoardElement(j * COLUMN_SIZE + 4)
            << all_max_tpb.getBoardElement(j * COLUMN_SIZE + 5)
            << all_max_tpb.getBoardElement(j * COLUMN_SIZE + 6)
            << all_max_tpb.getBoardElement(j * COLUMN_SIZE + 7) << "\n";
    }
    outputfile << "\n";
    outputfile << "-----------------------------------------" << "\n";
    outputfile << "|   色   |消去数|  倍率  |  発生値倍率  |" << "\n";
    outputfile << "-----------------------------------------" << "\n";
    outputfile << "|   赤   |" << right << setw(6) << ci.getElementCountPerColor(Red) << "|" << right << setw(8) << fixed << setprecision(2) << ci.getMagnificationPerColor(&pi, Red) << "|" << right << setw(8) << fixed << setprecision(2) << ci.getMagnificationPerColor(&pi, Red) * 6.0 << "(x6.0)|" << "\n";
    outputfile << "|   青   |" << right << setw(6) << ci.getElementCountPerColor(Blue) << "|" << right << setw(8) << fixed << setprecision(2) << ci.getMagnificationPerColor(&pi, Blue) << "|" << right << setw(8) << fixed << setprecision(2) << ci.getMagnificationPerColor(&pi, Blue) * 6.2 << "(x6.2)|" << "\n";
    outputfile << "|   緑   |" << right << setw(6) << ci.getElementCountPerColor(Green) << "|" << right << setw(8) << fixed << setprecision(2) << ci.getMagnificationPerColor(&pi, Green) << "|" << right << setw(8) << fixed << setprecision(2) << ci.getMagnificationPerColor(&pi, Green) * 4.5 << "(x4.5)|" << "\n";
    outputfile << "|   黄   |" << right << setw(6) << ci.getElementCountPerColor(Yellow) << "|" << right << setw(8) << fixed << setprecision(2) << ci.getMagnificationPerColor(&pi, Yellow) << "|" << right << setw(8) << fixed << setprecision(2) << ci.getMagnificationPerColor(&pi, Yellow) * 5.5 << "(x5.5)|" << "\n";
    outputfile << "|   紫   |" << right << setw(6) << ci.getElementCountPerColor(Purple) << "|" << right << setw(8) << fixed << setprecision(2) << ci.getMagnificationPerColor(&pi, Purple) << "|" << right << setw(8) << fixed << setprecision(2) << ci.getMagnificationPerColor(&pi, Purple) * 5.5 << "(x5.5)|" << "\n";
    outputfile << "|ワイルド| ---- |" << right << setw(8) << fixed << setprecision(2) << ci.getMagnificationPerColor(&pi, None) << "|" << right << setw(8) << fixed << setprecision(2) << ci.getMagnificationPerColor(&pi, None) * 2.2 << "(x2.2)|" << "\n";
    outputfile << "-----------------------------------------" << "\n";
    outputfile << "\n";

    outputfile << "処理時間(s) : " << time;
    outputfile << "\n";
    outputfile.close();
}

void search(int ThreadID, long long page, long long offset, Param_Info* pi)
{
    long long max_board = -1;
    double max_magnification = 0.0;

    sqlite3* db = NULL;
    sqlite3_stmt* pStmt;
    const char* path = "E:\\sqlite\\tp_int64_16.sqlite3";
    int ret;

    // DB接続
    ret = sqlite3_open_v2(
        path,
        &db,
        SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,
        nullptr
    );

    // トランザクション開始
    sqlite3_exec(db, "BEGIN IMMEDIATE TRANSACTION", nullptr, nullptr, nullptr);
    sqlite3_prepare_v2(
        db,
        "SELECT board FROM pattern LIMIT ? OFFSET ?;",
        -1,
        &pStmt,
        nullptr
    );
    sqlite3_bind_int64(pStmt, 1, page);
    sqlite3_bind_int64(pStmt, 2, page * ThreadID);

    while (sqlite3_step(pStmt) == SQLITE_ROW) {
        // 48文字のデータ
        long long board = sqlite3_column_int64(pStmt, 0);
        bitset<BOARD_SIZE> bs(board);
        // なぞり消し盤面設定
        Board tpb;
        for (int j = 0; j < BOARD_SIZE; ++j) {
            tpb.setBoardElement(j, bs[j]);
        }

        // 初期盤面設定
        Fixed_Next fnext(pi->getNextColor());
        Fixed_Board fboard(pi->getBoardPattern());
        // 連鎖情報生成
        Chain_Info ci(pi, &fnext, &fboard, &tpb);
        // 最大チェック
        double magnification = ci.getMagnificationPerColor(pi, pi->getMaxColor());
        int prism_count = ci.getElementCountPerColor(Prism);
        int blue_count = ci.getElementCountPerColor(Blue);
        if ((pi->getBoardPattern() > 210) && (pi->getBoardPattern() < 220) && (prism_count == 0)) {
            continue;   // しろいマール盤面でプリズムボールを消していなかったら何もしない
        }
        if ((pi->getBoardPattern() > 310) && (pi->getBoardPattern() < 320) && (prism_count == 0)) {
            continue;   // あたり＆プーボ盤面でプリズムボールを消していなかったら何もしない
        }
        // 更新の必要があるか確認
        if (max_magnification < magnification)
        {
            max_magnification = magnification;
            max_board = board;
        }
    }
    sqlite3_reset(pStmt);
    sqlite3_clear_bindings(pStmt);

    // コミット
    sqlite3_exec(db, "COMMIT TRANSACTION", 0, 0, 0);
    sqlite3_finalize(pStmt);

    // DB切断
    ret = sqlite3_close_v2(db);
    if (ret != SQLITE_OK) {
        printf("Disconnection Failed...\n");
    }

    result_magnification[ThreadID] = max_magnification;
    result_board[ThreadID] = max_board;
}

long long getTracePatternSize(const int max_trace)
{
    long long size = 0;
    switch (max_trace)
    {
    case 1:
        size = 48;
        break;
    case 2:
        size = 200;
        break;
    case 3:
        size = 804;
        break;
    case 4:
        size = 3435;
        break;
    case 5:
        size = 15359;
        break;
    case 6:
        size = 70147;
        break;
    case 7:
        size = 320111;
        break;
    case 8:
        size = 1438335;
        break;
    case 9:
        size = 6300691;
        break;
    case 10:
        size = 26702013;
        break;
    case 11:
        size = 108735877;
        break;
    case 12:
        size = 422742049;
        break;
    case 13:
        size = 1559392541;
        break;
    case 14:
        size = 5425777501;
        break;
    case 15:
        size = 17710655729;
        break;
    case 16:
        size = 53964309390;
        break;
    default:
        break;
    }
    return size;
}