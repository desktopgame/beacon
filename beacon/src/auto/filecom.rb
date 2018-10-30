require "open3"
require "fileutils"
require "date"

Dir.glob("**/*") do |file|
    next if (!file.end_with?(".h"))
    #最初に全て読み込む
    content = nil
    File.open(file, "r") {|fp| content = fp.read}
    
end