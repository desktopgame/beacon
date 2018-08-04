ジェネリックの実装に関するメモ

# ジェネリック
型に紐づけられる変数

仮型引数
--
    class List<T> { ... }

この場合の T を**仮型引数**と呼びます。

実型引数
--
    var list = new List<Hoge>()

この場合の Hoge を**実型引数**と呼びます。

# 型消去
Javaでは下記のように型引数の違いによるオーバーロードはできません。

オーバーロード
--
    private void myMethod(ArrayList<Hoge> hogeList) { ... }
    private void myMethod(ArrayList<Foo> fooList) { ... }

# 推測
Javaコンパイラの実装の動きはわかりませんが、  
クラスを表現するために次のような構造があるんじゃないかと思ってます。  
全て仮想コードです。

ClassRegistry
--
    class ClassRegistry {
        void register(Class class)
    }

TypeParameter
--
    class TypeParameter {
        //ここに T とかがはいる
        //これが仮型引数
        String name
    }

Class
--
    class Class {
        TypeParameter[] getTypeParameters()
        Field[] getFields()
        Method[] getMethods()
    }

GenericType
--
    class GenericType {
        Class coreClass;
        //これが実型引数
        GenericType[] arguments;
    }

Object
--
    class Object {
        VTable vptr;
        GenericType type;
        Object[] fields;
    }

仮引数を持つクラスはその型が定義された時点で登録できます。  
実引数を持つ List\<Hoge> はそれが実体化されるコードを発見した時点で登録出来ます。  
できますが、いわゆる型消去では List\<T> しか登録してないんじゃないでしょうか。

* List\<T> List\<Int> List\<Double> をどうやってレジストリへ登録するか?
    * 単純なマップにクラス一覧を格納している場合キーが重複してしまいます。  
      まあやろうと思えば区別をつけることはできるかもしれません。
* **仮引数を持つクラス**と**実引数をもつクラス**の区別
    * これも面倒なだけでなんとかなるかもしれません。

## typeof
Javaが typeof のようなものを用意していない理由がよくわからないのですが、  
型消去でも typeof は実装することが出来るかもしれません。  

上述のように Object が実体化された型(GenericType)への参照を持っているなら、  
それを単に実装言語自体のクラスクラスにして返すだけのはず
  
静的呼び出しだけをサポートするなら、
Object自身がどの型に属しているかは不要な情報だから  
実体化された型(GenericType)への参照をもっていないのかもしれません。  

### 補足(型情報)
フィールドは配列をそのまま使うし  
メソッドの一覧はVTableへの添え字アクセスを使用するので
Objectが型への参照を持つ必要はないはず。

Objectがクラス階層のトップの最初のフィールドを 0 として  
連番でフィールドを格納するリストを持っていれば、  
put_field/get_fieldにオペランドとして整数を渡せば静的型付けのフィールドアクセスは実装可能

vtableも大体同じ

# beaconでは
型消去で実装する予定  

# 参考
[ジェネリックの実現方法](http://ufcpp.net/study/csharp/sp2_generics.html?p=2)

