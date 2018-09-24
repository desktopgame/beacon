require "open3"
require "fileutils"
require "date"
FileUtils.cp_r("../obj/beacon", ".")
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