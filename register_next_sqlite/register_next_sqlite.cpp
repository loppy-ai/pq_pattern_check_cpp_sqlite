#include <sqlite3.h>
#include <element.h>
#include <size.h>
#include <print.h>
#include <sstream>

void recursionGenerate(int, int*, int*, sqlite3_stmt*, sqlite3*);

int main()
{
    int nest = 0;
    int next[NEXT_SIZE] = { 0 };
    int all_count = 0;
    sqlite3* db = NULL;
    sqlite3_stmt* pStmt;
    const char* path = "E:\\sqlite\\no_next_result.sqlite3";  //E:\\sqlite\\no_next_result.sqlite3
    int ret;

    // 接続
    ret = sqlite3_open_v2(
        path,
        &db,
        SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,
        nullptr
    );
    // 接続状態確認
    if (ret == SQLITE_OK) {
        printf("Connecttion Success!\n");
    }
    else {
        printf("Connection Failed...\n");
        cerr << sqlite3_errmsg(db) << endl;
        ret = sqlite3_close_v2(db);
        if (ret != SQLITE_OK) {
            printf("Disconnection Failed...\n");
        }
        return -1;
    }
    // 追加開始
    clock_t start_time = clock();
    cout << "\n" << "---------------------処理開始---------------------" << endl;
    // トランザクション開始
    sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);
    sqlite3_prepare_v2(
        db,
        "INSERT INTO result(id, next) VALUES(?, ?);",
        -1,
        &pStmt,
        nullptr
    );

    recursionGenerate(nest, next, &all_count, pStmt, db);
    cout << "count : " << all_count << endl;

    // コミット
    sqlite3_exec(db, "COMMIT TRANSACTION", 0, 0, 0);
    sqlite3_finalize(pStmt);
    // 追加終了
    clock_t end_time = clock();
    cout << "\n" << "---------------------処理終了---------------------" << endl;
    const double time = (static_cast<double>(end_time) - static_cast<double>(start_time)) / CLOCKS_PER_SEC;
    cout << "処理件数 : " << all_count << endl;
    cout << "処理時間 : " << time << endl;
    cout << endl;
    // 切断
    ret = sqlite3_close_v2(db);
    if (ret == SQLITE_OK) {
        printf("Disconnection Success!\n");
    }
    else {
        printf("Disconnection Failed...\n");
    }
    system("PAUSE");
}

void recursionGenerate(int nest, int* next, int* all_count, sqlite3_stmt* pStmt, sqlite3* db) {
    for (int c = 1; c <= COLOR_SIZE; ++c) {
        next[nest] = c;
        ++nest;
        if (nest == NEXT_SIZE) {
            // 件数
            ++(*all_count);
            // 文字列変換
            stringstream ss;
            ss << next[0] << next[1] << next[2] << next[3] << next[4] << next[5] << next[6] << next[7];
            string s = ss.str();
            // DB登録
            sqlite3_bind_int64(pStmt, 1, *all_count);
            sqlite3_bind_text(pStmt, 2, s.c_str(), NEXT_SIZE, SQLITE_TRANSIENT);
            while (sqlite3_step(pStmt) == SQLITE_BUSY) {}
            sqlite3_reset(pStmt);
            sqlite3_clear_bindings(pStmt);
        }
        else {
            recursionGenerate(nest, next, all_count, pStmt, db);
        }
        --nest;
    }
}