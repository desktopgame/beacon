文字列に関するメモ

# 文字列
beaconはC言語で記述されていますが、  
Cの標準APIの文字列をそのまま使用している部分はあまりありません。  
beaconではそれをラップしたより扱いやすいAPIを用意しています。

# 可変長文字列
## string_buffer
string_bufferの生成
````
string_buffer* buf = string_buffer_new();
string_buffer_appends(buf, "Hello");
````
string_bufferの解放(中の char* も削除)
````
string_buffer_delete(buf);
````
string_bufferの解放(中の char* は残す)
````
char* raw = string_buffer_release(buf);
````