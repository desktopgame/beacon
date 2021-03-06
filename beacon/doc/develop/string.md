# 文字列の管理
beaconのコンパイラではソースコードをいくつかの中間表現に変換しますが、  
その過程で文字列をどう管理するかについてです。  

# 文字列プールの初期化
最初と最後に必ず呼び出す必要があります。
````
void string_pool_init();
void string_pool_destroy();
````

# 文字列プールへの登録
文字列プールへ登録するとで、符号化された整数が返却されます。  
既に登録されている場合は前回の値を返します。  
この時の検索は二分探索で行われます。
````
string_view string_pool_intern(const char*);
````

# 文字列の変換
符号化された整数と文字列との相互変換の関数です。
````
const char* string_pool_ref2str(string_view);
string_view string_pool_str2ref(const char*);
````

# コンパイラとの連携
パーサが識別子を発見した時、それを符号化してからASTへ渡す実装になっています。  
AST以降の中間表現でもこの符号を複製しているだけです。  
また、フィールドやメソッドを解決するときにもこの符号を比較することで同じ名前かどうかを判定しています。