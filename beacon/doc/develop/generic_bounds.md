ジェネリックの境界に関するメモ

# ジェネリックの境界
ある型 T が与えられたクラス **General**と  
それをクラス **Super** で実体化したインスタンス **A**  
それをクラス **Sub** で実体化したインスタンス **B** について考えます。

General.beacon
--
    class General<T> { ... }

Super.beacon
--
    class Super { ... }

Sub.beacon
--
    class Super : Sub { ... }

main.beacon
--
    var A = new General<Super>();
    var B = new General<Sub>();

SubはSuperを継承しています。  
型変数による継承関係は代入にもそのまま適用できるのでしょうか。

# 入力
General.beacon
--
    class General<T> {
        void input(T e)
    }

Generalにこのようなメソッドがあったとします。  
これが Super/Sub で実体化されます。  
下記はイメージです。

General\<Super>
--
    class General<Super> {
        void input(Super e)
    }

General\<Sub>
--
    class General<Sub> {
        void input(Sub e)
    }

ここで、**A**に対して**B**を代入するケースを考えます。  

main.beacon
--
    var A = new General<Super>();
    var B = new General<Sub>();
    A = B;

A#input は Super 型で受け取ることが出来ますが、  
B#input は Sub 型で受け取ることしか出来ません。  
なのでこの代入は成立しません。  

# 出力
General.beacon
--
    class General<T> {
        T output()
    }

Generalにこのようなメソッドがあったとします。  
これが Super/Sub で実体化されます。  
下記はイメージです。

General\<Super>
--
    class General<Super> {
        Super output()
    }

General\<Sub>
--
    class General<Sub> {
        Sub output()
    }

ここで、**B**に対して**A**を代入するケースを考えます。  

main.beacon
--
    var A = new General<Super>();
    var B = new General<Sub>();
    B = A;

B#output の戻り値は Sub ですが、  
A#output の戻り値は Super なので、  
この場合もやはり要件を満たしていません。

# 代入互換性
入力の場合は **A** = **B** が成立せず、   
出力の場合は **B** = **A** が成立しないということを説明しました。  
  
これ実は逆のケースだとちゃんと成立します。
## 入力(B = A)
B#input は Sub で受け取ることが出来ます。  
よって、 B#input には それを継承した Super を渡すことが出来ます。

## 出力(A = B)
A#output は Super で返すことが出来ます。  
よって、 B#output で それを継承した Sub を返すことが出来ます。

# 境界の導入
Java には 型の境界を指定する方法があり、これを使うと  
入力で A = B  
出力で B = A  
をそれぞれ成立させることが出来ます。

## 入力の境界(A = B)
main.java
--
    List<? extends Super> A = new ArrayList<>();
	List<Sub> B = new ArrayList<Sub>();
	A = B;

## 出力の境界(B = A)
main.java
--
    List<Super> A = new ArrayList<>();
	List<? super Sub> B = new ArrayList<>();
	B = A;

# beaconでは
ここでは Java の方法を書きましたが、  
これは呼び出す側が境界を指定する必要があります。  
      
C#では型変数に対して in/out を指定することで  
これとだいたい似たようなことができる？ぽいです。

おそらくC#と同じ方法をとると思います。
