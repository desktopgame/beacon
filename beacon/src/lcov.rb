require "open3"
require "fileutils"
require "date"
#makeを実行する
o, e, s = Open3.capture3("make db")
p e
p
#テストを実行する
Dir.chdir("../bin") do
    o, e, s = Open3.capture3("./a.out --test")
    o.lines {|line| p "    " + line}
end
#.gcda .gcno をコピー
FileUtils.cp_r("../obj/beacon", ".")
File.delete("lcov.info") if File.exists?("lcov.info")
#lcov.info生成
o, e, s = Open3.capture3("lcov -c -d . -o lcov.info")
p e
p
#html生成
o, e, s = Open3.capture3("genhtml -o lcov lcov.info")
p e
#掃除
Dir.glob("**/*") do |file|
    next if (!file.end_with?(".gcda") &&
             !file.end_with?(".gcno") &&
             !file.end_with?(".o") &&
             !file.end_with?(".d"))
    File.delete(file)
end
page = sprintf("chrome %s", "file://" + File.expand_path("./lcov/index.html"))
p page
system page