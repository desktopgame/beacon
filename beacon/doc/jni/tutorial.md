# jni
jni は **Java Native Interface** のことで、  
CとJavaで相互に機能を呼び出すためのインターフェイスです。  
  
beacon ではこれを使って beacon を java から使えるように、  
また beacon から java を使えるようにする予定です。　  
java側の実装は jbeacon に置いてあります。

## 使い方
- **jbeacon** をダウンロードする
- 使いたいjavaプログラムから jbeacon.jar へパスを通す
- 使いたいjavaプログラムと同じディレクトリに **beacon.so** を置く

## サンプル
````
import jp.koya.jbeacon.Beacon;
import jp.koya.jbeacon.BCEval;

Beacon.init();
BCEval.file("samples/hello.bc");
Beacon.destroy();
````