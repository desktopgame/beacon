# enum
**enum** は連続する整数定数を定義する構文です。  
クラスと整数型の再代入不可の静的フィールドに変換されます。

## 実装例
````
enum TokenId {
	Value,
	Add,
	Sub,
	Mul,
	Div,
	Mod,
	LBrace,
	RBrace,
	Space,
	Undef,
}
````