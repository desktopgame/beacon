require "open3"
require "fileutils"
require "date"
require 'fileutils'

def count_lines(globFiles)lines = 0
	Dir.glob(globFiles) do |e|
		buf = File.open(e, "r") {|fp| fp.read }
		lines += buf.lines.length
	end
	lines
end

hlines = count_lines("**/*.h")
clines = count_lines("**/*.c")
puts "all .h line:" + hlines.to_s
puts "all .c line:" + clines.to_s
puts "all program line:" + (hlines + clines).to_s