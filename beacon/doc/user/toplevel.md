# toplevel
beaconはトップレベルに文を配置できます。  

## 実装例
この時の printLine は組み込み関数ではなく Object#printLine です。  
トップレベルの this は World です。
````
printLine("HelloWorld");
````

## 関数を定義する例
この場合、seq は World に定義されます。  
トップレベルの関数には修飾子やアクセスレベルを定義できません。
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

## クラスを定義する例
それらをする場合はトップレベルにクラスを定義します。
````
//http://yucchi.jp/blog/?p=570
//N-Queen
namespace samples {
	class NQ {
		private:
		static final Int QUEENS = 4;
		static final Array[Int] VERTICAL = new Array[Int](QUEENS);
		static final Array[Bool] HORIZONTAL = new Array[Bool](QUEENS);
		static final Array[Bool] DIP_POSITIVE = new Array[Bool](QUEENS * 2 -1);
		static final Array[Bool] DIP_NEGATIVE = new Array[Bool](QUEENS * 2 - 1);
		static final Bool SAFE = false;
		static final Bool OUT = true;
		static Int counter;

		public:
		def static main() -> Void {
			trySet(0);
			if(counter < 1) {
				Console.writeLine("can't put");
			} else {
				Console.write("count: ");
				Console.writeLine(counter);
			}
		}

		private:
		def static trySet(Int i) -> Void {
			var j = 0;
			while(j < QUEENS) {
				if((HORIZONTAL.get(j) == SAFE) &&
				   (DIP_POSITIVE.get(i + j) == SAFE) &&
				   (DIP_NEGATIVE.get((i - j) + (QUEENS - 1)) == SAFE)) {
				   VERTICAL.set(i, j);
				   assert (HORIZONTAL.get(j)) == SAFE;
				   assert (DIP_POSITIVE.get(i + j)) == SAFE;
				   assert (DIP_NEGATIVE.get((i - j) + (QUEENS - 1))) == SAFE;
					if(i == (QUEENS - 1)) {
					   counter += 1;
					   printBoard();
				   } else {
					   HORIZONTAL.set(j, OUT);
					   DIP_POSITIVE.set(i + j, OUT);
					   DIP_NEGATIVE.set((i - j) + (QUEENS - 1), OUT);
					   trySet(i + 1);
					   HORIZONTAL.set(j, SAFE);
					   DIP_POSITIVE.set(i + j, SAFE);
					   DIP_NEGATIVE.set((i - j) + (QUEENS - 1), SAFE);
					}
				}
				j += 1;
			}
		}
		def static printBoard() -> Void {
			//phase: n
			Console.write("phase: ");
			Console.writeLine(counter);
			var i = 0;
			var j = 0;
			while(i < QUEENS) {
				while(j < QUEENS) {
					if(j == VERTICAL.get(i)) {
						Console.write("@ ");
					} else {
						Console.write("_ ");
					}
					j += 1;
				}
				i += 1;
				j = 0;
				Console.writeLine(":");
			}
		}
	}
}
//Console.writeLine("aa");
samples::NQ.main();
````