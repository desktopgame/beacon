require "open3"
require "fileutils"
require "date"

if(ARGV.length < 2) then
    raise "few arguments"
end
key = ARGV[0]
value = ARGV[1]

content = nil
File.open("beacon/src/makefile", "r") {|fp| content = fp.read()}

File.open("beacon/src/makefile", "w") do |fp|
    at = -1
    lines = content.lines
    lines.each_with_index do |e, i|
        if e.include?(key) then
            at = i
            break
        end
    end
    if at == -1 then
        fp.puts(content)
        raise sprintf("%s is not found", key)
    end
    lines[at] = sprintf("%s  = %s", key, value);
    lines.each do |e|
        fp.puts(e)
    end
end

File.open("beacon/src/makefile", "r") {|fp| fp.read().lines{|line| p "    " + line}}