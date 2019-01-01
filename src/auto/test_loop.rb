require "open3"
require "fileutils"
require "date"
require 'fileutils'
loops = 10
if(ARGV.length > 0) then
	loops = ARGV[0].to_i
end
puts ("loops..." + loops.to_s)
puts "make..."
o, e, s = Open3.capture3("make")
o.lines {|i| puts "    " + i}
e.lines {|i| puts "    " + i}

puts "test..."
o_list = []
e_list = []
loops.times do |i|
	puts ("run test..." + i.to_s)
	Dir.chdir("../bin") do
		o, e, s = Open3.capture3("./beacon --test")
		if(e.include?("AddressSanitizer") ||
			e.include?("FAIL.")) then
			puts o
			puts e
			puts "----- FAIL -----"
			exit
		end
		o_list << o
		e_list << e
	end
end
puts "----- SUCCESS -----"