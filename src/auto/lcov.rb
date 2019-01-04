require "open3"
require "fileutils"
require "date"

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
if(File.exist?("lcov/index.html")) then
	File.delete("lcov/index.html")
end
#gcda,gcnoを削除しておく
Dir.glob("**/*.gcda") do |e|
	File.delete(e)
end
Dir.glob("**/*.gcno") do |e|
	File.delete(e)
end
#cleanを実行する
o, e, s = Open3.capture3("make clean")
p e
p
#makeを実行する
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