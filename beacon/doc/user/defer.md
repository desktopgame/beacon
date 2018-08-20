# defer
golangに搭載されている機能とおおよそ同じです。  
例外が発生してもしなくても必ず最後に実行されるステートメントを記述します。

## 実装例
サンプルより抜粋
````
require "beacon/unsafe/File"
var f = beacon::unsafe::File.open("File.text", "w");
defer f.close();
f.puts("HelloWorld\n");
f.puts("2D OR NOT 2D");
````