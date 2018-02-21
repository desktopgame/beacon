# coding: utf-8
require 'open3'

class Build
	DQ = "\""
	
	def self.__compile_impl__()
		#全てのテキストを buffer へ
		file = File.open("signal.tab.h","r")
		buffer = ""
		file.each do |line|
			buffer += (line)
		end
		file.close()
		#テキストの前にインクルードをつける
		includeTargets = [
			"../ast/ast.h", 
			"../ast/ast_new_factor.h", 
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
		#インクルードを付け加えたテキストで上書き
		File.open("signal.tab.h", "w") do |file| 
			file.puts(buffer)
		end
	end

	def self.compile()
		o, e, s = Open3.capture3("flex_compile.bat")
		o = o.delete("\"");
		o.each_line {|line|
			line = line.chomp
			if line.length() < 1 then
				next
			end
			printf "[ " + line + " ]"
			printf "\n"
		}

		begin
			Build.__compile_impl__()
		rescue => e
			p e
		end
	end
end