# pq_pattern_check_cpp_sqlite
特殊なぞり最適解算出

---

## register_sqlite
なぞり方のデータベースを作成します。
### 手順
1. https://sqlite.org/download.html から以下をDL
    - Precompiled Binaries for Windows
    - Alternative Source Code Formats
1. Precompiled Binaries for Windowsからlibを作成
1. register_sqliteプロジェクトに、Alternative Source Code Formatsのsqlite3.cppを追加
1. プロジェクトと同じ階層にsqlite3ディレクトリを作成し、DLしたファイルすべてを格納
1. プロジェクトと同じ階層にあるNODATA_tp_int64.sqlite3を任意の場所にコピーし、適当な名前にリネーム
1. register_sqlite.cpp main()内の変数pathを、上記のファイルを指すように変更
1. 必要に応じて最大なぞり消し数を変更
1. releaseビルドを実行
1. register_sqlite.exeを実行

### 注意
- DBのファイルサイズは最大なぞり消し数16個で **900GB** 弱になります
- 実行時間はCPU/SSDの性能によって大幅に変動します
  - まずは少ないなぞり消し数で作成してみて、時間を見積もることをお勧めします
    - 10個消し（2600万通り）
    - 13個消し（16億通り）
    - 15個消し（177億通り）
    - 16個消し（540億通り）

---

## find_the_best_pattern_sqlite / mt_find_the_best_pattern_sqlite
特殊なぞりの最適解をファイル出力します。（mtはマルチスレッドで処理を行います）
### 手順
1. find_the_best_pattern_sqliteプロジェクトにAlternative Source Code Formatsのsqlite3.cppを追加
1. register_sqliteの手順を一通り実行し、DBを作成
1. find_the_best_pattern_sqlite.cpp main()内の変数pathを、上記のDBを指すように変更
   - mt版の場合はsearch()内
2. releaseビルドを実行
3. プロジェクトと同じ階層にあるfind_the_best_pattern_sqlite.batを編集
4. 求めたい設定を引数で指定
5. バッチファイルを実行

### 引数
- ネクスト
    |赤|青|緑|黄|紫|なし|
    |:-:|:-:|:-:|:-:|:-:|:-:|
    |1|2|3|4|5|9|
- 盤面
    |盤面|番号|
    |:-:|:-:|
    |とくべつルール1|1 - 8|
    |連鎖のタネ1|101 - 116|
    |連鎖のタネ2|151 - 166|
    |とくべつルール2|201 - 208|
    |とくべつルール2<br>プリボ消|211 - 218|
    |とくべつルール3|301 - 308|
    |とくべつルール3<br>プリボ消|311 - 318|
- 最大なぞり数
    - **DB作成時に指定した最大なぞり消し数より大きな値を指定しないでください**
- 同時消し係数
- 連鎖係数
    - 整数でも小数でも入力可
- (最大倍率を)求める色
    |赤|青|緑|黄|紫|ワイルド|
    |:-:|:-:|:-:|:-:|:-:|:-:|
    |1|2|3|4|5|9|

### 出力
- x64\releaseディレクトリに、引数と同じファイル名のtxtファイルが出力されます
- 倍率1位～3位のなぞり方・その時の倍率が記録されています
  - mt版は1位のみ

### 注意
- **mt版を使用する場合、size.hのTHREAD_COUNTを使用するCPUのスレッド数にしてください**
- なぞり消し数に応じて処理時間が増えます

---
## any_next
ユーザが入力したネクストにおける最適解を表示します。

### 手順
1. any_nextプロジェクトにAlternative Source Code Formatsのsqlite3.cppを追加
1. register_sqliteの手順を一通り実行し、DBを作成
1. any_next.cpp search()内の変数pathを、上記のDBを指すように変更
1. releaseビルドを実行
1. x64\Release\any_next_config.cfgを編集
1. any_next.exeを実行
1. 任意のネクストの数字8文字を入力（赤:1～紫:5）
1. 盤面の番号を入力（find_the_best_pattern_sqliteの番号と同様）

### 出力
- 画面に表示されます

### 注意
- **マルチスレッド処理専用**
- **size.hのTHREAD_COUNTを使用するCPUのスレッド数にしてください**
- なぞり消し数に応じて処理時間が増えます

---

## display_of_chain_results
連鎖結果を表示します。
### 手順
1. releaseビルドを実行
1. x64\Release\param_config.cfgを編集
    - =の後の数字を計算したい値に書き換えてください
1. x64\Release\trace_pattern.tpbを編集
    - なぞる箇所を1に設定してください
1. display_of_chain_results.exeを実行
