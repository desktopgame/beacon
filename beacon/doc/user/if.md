# if
**if** は特定の条件を満たす時に処理を実行する制御構造です。  
ぶら下り構文は使えません。

## 実装例
````
var text = Console.readLine();
var ival =text.toInt();
if(ival > 100) {
	Console.writeLine("ival > 100");
} elif(ival < 50) {
	Console.writeLine("ival < 50");
} else {
	Console.writeLine("else");
}
````