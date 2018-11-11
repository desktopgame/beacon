# ビルド
下記の二つの方法があります。  
どちらの場合でも **jdk1.8.0_151.jdk** が必要です。

## Mac環境
- clangコンパイラーをダウンロードする
- [Branch:master] から [master] を選択する
- このページの [Clone or Download] から [Download ZIP] を実行する
- 次のコマンドを実行する
````
cd beacon/src
--
↓のどっちか
cmake -D CMAKE_BUILD_TYPE=Release -D JNI_INCLUDE_DIR=jni.hのパス -D JNI_NATIVE_INCLUDE_DIR=jni_md.hのパス .
cmake -D CMAKE_BUILD_TYPE=Debug -D JNI_INCLUDE_DIR=jni.hのパス -D JNI_NATIVE_INCLUDE_DIR=jni_md.hのパス .
--
make
````
## visual-studio を使う方法
準備中