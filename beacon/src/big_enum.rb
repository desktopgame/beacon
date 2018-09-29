require "open3"
require "fileutils"
require "date"

def extract_name(name)
    buf = ""
    name.chars.each do |e|
        if e =~ /[a-zA-Z0-9]|_/ then
            buf << e
        else
            break
        end
    end
    buf
end

def bigger(str)
    buf = ""
    str.chars.each do |e|
        if (e == "_") then
            buf << "_"
        elsif e =~ /[a-zA-Z]/ then
            buf << e.upcase
        else
            buf << e
        end
    end
    buf
end

hash = {}
Dir.glob("**/*") do |file|
    next if !file.end_with?(".h")
    File.open(file, "r") do |fp|
        src = fp.read()
        in_enum = 0
        src.lines do |line|
            if(in_enum == 0) then
                line = line.lstrip
                next if !line.start_with?("typedef")
                line = line.slice("typedef".length, line.length - "typedef".length).lstrip
                next if !line.start_with?("enum")
                in_enum += 1
            elsif in_enum > 0
                line = line.lstrip
                next if line.empty?
                next if line.start_with?("//")
                if(line.include?("}")) then
                    in_enum -= 1
                    next
                end
                before = extract_name(line.slice(0, line.length - 1))
                after = bigger(before)
                next if after.empty?
                hash[before] = after
            end
        end
    end
end
Dir.glob("**/*") do |file|
    next if (!file.end_with?(".h") &&
            !file.end_with?(".c") &&
            !file.end_with?(".l") &&
            !file.end_with?(".y"))
    content = nil
    File.open(file, "r") {|fp| content = fp.read()}
    File.open(file, "w") do |fp|
        hash.each_pair do |k,v|
            content = content.gsub(k, v)
        end
        fp.write(content)
    end
end