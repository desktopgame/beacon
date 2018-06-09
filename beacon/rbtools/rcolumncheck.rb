require './rgrep'
p "target: " + File.expand_path('./../src')
file_list = []
line_dict = {}
class LineData
	attr_accessor :line, :length
	def initialize(aline, alength)
		@line = aline
		@length = alength
	end
end
Dir.glob(File.expand_path('./../src/**/*')) do | filename |
	if(!filename.end_with?(".c")) then
		next
	end
	if(filename.end_with?("beacon.tab.c") ||
	   filename.end_with?("lex.yy.c")) then
		next
	end
	File.open(filename) do | file |
		content = file.read()
		content.lines {|line|
			line = line.lstrip().rstrip()
			if(line.length() >= 80) then
				if(!file_list.include?(filename)) then
					file_list << filename
				end
				if(!line_dict.has_key?(filename)) then
					line_dict[filename] = []
				end
				line_list = line_dict[filename]
				line_list << LineData.new(sprintf("<%d>%s", line.length(), line), line.length())
			end
		}
	end
end
file_list.each do | filename |
	list = line_dict[filename]
	list.sort! do |a, b|
		b.length <=> a.length
	end
end
File.open("rcolumn.text", "w") do |file|
	file_list.each do | filename |
		file.puts(filename)
		list = line_dict[filename]
		list.each do | data |
			file.write("    ")
			file.puts(data.line)
		end
	end
end