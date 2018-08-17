require "open3"
require "fileutils"
require "date"

#namespace
#hoge::foo
#typename
#Sample
#method_name_start
#call
#method_name_end
#method_param_start
#Int,
#method_param_end

namespace = nil
typename = nil
method_name_list = []
method_param_list = []
method_param_list_C = []
File.open("rnative_template.text", "r") do|file|
	content = file.read
	lines = content.lines.map{|e| e.lstrip.rstrip }
	index = 0
	in_name = false
	in_param = false
	while index < lines.size
		if lines[index] == "namespace" then
			index += 1
			namespace = lines[index]
		elsif lines[index] == "typename" then
			index += 1
			typename = lines[index]
		elsif lines[index] == "method_name_start" then
			if in_name then
				raise "syntax error!"
			end
			in_name = true
		elsif lines[index] == "method_name_end" then
			if !in_name then
				raise "syntax error!"
			end
			in_name = false
		elsif lines[index] == "method_param_start" then
			if in_param then
				raise "syntax error!"
			end
			in_param = true
		elsif lines[index] == "method_param_end" then
			if !in_param then
				raise "syntax error!"
			end
			in_param = false
		else
			if in_name then
				method_name_list << lines[index]
			elsif in_param then
				method_param_list << lines[index].split(",")
			end
		end
		index += 1
	end
end
#check
if method_name_list.size != method_param_list.size then
	raise "syntax error!"
end
#print all
pindex = 0;
while pindex < method_name_list.size
	p sprintf("%s    %s", method_name_list[pindex], method_param_list[pindex])
	pindex += 1
end
#convert to ctype
method_param_list_C = method_param_list.map{|e|
	if e == "Int" then
		"int"
	elsif e == "Char" then
		"char"
	elsif e == "Double" then
		"double"
	elsif e == "String" then
		"const char*"
	end
}


File.open("rnative_h.text", "w") do |file|
	symbol = sprintf("BEACON_LIB_BEACON_%s_BC_%s_H", namespace.gsub("::", "_").upcase(), typename.upcase())
	file.puts(sprintf("#ifndef %s", symbol))
	file.puts(sprintf("#define %s", symbol))
	file.puts("struct type;")
	file.puts
	file.puts(sprintf("void %s_init();", typename.downcase()));
	file.puts
	file.puts(sprintf("struct type* %s_type();", typename.downcase()));
	file.puts
	file.puts("#endif")
end
File.open("rnative_c.text", "w") do |file|
	file.puts(sprintf("#include \"%s\"", "bc_" + typename.downcase + ".h"))
	file.puts
	file.puts "/**"
	file.puts " * created by rbtools/rnative.rb"
	file.puts sprintf(" * time: %s", Date.today.to_s)
	file.puts " */"
	#プロトタイプ宣言
	method_name_list.each do|name|
		file.puts(sprintf("static void bc_%s_native_%s(method* parent, frame* fr, enviroment* env);", typename.downcase, name));
	end
	file.puts
	file.puts(sprintf("void %s_init() {", typename.downcase()));
	file.puts("}")
	file.puts
	file.puts(sprintf("type* %s_type() {", typename.downcase()));
	file.puts("\treturn NULL;")
	file.puts("}")
	file.puts
	file.puts "//private"
	#プロトタイプの実装
	method_name_list.each do|name|
		file.puts(sprintf("static void bc_%s_native_%s(method* parent, frame* fr, enviroment* env) {", typename.downcase, name));
		file.puts "}"
		file.puts
	end
end
File.open("rnative_bc.text", "w") do |file|

	file.puts "/**"
	file.puts " * created by rbtools/rnative.rb"
	file.puts sprintf(" * time: %s", Date.today.to_s)
	file.puts " */"
	file.puts(sprintf("namespace %s {", namespace))
	file.puts(sprintf("\tclass %s {", typename))
	file.puts("\t\tpublic:")
	method_name_list.each_with_index do|name,i|
		file.print(sprintf("\t\tdef static %s(", name))
		params = method_param_list[i]
		args = []
		params.each_with_index do|param, j|
			break if params.size == 1
			args << sprintf("param%d", j)
			file.print(sprintf("%s param%d", param, j))
			if j == params.size-2 then
				break
			else
				file.print(", ")
			end
		end
		file.puts sprintf(") -> %s {", params[params.size-1])
		if params[params.size-1] == "Void" then
			file.print(sprintf("\t\t\t%s(", ("native" + name.capitalize)))
			args.each_with_index do|e,j|
				file.print e
				if j == (args.size - 1) then
					break
				else
					file.print(", ")
				end
			end
			file.puts(");")
		else
			file.print("\t\t\treturn ");
			file.print(sprintf("%s(", ("native" + name.capitalize)))
			args.each_with_index do|e,j|
				file.print e
				if j == (args.size - 1) then
					break
				else
					file.print(", ")
				end
			end
			file.puts(");")
		end
		file.puts("\t\t}");
		file.puts
	end
	#ネイティブメソッド実装
	file.puts("\t\tprivate:")
	method_name_list.each_with_index do|name, i|
		file.print(sprintf("\t\tdef native static native%s(", name.capitalize))
		params = method_param_list[i]
		params.each_with_index do|param, j|
			break if params.size == 1
			file.print(sprintf("%s param%d", param, j))
			if j == params.size - 2 then
				break
			else
				file.print(", ")
			end
		end
		file.puts sprintf(") -> %s;", params[params.size-1])
		file.puts
	end
	file.puts("\t}")
	file.puts("}")
end