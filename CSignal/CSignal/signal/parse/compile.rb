require 'open3'

o, e, s = Open3.capture3("flex_compile.bat")
o = o.delete("\"");
o.each_line {|line| p line.chomp }

begin
	file = File.open("signal.tab.h","r")
	buffer = ""
	file.each do |text|
		buffer += (text)
	end
	#puts buffer
	file.close

	DQ = "\"";
	includeTargets = [
		"../ast/ast.h", 
		"../ast/constructor_chain_type.h",
		"../ast/assign_operator_type.h",
		"../ast/modifier_type.h",
		"../ast/access_level.h",
		"../util/mem.h"
	]
	prepend = "//insert by compile.rb\n"
	includeTargets.each do |include|
		prepend += ("#include " + DQ + include + DQ + "\n")
	end
	buffer = prepend + buffer;
	File.open("signal.tab.h", "w") do |f| 
		f.puts(buffer)
	end
rescue => e
	p e
end
