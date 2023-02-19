@echo off

cd x64\Release

rem ネクスト/盤面/最大なぞり数/同時消し係数/連鎖係数/求める色
call find_the_best_pattern_sqlite 2 307 14 6.5 10.5 2

cd ../../
