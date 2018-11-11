# manual
このプロジェクトで用意しているスクリプト/タスクについてのマニュアル

## CMake
以前は makefile を使用してビルドしていましたが、  
windows環境でも同じ設定でビルドできるようにするため、CMakeに変更しました。  
  

### Mac環境
#### 開発者が行う作業
````
cd beacon/src
cmake -D JNI_INCLUDE_DIR=/Library/Java/JavaVirtualMachines/jdk1.8.0_151.jdk/Contents/Home/include -D JNI_NATIVE_INCLUDE_DIR=/Library/Java/JavaVirtualMachines/jdk1.8.0_151.jdk/Contents/Home/include/darwin .
````

#### 備考
CMakeは makefile を生成しますが、  
makefile はバージョン管理に含まれないようにしています。  
まだ現在のCMakeはプラットフォームごとの処理の分岐などがありませんが、  
将来的にはこれはユーザによって生成される makefile の内容が変わるためです。  

### Windows環境
あとで