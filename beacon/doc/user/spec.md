# beacon言語仕様
beaconの言語仕様に関するファイルです。  

# beaconを構成するファイル
## ライブラリ
beacon と同じディレクトリにある `script-lib` がライブラリとして参照されます。

## エントリポイント
コマンドによって指定します。
````
beacon --run main.bc
````

# コマンド引数
beaconはコマンドによって起動します。

## -r --run
指定のファイルを実行します。
````
./beacon -r main.bc
./beacon --run main.bc
````

## -a --ast
指定のファイルを解析してASTとして出力します。
````
./beacon -a main.bc
./beacon --ast main.bc
````

## -i --il
指定のファイルを解析してILとして出力します。
````
./beacon -i main.bc
./beacon --il main.bc
````

## -o --op
指定のファイル解析してオペコードとして出力します。
````
./beacon -o main.bc
./beacon --op main.bc
````

# ファイル
beaconスクリプトは `.bc` で作成します。  
その中に`トップレベル`を記述します。

# トップレベル
トップレベルには[`require` | `名前空間宣言` | `ステートメント`]を任意の数だけ配置できます。
````
require "hoge"
namespace mynamespace {
	...
}
printLine("HelloWorld");
````

# require
requireは beacon と同じディレクトリの`script-lib`を基準として相対パスでファイルを読み込みます。
````
require "beacon/unsafe/File"
````

# 名前空間宣言
名前空間宣言には[`名前空間宣言` | `型宣言`]を任意の数だけ配置できます。
````
namespace mynamespace {
	namespace subnamespace {
	}
	class Class[...] : ... {
		...
	}
	abstract class Class[...] : ... {
		...
	}
	interface Interface[...] : ... {
		...
	}
	enum Enum {
		...
	}
}
````
名前空間をネストして定義する場合には、`::`でインデントを浅くできます。
````
namespace beacon::lang {

}
````

# 型宣言
型宣言は[`クラス宣言` | `抽象クラス宣言` | `インターフェイス宣言` | `列挙宣言`]のいずれかです。

# クラス宣言
クラス宣言には`メンバー宣言ツリー`を任意の数配置できます。
````
class ClassName[TypeParameterList] : ExtendClassOpt, ImplementsList {
	MemberTree
}
````

# 抽象クラス宣言
クラス宣言には`メンバー宣言ツリー`を任意の数配置できます。  
- 抽象メソッドを定義できます。
- このクラスは `new` によって生成できません。
- 継承したクラスは全ての抽象メソッドを実装する必要があります。
````
abstract class ClassName[TypeParameterList] : ExtendClassOpt, ImplementsList {
	MemberTree
}
````

# インターフェイス宣言
インターフェイス宣言には[`メソッド` | `プロパティ`]を任意の数配置できます。  
構文規則ではコンストラクタやフィールドも配置可能ですが、  
コンパイル時点でエラーとして報告されます。
  
これを実装するクラスは定義された全てのメソッド/プロパティを実装する必要があります。
````
interface InterfaceName[TypeParameterList] : ImplementsList {
	MemberTree
}
````

# 列挙宣言
列挙宣言には`識別子`を任意の数だけ配置できます。  
実際にはクラスと静的整数フィールドに変換されます。  
これは 0 から開始します。
````
enum EnumName {
	IdentifierList
}
````

# メンバー宣言ツリー
メンバー宣言ツリーは { `アクセスレベル`と`メンバー宣言`のペア } のリストです。  
C++のものと概ね同じ書式をとります。
````
public ClassName {
	AccessLevel:
		MemberList
	AccessLevel:
		MemberList
}
````

# アクセスレベル
アクセスレベルはメンバー宣言の可視性を定義するキーワードです。  
[`public` | `private` | `protected`] のいずれかを使用できます。

# メンバー宣言
メンバー宣言は[`フィールド` | `プロパティ` | `コンストラクタ` | `メソッド` | `オペレーター`]のいずれかです。

# フィールド
フィールドはクラスに属性を定義します。  
初期値を省略する書式と初期値を指定する書式があります。  
省略された場合には型に応じてデフォルト値が設定されます。  
- Int = 0
- Double = 0.0
- Char = ¥0
- Bool = false
- そのほか = null
````
public:
	ModifierList FieldType FieldName;
	ModifierList FieldType FieldName = Expr;
````

# プロパティ
プロパティはクラスに属性を定義します。  
本文を省略した場合にはフィールドと同じ挙動です。
片方のみ本文を省略することは出来ません。  
省略しない場合、`defset`では`value`で代入される値を参照出来ます。
````
public:
	property PropertyType PropertyName {
		AccessLevel defset;
		AccessLevel defget;
	}

	property PropertyType PropertyName {
		AccessLevel defset {
			StatementList
		}
		AccessLevel defget {
			StatementList
		}
	}
````

# コンストラクタ
コンストラクタはクラスの生成方法を定義します。  
  
親クラスが空のコンストラクタを持っていない場合には、  
明示的に親クラスのコンストラクタを選択する必要があります。

````
public:
	def new(ParameterList) {
	}

	def new(ParameterList) : this(ArgumentList) {
	}

	def new(ParameterList) : super(ArgumentList) {
	}
````

# メソッド
メソッドはクラスに振る舞いを定義します。  
- 本文を省略する場合としない場合があります。  
- ネイティブメソッド、抽象メソッドの場合は省略しなければいけません。
- Voidを戻り値とするメソッドで`値を持つreturn`は使用できません。
- Voidを戻り値としないメソッドで`値を持たないreturn`は使用できません。
````
public:
	ModifierList MethodName (ParameterList) -> ReturnType ;
	ModifierList MethodName (ParameterList) -> ReturnType {
		StatementList
	}
````

# コルーチン
メソッドの中でも`Iterator`を返すインスタンスメソッドはコルーチンとして記述できます。
````
def seq(Int len) -> Iterator[Int] {
	var start = 0;
	while(start < len) {
		yield return start;
		start += 1;
	}
}
var iter = seq(10);
while(iter.moveNext()) {
	iter.current().printLine();
}
````

# オペレータ
オペレータはクラスに対して特定の演算子を利用できるようにします。  
- 必ず public である必要があります。
- 二項演算子であれば1個の引数をとります。
- 単項演算子であれば0個の引数をとります。
````
public:
	operator +(Object a) -> Object {
		StatementList
	}
````

# 修飾子
修飾子はメンバーに対して指定できるヒントです。  
[`static` | `native` | `final` | `abstract`] のいずれかです。

# static
staticは[`フィールド` | `プロパティ` | `メソッド`]に使用出来ます。  
static で修飾されたメンバーはクラス名でアクセスできます。
````
Console.writeLine("hello");
````

# native
nativeはメソッドにのみ使用できます。  
nativeで修飾されたメソッドは事前に登録されたCの関数ポインタへ移譲されます。

# final
finalは[`フィールド` | `プロパティ`]に使用できます。  
- finalで修飾された場合、再代入することは出来ません。
- コンストラクタで初期化するか、初期値を指定する必要があります。

# abstract
abstractはメソッドにのみ使用できます。  
必ずサブクラスで実装される必要があります。
````
public:
	def abstract call() -> Void;
````

# ステートメント
ステートメントは以下のいずれかです。
- `if`
- `while`
- `try`
- `throw`
- `defer`
- `variable_decl`
- `variable_init`
- `infereneced_init`
- `continue`
- `break`
- 'return'
- `yield return`
- `yield break`
- `assert`
- `factor ;`

# if
ifは条件によって処理を分岐するステートメントです。
````
if Expr {
	StatementList
}

if Expr {
	StatementList
} elif Expr {
	StatementList
}

if Expr {
	StatementList
} else {
	StatementList
}
````

# while
whileは条件を満たす限り処理を実行するステートメントです。
````
while Expr {
	StatementList
}
````


# try
tryは内側のステートメントで`例外`が発生した時、  
キャッチ節に実行をジャンプさせるステートメントです。
````
try {
	StatementList
} catch(TypeName Identifier) {
	StatementList
}
````

# throw
throwはメソッドを例外によって中断させるステートメントです。  
最寄りのキャッチ節までジャンプします。  
例外オブジェクトは捕捉されるかVMが終了されるまでGCから保護されます。
````
throw Expr;
````

# defer
deferはメソッドの最後で実行される処理を記述するステートメントです。  
例外が発生した場合でも必ず実行されます。  
deferを通った時点でのシンボルテーブルを記録し、GCから保護します。
````
defer Statement
````

# variable_decl
variable_declは変数を初期化せずに宣言だけするステートメントです。
````
TypeName Identifier;
````

# variable_init
variable_initは変数の宣言と初期化を同時に行うステートメントです。
````
TypeName Identifier = Expr;
````

# infereneced_init
infereneced_initは右辺から型を決定して初期化を行うステートメントです。
````
var str = "String";
var ival = 0;
````

# continue
continueはwhileの中でのみ使用可能なステートメントです。  
実行を中断してループの先頭に戻ります。
````
var offset = 0;
while(offset < 10) {
	if offset == 5 {
		continue;
	}
	printLine(offset)
}
````

# break
breakはwhileの中でのみ使用可能なステートメントです。  
実行を中断してループを抜けます。
````
var offset = 0;
while(offset < 10) {
	if offset == 5 {
		break;
	}
	printLine(offset)
}
````

# return
returnは処理を終了するステートメントです。  
- 値を返すものと返さないものがあります。
- Voidを戻り値とするメソッドから戻り値を伴う`return`はエラーになります。
- Voidを戻り値としないメソッドから戻り値を伴わない`return`はエラーになります。
````
return;
return Expr;
````

# yield return
yield returnは`コルーチン`の中でのみ使用可能です。  
処理を中断して値を返します。
````
def seq(Int len) -> Iterator[Int] {
	var start = 0;
	while(start < len) {
		yield return start;
		start += 1;
	}
}
var iter = seq(10);
while(iter.moveNext()) {
	iter.current().printLine();
}
````

# yield break
yield break`コルーチン`の中でのみ使用可能です。  
処理を終了します。
````
def seq2(Int len) -> Iterator[Int] {
	var start = 0;
	while(start < len) {
		if(start > 5) {
			yield break;
		}
		yield return start;
		start += 1;
	}
}
var iter = seq2(10);
while(iter.moveNext()) {
	iter.current().printLine();
}
````

# assert
assert は条件を満たさないときに例外をスローするステートメントです。  
メッセージを省略する版と省略しない版があります。  
省略した場合は条件式を文字列化して使用します。
````
assert(Expr);
assert(Expr, Message)
````

# ファクター
ファクターは以下のいずれかです。
- `int_literal`
- `double_literal`
- `char_literal`
- `string_literal`
- `bool_literal`
- `variable`
- `field_access`
- `indexer_access`
- `new_instance`
- `binary operator`
- `unary operator`
- `assign operator`
- `explicit operator`
- `call`
- `invoke`
- `static_invoke`
- `this`
- `super`
- `null`
- `as`

# int_literal
int_literalは整数リテラルによって表されるファクターです。  
````
0
````

# double_literal
double_literalは浮動小数リテラルによって表されるファクターです。
````
0.5
````

# char_literal
double_literalは文字リテラルによって表されるファクターです。
````
'a'
````

# string_literal
string_literalは文字列リテラルによって表されるファクターです。
````
"aaaa"
````

# bool_literal
bool_literalはtrue/falseによって表されるファクターです。
````
true
false
````

# variable
variableは識別子によって表されるファクターです。  
ローカル変数/メソッド実引数として解決できなかった場合、  
フィールド/プロパティとして解決します。
````
name
````

# field_access
field_accessはフィールドへのアクセスによって表されるファクターです。  
フィールドとして解決できなかった場合、  
プロパティとして解決します。
````
//instance field
hoge.name

//class field
namespace_name::Hoge.name
````

# indexer_access
indexer_accessは添字アクセス演算子によって表されるファクターです。
````
//0番目を参照する
arr(0)

//代入
arr(0) = 0;
````

# new_instance
new_instanceはクラスの生成によって表されるファクターです。
````
new Class();
new namespace::Class();
new Class[Int]();
new namespace::Class[Int]();
````

# binary operator
binary operatorは二項演算によって表されるファクターです。  
演算子と二つの引数をとります。
````
10 + 10
````

# unary operator
binary operatorは単項演算によって表されるファクターです。  
演算子と引数をとります。
````
-10
````

# assign operator
assign operatorは代入によって表されるファクターです。  
左辺は変数/プロパティ/インデクサーのいずれかである必要があります。
````
variable = 10;
variable.field = 10;
array(0) = 5;

variable += 10;
variable.field += 10;
array(0) += 5;
````

# explicit operator
explicit operatorは明示的な演算子の呼び出しです。  
Intなどのプリミティブなデータ型においても演算子オーバーロードは用意されていますが、  
通常の二項演算ではこれを呼び出すことが出来ません。  
しかし、明示的な呼び出しでは必ず演算子オーバーロードが呼び出されます。
````
10.+(5);
````

# call
callはthisに対するメソッド呼び出しです。  
this.method() の省略形です。
````
method();
````

# invoke
invokeはレシーバに対するメソッド呼び出しです。  
````
a.method();
````

# static_invoke
static_invokeはクラスに対するメソッド呼び出しです。
````
namespace::Class.method();
````

# this
thisは現在のオブジェクトを参照します。  
静的メソッドでは使用できません。
````
this
````

# super
superは現在のオブジェクトを親クラス型で参照します。  
静的メソッドでは使用できません。
````
super
````

# null
nullは何もないことを指す参照です。  
あらゆるデータ型の変数に代入できます。
````
null
````

# as
as はあるオブジェクトを別の型へ変換するファクターです。  
変換に失敗した場合には null が返されます。
````
factor as MyClass
````

# 使用できる演算子の一覧
短絡評価は未実装です。
````
+
-
*
/
%

|
||

&
&&

<<
>>

!=
==
<
>
<=
>=

=
+=
-=
*=
/=
%=
&=
|=
^=
<<=
>>=

-
!

#配列参照演算子
()
````

# オーバーロード可能な演算子一覧
````
+
-
*
/
%

|
||

&
&&

<<
>>

!=
==
<
>
<=
>=

-
!

#配列参照演算子
(&)
(=)
````