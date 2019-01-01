require "open3"
require "fileutils"
require "date"
#makeを実行する
o, e, s = Open3.capture3("make")
p e
p
#テストを実行する
o, e, s = Open3.capture3("make test ARGS='-V'")
o.lines {|line| p "    " + line}
#.gcda .gcno をコピー
File.delete("lcov.info") if File.exists?("lcov.info")
#lcov.info生成
o, e, s = Open3.capture3("lcov -c -d ./CMakeFiles/beacon.dir -o lcov.info")
p e
p
#html生成
o, e, s = Open3.capture3("genhtml -o lcov lcov.info")
p e
page = sprintf("chrome %s", "file://" + File.expand_path("./lcov/index.html"))
p page