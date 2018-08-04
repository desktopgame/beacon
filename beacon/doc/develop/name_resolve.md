名前解決演算子に関するメモ

# 名前解決演算子
RubyやC++では、 **::** を使用して定数を参照できます。  

stdに対する名前解決の例
--
    std::cout << "HelloWorld" << std::endl;

名前空間に使用する場合
--
    boost::filesystem::path

# 名前空間
JavaやC#では名前空間(パッケージ)を **.** で連結します。

HelloWorldの例
--
	System.out.println("HelloWorld");

# フィールドアクセス
Javaでは . を使ってクラスの値を参照できます。

Pointの例
--
	point.x = 10

# フィールドアクセスと名前解決の併用
実現したいシンタックス
--
	Namespace::SubDir::Class.name = "Foo"
	point.x = "Foo"
	dist = point.distance()

名前空間の区切りに **::** を使用して、  
フィールドアクセスに **.** を使用する場合には構文規則に注意が必要です。

構文規則の例
--
	primary
		: ...
		| primary COLON2 IDENTITIFER

恐らくこのような規則が必要です。  
これだと名前空間だけでなく、  
戻り値や変数に対しても :: によるアクセスが可能になってしまいます。  
これは一度ASTに変換してしまった後でエラーとして報告するしかなさそうです。

もしくは、 :: によるアクセスを実装する方法もあります。  
というか C++ では実際にそれが可能らしい？  
[Why does C++ need the scope resolution operator?
](https://stackoverflow.com/questions/9338217/why-does-c-need-the-scope-resolution-operator)