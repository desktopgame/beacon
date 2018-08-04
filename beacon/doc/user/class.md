# class
class(クラス)はユーザが定義できる型です。  
以下のような構文で定義します。
````
namespace sample {
	class Person {
		public:
		Int age;
		String name;

		def new(String name, Int age) {
			this.name = name;
			this.age = age;
		}

		def toString() -> String {
			return name;
		}
	}
}
````
クラスを生成するには new を使用して次のように記述します。
````
var p = new sample::Person("beacon", 1);
printLine(p);
````