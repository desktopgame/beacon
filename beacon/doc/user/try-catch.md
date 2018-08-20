# try-catch
javaやC#に搭載されている機能とおおよそ同じです。  
finally はありません。  
また、javaのマルチキャッチ節もまだ実装されていません。

## 実装例
テストコードより抜粋
````
var num = -1;
try {
	except::Root.panic();
} catch(except::AException ae) {
	num = 0;
	printLine("AException");
} catch(except::BException be) {
	num = 1;
	printLine("BException");
} catch(except::CException ce) {
	num = 2;
	printLine("CException");
}
assert(num == 2);
````

## throw
throw は例外をスローする構文です。  
beacon::lang::Exception のサブクラスのみをスロー可能です。


## 実装例
テストコードより抜粋
````
throw new CException();
````