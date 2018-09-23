require "open3"
require "fileutils"
require "date"
if(ARGV.length == 0) then
    raise "few arguments"
end
workspace = ARGV[0]
src = workspace + "/beacon/src"
Dir.chdir(src) do
	o, e, s = Open3.capture3("make db")
	p o
	p e
	p s
	o, e, s = Open3.capture3(workspace + "/beacon/bin/a.out --test")
	p o
	p e
	p s
    o, e, s = Open3.capture3("gcovr --xml --output=gcovr.xml ../obj")
	p o
	p e
	p s
end