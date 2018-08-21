# require
require とは、 ファイルを読み込むための宣言です。  
beacon と同じディレクトリの **script-lib** を基準としてファイルを検索します。
````
require "FileName.bc"
````

**include**や**import**ではなく**require**としているのは、  
そのほうが実際の動作に近いと判断したためです。  
beaconの require は次のような特徴を持ちます。
- include のように、ソースコードを取り込まない
- import のように、完全修飾名に対するショートカットではない
- 使用するファイルは必ず require する必要がある