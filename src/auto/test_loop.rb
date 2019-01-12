require "open3"
require "fileutils"
require "date"
require 'fileutils'
require_relative "cmd"
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
		Cmd.timeout = 10;
		begin
			res = Cmd.run("./beacon --test");
			o = res.stdout;
			e = res.stderr;
			s = res.status;
			if(e.include?("AddressSanitizer") ||
				e.include?("FAIL.")) then
				puts o
				puts e
				puts "----- FAIL -----"
				exit
			end
			o_list << o
			e_list << e
		rescue Cmd::Exception => e
			while line = Cmd.stdout_file_last.gets
				puts "o: " + line
			end
			while line = Cmd.stderr_file_last.gets
				puts "e: " + line
			end
			puts("----FAIL")
			abort()
		end
	end
end
puts "----- SUCCESS -----"