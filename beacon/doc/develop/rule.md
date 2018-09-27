# 命名規則
beaconのプログラムにおける命名規則

## 以前のもの
- 構造体、関数などの名前は小文字で統一して、単語の区切りは _ を使用する
- それ以外は特に統一されていない

## なぜ命名規則が必要になったか
- C++との名前の衝突を避けるため、現状では namespace_ class_ を構造体名として使用している
- これをもう少しマシにしたい(Namespace, Classとか)
- 全体で統一されていないと気持ち悪いので、他のもそれに合わせて命名を修正する

## 新しいもの
### 構造体名について
- 単語の頭は大文字にする
- 最初の一文字も大文字にする
- 略語の場合はどちらも大文字
    - Io ではなく IO とする
    - Xml ではなく XML とする
- Win32APIを参考にする
    - ただし明らかに理解できない/不自然な略語等は使用しない

例えば
````
string_builder -> StringBuilder
namespace_ -> Namespace
class_ -> Class
````

### 関数名について
- ある構造体をレシーバのように扱う場合、その構造体自体の名前か略語を含める
    - string_builder_append -> AppendBuffer
- オブジェクト指向的に扱われる関数は注意が必要
    - ルートの関数は簡潔に
        - il_factor_eval -> EvalILFactor
    - ルートから呼び出される子関数は冗長に
        - il_factor_int_eval -> EvalILFactorInt
- Win32APIを見る限り、動詞が先に来ることが多い
    - `Get`MapMode
    - `Get`ViewportExtEx
    - `Map`WindowPoints
        - Mappingの省略?
    - `Scale`ViewportExtEx
    - `Create`RectRgn
        - 他にも生成系関数はこの`Create`XXX の形式をとる
    - `Delete`DC
        - 他にも破棄系関数はこの`Delete`XXX の形式をとる
        - DestroyXXX っていうのもある
    - `Find`FirstFile
    - `Find`NextFile

### 方針
機械的に一気に変換するのは難しそうなので、  
手作業でじわじわと進めていきます。

### 参考になるかもしれないページ
#### [Win32 API 関数リスト](http://chokuto.ifdef.jp/urawaza/api/)
- C言語で記述されている
- Rgn, Msg, DC など略称を参考にしたい
#### [Win32API一覧](http://codepanic.itigo.jp/win32.html)
- 同じく