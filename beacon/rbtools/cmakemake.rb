require 'pathname'
require 'find'
@@words = []

def word_intern(word)
	if @@words.include?(word)
		nw = word + "_copy"
		@@words << nw
		return nw
	else
		@@words << word
		return word
	end
end

def path_is_source_dir(path)
	children = Dir.children(path)
	return (children.all?{|item| 
		item.end_with?(".c") ||
		item.end_with?(".h") ||
		item.end_with?(".l") ||
		item.end_with?(".y") ||
		item.end_with?(".c")
	})
end

def configure_root(path, file_list, dir_list, fp)
	#fp.puts "cmake_minimum_required(VERSION 3.5)"
	#fp.puts "project(beacon C)"
	Find.find("../src") do |a|
		if File.file?(a) || !a.end_with?("bin") then
			next
		end
		fullname = File.expand_path(a, path)
		if !fullname.include?("HTML") then
			p "conf "+ fullname
		end
	end
	fp.puts "include_directories( /usr/include /opt/local/include )"
	fp.puts "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)"
	fp.puts "set(CMAKE_C_COMPILER \"/usr/bin/clang\" CACHE string \"clang compiler\" FORCE)"
	fp.puts "link_directories( /usr/local/lib /opt/local/lib )"
	#fp.puts "set(CMAKE_CXX_FLAGS \"\")"
	#fp.puts "set(CMAKE_CXX_FLAGS_DEBUG \"-g -O0 -DDEBUG -MMD -Wall\")"
	#fp.puts "set(CMAKE_CXX_FLAGS_RELEASE \"-g -O2 -MMD -w\")"
	#fp.puts set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
	#fp.puts set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -s -DNDEBUG -march=native")
end

def configure_file(path, file_list, dir_list, depth)
	File.open(path + "/CMakeLists.txt", "w") do |file|
		basename = word_intern(File.basename(path))
		#トップレベルのみ色々追記
		if depth == 0 then
			configure_root(path, file_list, dir_list, file)
		end
		file.puts "cmake_minimum_required(VERSION 3.5)"
		file.puts sprintf("project(%s C)", basename)
		if !file_list.empty?() then
			file.puts(sprintf("add_executable(\n    %s\n", basename))
			file_list.each do |e|
				file.puts(sprintf("    %s\n", e))
			end
			file.puts(")")
		end
		dir_list.each do |e|
			if path_is_source_dir(e) then
				file.puts(sprintf("add_subdirectory(%s)", File.basename(e)))
			end
		end
	end
end

def configure_recursive(path, depth=0)
	children = Dir.children(path)
	file_list = []
	dir_list = []
	p path
	if !path_is_source_dir(path) && depth > 0 then
		return
	end
	children.each do |file|
		file = File::expand_path(file, path)
		#存在しない
		if !File.exists?(file)
			p "n: " + file;
			next
		end
		#ファイルなら書き込む
		if File.file?(file) && file.end_with?(".c") then
			file_list << file
		#ディレクトリならさらに再帰
		elsif File.directory?(file) then
			dir_list << file
			configure_recursive(file, depth + 1)
		#?
		else
			#p "?: " + file
		end
	end
	configure_file(path, file_list, dir_list, depth)
end

configure_recursive("../src")