require "open3"
require "fileutils"
require "date"
#todo, TODO, fixme, FIXME を調べ上げて報告するスクリプト
#引数として jenkins のワークスペースが必要です。

class Token
	attr_accessor :filename, :text, :line, :column

	def initialize(filename, text, line, column)
		@filename = filename
		@text = text
		@line = line
		@column = column
	end

	def to_s()
		return sprintf("%s@%s<%d:%d>", text, filename, line, column)
	end
end

#@param source
#@param pos
#@return [line, column]
def find_range(source, pos)
	lineno = 0
	column = 0
	offset = 0
	source.lines do |line|
		lineno += 1
		column = 0
		at = 0
		over = false
		while(at < line.length)
			column += 1
			at += 1
			if offset + at >= pos
				over = true
				break
			end
		end
		offset += line.length
		break if over
	end
	[lineno, column]
end

#@param source
#@param word
def collect_ignore_case(source, word)
	collect(source, word.downcase) + collect(source, word.upcase)
end

#@param source
#@param word
def collect(source, word)
	pos = 0
	ret = []
	while (pos = source.index(word, pos)) != nil
		start = pos
		pos = start + word.length
		values = find_range(source, start)
		line = values[0]
		column = values[1]
		ret << Token.new(nil, word, line, column)
	end
	ret
end

if(ARGV.length == 0) then
    raise "few arguments"
end

all_remind_list = []
Dir.glob(ARGV[0] + "/beacon/src/**/*") do |file|
	next if(!file.end_with?(".h") && !file.end_with?(".c"))
	File.open(file, "r") do |fp|
		content = fp.read()
		remind_list = collect_ignore_case(content, "todo") +
					  collect_ignore_case(content, "fixme");
		remind_list = remind_list.map{|e| Token.new(File.basename(file), e.text, e.line, e.column)}
		all_remind_list = all_remind_list + remind_list
	end
end
unless all_remind_list.empty?
	all_remind_list.each{|e| puts "    " + e.to_s + "\n" }
	raise "check!"
end