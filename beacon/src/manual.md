# manual
このプロジェクトで用意しているスクリプト/タスクについてのマニュアル

## makefile
### make db
デバッグ情報付きのビルド。  
カバレッジのための情報も一緒に出力される。

### make rb
リリース用ビルド。

### make cov
`make db` -> `テストの実行` -> `ruby lcov.rb` をまとめて実行する。  
src/lcovにはカバレッジの結果がhtmlで出力される。

### make clean
objフォルダを綺麗にする。

## task(vscode)
上述した makefile の機能には vscode の task 機能からもアクセスできます。