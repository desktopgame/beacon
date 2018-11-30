require "open3"
require "fileutils"
require "date"
require 'fileutils'

puts "clean..."
o, e, s = Open3.capture3("make clean")
e.lines {|i| puts "    " + i}

puts "make..."
o, e, s = Open3.capture3("make")
o.lines {|i| puts "    " + i}
e.lines {|i| puts "    " + i}

puts "test..."
Dir.chdir("../bin") do
    o, e, s = Open3.capture3("./beacon --test")
    e.lines {|i| puts "::" + i}
    o.lines {|i| puts "    " + i}
end