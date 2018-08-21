require "open3"
require "fileutils"
require "date"

from_list = []
to_list = []
File.open("rrenameident_in.text", "r") do |file|
	str = file.read();
	str.lines do |line|
		if line.length == 0 || line.start_with?("//") then
			next
		end
		pair = line.split(":=")
		if pair.length != 2 then
			raise "syntax error!"
		end
		from_list << pair[0].lstrip.rstrip
		to_list << pair[1].lstrip.rstrip
	end
end

Dir.glob(File.expand_path('./../src/**/*')) do | filename |
	if(!filename.end_with?(".h") &&
	   !filename.end_with?(".c") &&
	   !filename.end_with?(".text")) then
	   next
	end
	str = nil
	File.open(filename, "r"){|e| str = e.read }
	File.open(filename, "w") do |file|
		from_list.each_with_index do|e,i|
			from = e
			to = to_list[i]
			str = str.gsub(from, to)
		end
		file.write(str)
	end
end