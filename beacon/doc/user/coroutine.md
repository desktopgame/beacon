# coroutine
コルーチンはイテレータの糖衣構文です。  
イテレータを簡単に記述するための仕組みで、C#のそれを参考にしています。  
  
beacon の iterator が Java のそれと違うのは、  
このコルーチンを実装するためです。  
以下に Java/Iterator と C#/Enumerator を簡単に比較します。

## Java/Iterator
````
boolean hasNext();

E next();
````

## C#/Enumerator
````
bool moveNext();

E current { get };
````

java の設計では次の要素を取得すると共に位置を一つ進めます。  
こちらの方法だとコルーチンを実装することが出来ません。  
  
javaの設計で問題になるのはイテレータの最後を取り出す時です。  
実はC#のコルーチンは最後が **yield return** で終わる必要はありません。  
最後まで実行して false を返すだけです。

## イメージ(C#)
````
定義
Enumerator<int> hoge() {
	yield return 0;
	Console.writeLine("Hoge");
}
---
呼び出し
var enumerator = hoge();
while(enumerator.moveNext()) {
	Console.writeLine(enumerator.current)
}
---
出力
0
Hoge
````

最後が **yield return** でない時にコンパイルエラーにするなどの方法もありますが、  
C#の方が書きやすいと判断したのでそれに合わせています。  


## サンプル
Array.bc より抜粋
````
def iterate() -> Iterator[T] {
	var offset = 0;
	while(offset < this.length()) {
		yield return this.get(offset);
		offset += 1;
	}
}
````

中断する例
````
def seq(Int len) -> Iterator[Int] {
	var start = 0;
	while(start < len) {
		if(start > 5) {
			yield break;
		}
		yield return start;
		start += 1;
	}
}
var iter = seq(10);
while(iter.moveNext()) {
	iter.current().printLine();
}
````
