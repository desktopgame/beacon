# beacon
beacon(ビーコン)は静的型付けのプログラミング言語です  

# ファイル
* bin --成果物
* obj --中間生成されるオブジェクトファイル
* src --ソースコード

# ブランチ
* **develop** が 開発中のブランチ
* **windows** が windows用ブランチ
* **master** が 最後のリリース

# ビルド
下記の二つの方法があります。  
どちらの場合でも **jdk1.8.0_151.jdk** が必要です。

## clang/make を使う方法
- clangコンパイラーをダウンロードする
- [Branch:master] から [master] を選択する
- このページの [Clone or Download] から [Download ZIP] を実行する
- makefileに指定された JNI のインクルードパスを修正する
- 次のコマンドを実行する
````
cd beacon/src
make
````
## visual-studio を使う方法
- [Branch:master] から [windows] を選択する
- このページの [Clone or Download] から [Download ZIP] を実行する
- beacon.sln を起動する
- インクルードパスとして JNI を参照できるようにする

# その他
もともと signal という名前で開発していた時の名残で、  
一部の命名で整合性が取れていないかもしれません。
(そのうち修正します。)

