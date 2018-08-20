# as
C#に実装されているものとだいたい同じです。  
変換できなかった場合には null が返されます。  
型に互換性がないことが明らかな時はコンパイルできません。

## 実装例
````
var str = "Hello";
//これはだめ
//printLine(str as Int);

Object o = str;
printLine(o as Int);
````