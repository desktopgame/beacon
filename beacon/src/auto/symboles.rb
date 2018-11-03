require "open3"
require "fileutils"
require "date"

lengthOfTypedef = "typedef".length
lengthOfStruct = "struct".length
lengthOfEnum = "enum".length
typedefs = []
structs = []
enums = []
others = []
all = []

def is_old_style(str)
    str.include?("_")
end

def fix_word(str)
    if is_old_style(str) then
        str + "__old"
    else
        str
    end
end

def count_char(str, c)
    i = 0
    str.chars.each do |e|
        if e == c then
            i += 1
        end
    end
    return i
end

Dir.glob("**/*") do |file|
    next if (!file.end_with?(".h"))
    #最初に全て読み込む
    content = nil
    File.open(file, "r") {|fp| content = fp.read}
    content.lines do |line|
        if line.include?("typedef") then
            typedefs << line.lstrip.rstrip
        end
    end
end
typedefs.map! {|e| e.slice(lengthOfTypedef, e.length - lengthOfTypedef).lstrip}
typedefs.each do |e|
    if e.start_with?("struct") then
        structs << e.slice(lengthOfStruct, e.length - lengthOfStruct).lstrip
    elsif e.start_with?("enum") then
        enums << e.slice(lengthOfEnum, e.length - lengthOfEnum).lstrip
    else
        others << e
    end
end
structs.map! do |e|
    if(e.end_with?("{")) then
        e.slice(0, e.length - 1).rstrip
    else
        e
    end
end
enums.map! do |e|
    if(e.end_with?("{")) then
        e.slice(0, e.length - 1).lstrip.rstrip
    else
        e
    end
end
others.map! do |e|
    pos = e.index(" ")
    name = e.slice(pos, e.length - pos - 1)
    if(name.include?(")")) then
        if(count_char(e, "(") >= 2 &&
           count_char(e, ")") >= 2) then
            tstart = e.index("(")
            tend = e.index(")", tstart)
            e = e.slice(tstart, tend-tstart)
            if e.start_with?("(*") then
                e.slice("(*".length, e.length - "(*".length)
            else
                e
            end
        else
            e
        end
    else
        if name.include?(" ") then
            pos = name.rindex(" ")
            name = name.slice(pos, e.length - pos)
        end
        name.lstrip
    end
end
hash = {}
structs.each {|e| all << e}
enums.each {|e| all << e}
others.each {|e| all << e}
all.sort!{|a,b| b.length - a.length}
all.each {|e| hash[e] = "bc" + fix_word(e)}
hash.each do |k, v|
    if k.include?("_") then
        puts ("    " + k)
    else
        puts k
    end
end
