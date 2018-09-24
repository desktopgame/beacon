# メモリー管理
beaconにはデバッグ時のみ動作するメモリ管理の機構が存在します。  
- メモリリーク
- オーバーラン
- フリーされた後のポインタへのアクセス
  
などを検出することができます。  
[プログラム言語を作る](http://kmaebashi.com/programmer/devlang/index.html)で紹介されているメモリ管理の仕組みを参考に作っています。

# 仕組み
beaconはメモリ管理のためのラッパー関数を提供しています。  
デバッグ情報として**ファイル名**/**行番号**を使用するので、  
実際にはマクロとして呼び出します。  
このマクロはデバッグ時にはC標準の関数の呼び出しに置き換えられます。  
イメージ
````
mem_malloc(size, filename, lineno)
mem_realloc(block, new_size, filename, lineno)
mem_free(block, filename, lineno)

#define MEM_MALLOC(size) (mem_malloc(size, __FILE__, __LINE__))
#define MEM_REALLOC(block, size) (mem_realloc(block, size, __FILE__, __LINE__))
#define MEM_FREE(block) mem_free(block, __FILE__, __LINE__)
````

# メモリ構造
ラッパー版のmallocによって確保された領域は、  
それが呼ばれたファイル名や行番号などの情報と共に連結リストへ格納されます。
  
簡略図
````
*--------------*   *------------*
|slot(struct)  |   |arena(void*)|
|-filename     |   |-0xCD...    | <------ over run checker
|-lineno       |   |-user data  |    |
|-arena        |   |-0xCD...    | <--*
|-prev         |   *------------*
|-next         |
|-free_location|
|-free_lineno  |
|-freed        |
*--------------*
````

また、ユーザが要求したサイズよりも少しだけ大きい領域を確保します。  
これはオーバーランをチェックするための仕組みで、  
先頭と末尾が 4byte 分だけ 0xCD で埋められています。  
なので呼び出しに返される領域は 4byte だけポインタを進めたものです。
  
mallocやfreeが呼び出されると、  
連結リストの全ての要素で 0xCD で埋められているかチェックを行います。  
これによってオーバーランのチェックが可能です。

freeでは連結リストから正しく切り離したのちに 0xCD を含む領域を解放します。  
プログラムの最後で連結リストの先頭が **NULL** になっていればメモリリークがないことが確認できます。

# visual-studio
visual-studioでは組み込みのメモリ検査機能が備わっているので、  
`_MSC_VER` が定義されている場合にはそれを利用するようになっています。