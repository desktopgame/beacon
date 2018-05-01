LN = "\n"
hlines = 0
clines = 0
datum = []
class LineCount
	attr_accessor :text, :amount
	def initialize(text, amount)
		@text = text
		@amount = amount
	end
end

Dir.glob(File.expand_path('./../src/**/*')) do | filename |
	if(!filename.end_with?(".h") && !filename.end_with?(".c")) then
		next
	end
	temp = 0
	File.open(filename, "r") do | hfile |
		content = hfile.read();
		temp = content.lines().length
	end
	text = sprintf(filename + "<%d>", temp)
	datum << LineCount.new(text, temp)
	if(filename.end_with?(".h")) then
		hlines += temp
	elsif (filename.end_with?(".c")) then
		clines += temp
	end
end
datum = datum.sort do | a, b|
	a.amount <=> b.amount
end
datum = datum.reverse!
File.open("linecount.text", "w") do | file |
	file.puts sprintf(".h: %d", hlines)
	file.puts  sprintf(".c: %d", clines)
	datum.each do | data |
		file.puts(data.text)
	end
end