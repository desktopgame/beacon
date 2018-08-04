仮想関数テーブルの実装に関するメモ

# 仮想関数テーブル
仮想関数テーブルは、  
オーバーライド可能な関数の一覧です。  

一般的には クラスが 仮想関数テーブルを持っていて、  
それから生成されたオブジェクトは 仮想関数テーブルへのポインタ(いわゆるvptr)を持っているようです。  

ここから僕がどう実装したかのメモなので、  
もしかしたらもっといい方法があるかもしれません。  

次のようなクラス階層を考えます。

A.beacon
--
    class A { AMethod, BMethod, CMethod }

B.beacon
--
    class B { AMethod(override), XMethod, YMethod }

Aのもつvtableはこうなります。
* [0] AMethod
* [1] BMethod
* [2] CMethod

Bのもつvtableはこうなります。
* [0] AMethod(override)
* [1] BMethod
* [2] CMethod
* [3] XMethod
* [4] YMethod

同じシグネチャのメソッドが現れた場合、  
その位置をオーバライドされた後のメソッドで上書きする感じです。  

# インターフェイス(もしくは多重継承)

次のような関係を考えます。

X.beacon
--
    interface X { AbstractA AbstractB }

Y.beacon
--
    class Y : X { Hoge Foo AbstractA AbstractB }

main.beacon
--
    X xVal = new Y()
    xVal.AbstractA()

ここで重要なのは、X型の変数に対して呼び出している点です。  
XインターフェースでAbstractAが現れるのは 0 番目ですが、  
実装クラスでは 2 番目に表れています。  

0 が invokevirtual に渡されれば、  
Hogeが呼び出されてしまいます。  

# invokeinterface
Javaではこのような名前で呼ばれているようです。  
あるメソッドの呼び出しを解析するとき、  
そのレシーバがインターフェースであるかどうかはちゃんと事前に知ることが出来ます。
  
そこで、レシーバがインターフェースである場合には、  
invokeinterfaceというものを渡します。  
この命令のオペランドには、
* 型を指すためのインデックス
* インターフェースの中で何番目であるかを示す添え字
  
を渡します。  
(前者については型を通し番号のリストに登録しているだけです。)

また、クラスには vtable に加えて、  
vtable のリストを追加します。  
これを仮に vtableVec と呼称するとします。

このなかのvtableはインターフェースと同じ順番で、  
ぴったり対応付けられるように実装メソッドが並びます。  

invokeinterfaceが呼ばれたとき  
* 通し番号からインターフェイスを取得します。  
* 添え字を使ってそのインターフェースのどのメソッドかを取得します。
* 演算スタックからポップします。
* 演算スタックの クラス->vtableVec から、インターフェースに対応する vtable を取り出す。
* その vtable に 最初に使った添え字を当てれば実装メソッドが取り出せる。

