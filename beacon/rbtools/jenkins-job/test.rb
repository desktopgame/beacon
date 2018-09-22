require "open3"
require "fileutils"
require "date"

if(ARGV.length == 0) then
    raise "few arguments"
end
src = ARGV[0] + "/beacon/bin"
Dir.chdir(src) do
    o, e, s = Open3.capture3("./a.out --test")
	p o
	p e
	p s
end