# error
beaconがコンパイルをどのようにエラーを処理するかについて示します。

# エラーの報告
`error.h`にて定義されます。
````
void bc_error_throw(bc_error_id id, ...);
void bc_error_vthrow(bc_error_id id, va_list ap);
````

# エラーの検出
エラーが起きると、内部的に保存されたフラグがオンになるので、  
これをチェックして処理を中断することでトップレベルまで戻ります。
````
bc_error_id bc_error_last();
````

# リリースビルド
ただし、リリースビルドではエラーが発生したら即座に`abort()`します。  
JNIから呼び出されているときは例外で、この場合はやはりフラグを検査しながらトップレベルへ戻ります。