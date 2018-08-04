# interface
インターフェイスはメソッドだけを持つことができる型です。  
クラスに実装して使います。
````
namespace sample {
	interface Callable {
		public:
		def call() -> Void;
	}
	class Print : Callable {
		public:
		def new(String text) {
			this.text = text;
		}

		def call() -> Void {
			printLine(text);
		}

		private:
		String text;
	}
}
````
インターフェイス型には、それを実装したクラスを代入できます。
````
sample::Callable c = new sample::Print("hello");
c.call();
````