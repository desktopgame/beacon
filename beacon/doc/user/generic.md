# generic
ジェネリックはまだ実装途中です。  
現在は型の境界の指定が出来ません。

## 実装例
Vectorをそのまま抜粋
````
require "beacon/lang/Array"
require "beacon/lang/Exception"

namespace beacon::lang {
	class Vector[T] : Iterable[T] {
		private:
		Array[T] proxy;
		Int length;
		Int capacity;

		public:
		def new() {
			init();
		}

		def push(T o) -> Void {
			if(this.length < this.capacity) {
				this.proxy.set(this.length, o);
			} elif (this.length >= this.capacity) {
				var newLen = this.length + (this.length / 2);
				var newArr = new Array[T](newLen);
				Array.copy[T](this.proxy, 0, newArr, 0, this.length);
				this.proxy = newArr;
				this.proxy.set(this.length, o);
			}
			this.length = this.length + 1;
		}

		def pop() -> T {
			if(this.length == 0) {
				throw new Exception("not added any objects");
			}
			var ret = this.proxy.get(this.length - 1);
			this.length = this.length - 1;
			return ret;
		}

		def top() -> T {
			if(length == 0) {
				throw new Exception("not added any objects");
			}
			return proxy.get(length - 1);
		}

		def set(Int index, T a) -> Void {
			this.checkRange(index);
			this.proxy.set(index, a);
		}

		def get(Int index) -> T {
			this.checkRange(index);
			return this.proxy.get(index);
		}

		def remove(Int index) -> T {
			T ret = get(index);
			Int offs = index + 1;
			while(offs < length) {
				set(offs - 1, get(offs));
				offs = offs + 1;
			}
			this.length = length - 1;
			return ret;
		}

		def clear() -> Void {
			init();
		}

		def length() -> Int {
			return this.length;
		}

		def iterate() -> Iterator[T] {
			var offset = 0;
			while(offset < this.length()) {
				yield return this.get(offset);
				offset += 1;
			}
		}

		def toArray() -> Array[T] {
			var ret = new Array[T](length());
			Array.copy[T](this.proxy, 0, ret, 0, this.length);
			return ret;
		}

		operator <<(T e) -> Vector[T] {
			push(e);
			return this;
		}

		private:
		def init() -> Void {
			this.length = 0;
			this.capacity = 16;
			this.proxy = new Array[T](this.capacity);
		}

		def checkRange(Int index) -> Void {
			if(index < 0 || index >= this.length) {
				throw new Exception("Out Of Range");
			}
		}
	}
}
````