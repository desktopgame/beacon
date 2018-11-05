require "open3"
require "fileutils"
require "date"

defines = []

Dir.glob("**/*") do |file|
    next if (!file.end_with?(".h"))
    #最初に全て読み込む
    content = nil
    File.open(file, "r") {|fp| content = fp.read}
    content.lines do |line|
        if line.include?("#") && line.include?("define") then
            defines << line.lstrip.rstrip
        end
    end
end
defines = defines.select{|e| !e.include?("_H")}
defines = defines.select{|e| !e.include?("if")}
defines = defines.select{|e| e.include?("(") && e.include?(")")}
defines.each {|e| puts e}