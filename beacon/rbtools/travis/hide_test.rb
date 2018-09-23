require "open3"
require "fileutils"
require "date"

skip_list = ["run/main92"]
Dir.glob("beacon/bin/semantics_test/**/*") do |file|
    next if !file.end_with?(".bc")
    path = File.expand_path(file)
    #指定のファイルがスキップ一覧に入ってるかどうか
    skip = false
    skip_list.each do |e|
        if path.include?(e)
            skip = true
            break
        end
    end
    #入ってるのでスキップ
    if skip then
        File.open(path, "w") do |fp|
            fp.puts(sprintf("printLine(\"skipped test %s\");", file))
        end
    end
end