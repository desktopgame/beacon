require "open3"
require "fileutils"
require "date"
require 'fileutils'
require_relative "cmd"
require 'rbconfig'

def os
	@os ||= (
	  host_os = RbConfig::CONFIG['host_os']
	  case host_os
	  when /mswin|msys|mingw|cygwin|bccwin|wince|emc/
		:windows
	  when /darwin|mac os/
		:macosx
	  when /linux/
		:linux
	  when /solaris|bsd/
		:unix
	  else
		:unknown
	  end
	)
  end
  
  def say(str)
	  if(os == :macosx) then
		  system("say " + str)
	  end
  end

def copy_sub(from_dir, to_dir, e)
	e = File.basename(e)
	ret = []
	from_p = File.expand_path(from_dir + e)
	to_p = File.expand_path(to_dir + e)
	if(File.exist?(to_p)) then
		File.delete(to_p)
	end
	puts "    " + e
	FileUtils.cp(from_p, to_p)
	ret << to_p
	ret
end

def copy_to(from_dir, to_dir)
	ret = []
	if(!Dir.exist?(from_dir)) then
		raise from_dir + " is not found"
	end
	puts to_dir
	if(!Dir.exist?(to_dir)) then
		FileUtils.mkdir_p(to_dir)
	end
	Dir.glob(from_dir + "/*.c") do |e|
		ret.concat(copy_sub(from_dir, to_dir, e))
	end
	Dir.glob(from_dir + "/*.l") do |e|
		ret.concat(copy_sub(from_dir, to_dir, e))
	end
	Dir.glob(from_dir + "/*.y") do |e|
		ret.concat(copy_sub(from_dir, to_dir, e))
	end
	Dir.entries(from_dir).select {|entry| File.directory? File.join(from_dir,entry) and !(entry =='.' || entry == '..') }.each do |dir|
		ret.concat(copy_to(from_dir + dir + "/", to_dir + dir + "/"))
	end
	ret
end
#lcovを削除しておく
if(Dir.exist?("lcov/beacon")) then
	FileUtils.rm_r("lcov/beacon")
end
if(Dir.exist?("CMakeFiles")) then
	FileUtils.rm_r("CMakeFiles")
end
if(File.exist?("CMakeCache.txt")) then
	File.delete("CMakeCache.txt")
end
if(File.exist?("lcov/index.html")) then
	File.delete("lcov/index.html")
end
#makeを実行する
o, e, s = Open3.capture3("cmake -D CMAKE_BUILD_TYPE=Debug -D JNI_INCLUDE_DIR=/Library/Java/JavaVirtualMachines/jdk1.8.0_151.jdk/Contents/Home/include -D JNI_NATIVE_INCLUDE_DIR=/Library/Java/JavaVirtualMachines/jdk1.8.0_151.jdk/Contents/Home/include/darwin .")
p e
p
o, e, s = Open3.capture3("make")
p e
p
#テストを実行する
o, e, s = Open3.capture3("make test ARGS='-V'")
o.lines {|line| p "    " + line}
e.lines {|line| p "    " + line}
File.delete("lcov.info") if File.exists?("lcov.info")
copy_list = copy_to("beacon/", "./CMakeFiles/beacon.dir/beacon/")
#lcov.info生成
o, e, s = Open3.capture3("lcov -c -d ./CMakeFiles/beacon.dir -o lcov.info")
p e
p
#html生成
o, e, s = Open3.capture3("genhtml -o lcov lcov.info")
p e
page = sprintf("chrome %s", "file://" + File.expand_path("./lcov/index.html"))
p page
#コピーしたファイル全削除
copy_list.each do |e|
	File.delete(e)
end
say("カバレッジ生成完了");