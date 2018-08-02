# require
require とは、 ファイルを読み込むための宣言です。
````
require "FileName.bc"
````

**include**や**import**ではなく**require**としているのは、  
そのほうが実際の動作に近いと判断したためです。  
beaconの require は次のような特徴を持ちます。
- include のように、ソースコードを取り込まない
- import のように、完全修飾名に対するショートカットではない
- つまり使用するファイルは必ず require する必要がある