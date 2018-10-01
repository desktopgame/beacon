require "open3"
require "fileutils"
require "date"

struct_names = []
def short_struct_rename(name)
    name = name.lstrip.rstrip
    if name.start_with?("struct") then
        name = name.slice("struct".length, name.length - "struct".length).lstrip
    end
    if name.include?(" ") then
        words = name.split(" ")
        name = words[0]
    end
    if name.end_with?(";") then
        name = name.slice(0, name.length - 1)
    end
    if name.end_with?("*") then
        name = name.slice(0, name.length - 1)
    end
    name
end
Dir.glob("**/*") do |file|
    next if !file.end_with?(".h") && !file.end_with?(".c")
    File.open(file, "r") do |fp|
        src = fp.read()
        src.lines do |line|
            line = line.lstrip
            next if line.include?("(")
            if(line.start_with?("struct")) then
                struct_names << short_struct_rename(line)
            end
        end
    end
end
struct_names.sort!
struct_names.uniq!
struct_names.each do |e|
    puts ":" + e + ":"
end