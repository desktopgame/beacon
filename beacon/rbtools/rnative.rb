require "open3"
require "fileutils"
require "date"

if ARGV.length < 2 then
	raise "few arguments"
end
namespace = ARGV[0]
typename = ARGV[1]
method_name_list = ARGV[2].split(",")

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