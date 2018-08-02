require "open3"
require "fileutils"
require "date"
cpp_check_exe = "/Users/koya/Work/cppcheck/cppcheck"
#ビルド
Dir.chdir("../src") do
	o, e, s = Open3.capture3(cpp_check_exe + " --enable=all beacon");
	p o
	p e
	p s
	File.open("cppcheck_out.text", "w") do | file |
		file.puts(o);
	end
	File.open("cppcheck_err.text", "w") do | file |
		file.puts(e);
	end
end