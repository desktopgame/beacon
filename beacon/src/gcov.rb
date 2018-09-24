require "open3"
require "fileutils"
require "date"

def isdigit(a)
       (a == '0' ||
       a == '1' ||
       a == '2' ||
       a == '3' ||
       a == '4' ||
       a == '5' ||
       a == '6' ||
       a == '7' ||
       a == '8' ||
       a == '9')
end

def fix_num(str)
    return str if str == nil
    #p str
    last_char = str[str.length - 1]
    if(isdigit(last_char))
        return str
    end
    fix_num(str.slice(0, str.length - 1))
end

p "start gcov"

output_list = []
error_list = []
current = File.expand_path("./")
Dir.glob("./**/*") do |file|
    next if !file.end_with?(".c")
    path = File.expand_path(file)
    dir = File.dirname(path)
    component = dir.slice(current.length, dir.length - current.length)

    gcda = path.gsub(".c", ".gcda")
    cmd = sprintf("gcov %s -o ../obj" + component, gcda)
    #.c.gcdaの生成
    o, e, s = Open3.capture3(cmd)
    output_list << o
    error_list << e if e.length > 0
end
Dir.glob("./**/*") do |file|
    next if !file.end_with?(".gcov")
    from = File.expand_path(file)
    to = File.expand_path("../gcov/" + file)
    File.delete(to) if File.exist?(to)
    File.rename(from, to)
    p to
end
# そのまま出力をファイルへ
raw_output = "../gcov/00raw_data.text"
File.delete(raw_output) if File.exist?(raw_output)
File.open(raw_output, "w") do |fp|
    output_list.each do |e|
        fp.puts(e)
    end
end
# 整形済みの出力をファイルへ
score_output = "../gcov/00score_data.text"
File.delete(score_output) if File.exist?(score_output)
File.open(score_output, "w") do |fp|
    output_list.each do |e|
        lines = e.lines
        next if lines[0] == nil
        filename = lines[0].slice(5, lines[0].length - 5)
        score = lines[1]
        fp.puts(filename)
        fp.puts(fix_num(score.slice(15, 10)))
    end
end
p "finished gcov"