require 'pathname'

def configure_root(path, file_list, dir_list, fp)
	fp.puts "cmake_minimum_required(VERSION 2.8)"
	fp.puts "project(MyProject CXX)"
	fp.puts "set(CMAKE_CXX_FLAGS \"\")"
	fp.puts "set(CMAKE_CXX_FLAGS_DEBUG \"-g -O0 -DDEBUG -MMD -Wall\")"
	fp.puts "set(CMAKE_CXX_FLAGS_RELEASE \"-g -O2 -MMD -w\")"
	#fp.puts set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
	#fp.puts set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -s -DNDEBUG -march=native")
end

def configure_file(path, file_list, dir_list, depth)
	File.open(path + "/CMakeLists.txt", "w") do |file|
		#トップレベルのみ色々追記
		if depth == 0 then
			configure_root(path, file_list, dir_list, file)
		end
		file_list.each do |e|
			objname = File.basename(e, ".c")
			file.puts(sprintf("add_executable(%s %s)", objname, objname + ".c"))
		end
		dir_list.each do |e|
			file.puts(sprintf("add_subdirectory(%s)", e))
		end
	end
end

def configure_recursive(path, depth=0)
	children = Dir.children(path)
	file_list = []
	dir_list = []
	p path
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
			p "?: " + file
		end
	end
	configure_file(path, file_list, dir_list, depth)
end

configure_recursive("../src")