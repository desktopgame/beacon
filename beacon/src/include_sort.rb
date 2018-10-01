require "open3"
require "fileutils"
require "date"

file_src = {}
Dir.glob("**/*") do |file|
    next if !file.end_with?(".h") && !file.end_with?(".c")
    content = nil
    begin_include = false
    end_include = false
    include_list = []
    include_start_line = -1
    include_end_line = -1
    src = nil
    File.open(file, "r") do |fp|
        src = fp.read()
        #includeを集計する
        src.lines.each_with_index do |line, i|
            next if line.start_with?("//")
            if !begin_include then
                line = line.lstrip
                if line.include?("#include") then
                    begin_include = true
                    include_list << line
                    include_start_line = i
                end
            else
                line = line.lstrip
                if line.include?("#include") then
                    include_list << line
                else
                    if !end_include then
                        include_end_line = i
                    end
                    end_include = true
                end
            end
        end
    end
    next if include_start_line == -1 || include_end_line == -1
    #includeをソートする
    include_list.map! do |e|
        e.slice("#include ".length, e.length - "#include ".length)
    end
    include_system = include_list.select {|e| e.lstrip.start_with?("<")}
    include_user = include_list.select {|e| e.lstrip.start_with?("\"")}
    include_system.map! {|e| e.slice(1, e.length - 3)}
                  .sort!
                  .map! {|e| "#include <" + e + ">"}
    include_user.map! {|e| e.slice(1, e.length - 3)}
                .sort!
                .map! {|e| "#include \"" + e + "\""}
    #新しいソースを生成
    lines = src.lines
    lines.slice!(include_start_line, include_end_line-include_start_line)
    #ソート後のincludeを挿入
    include_system.each {|e| lines.insert(include_start_line, e)}
    include_user.each {|e| lines.insert(include_start_line + include_system.length, e)}
    file_src[file] = lines
end
file_src.each_pair do |k, v|
    File.open(k, "w") do |fp|
        v.each {|line| fp.puts(line)}
    end
end