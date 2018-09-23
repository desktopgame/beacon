require "open3"
require "fileutils"
require "date"

errors = []
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
    errors << e if e.length > 0
end
Dir.glob("./**/*") do |file|
    next if !file.end_with?(".gcov")
    from = File.expand_path(file)
    to = File.expand_path("../gcov/" + file)
    File.delete(to) if File.exist?(to)
    p from
    p to
    File.rename(from, to)
end
errors.each do |e|
    p e
end