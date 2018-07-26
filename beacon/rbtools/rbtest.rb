require "open3"
require "fileutils"
require "date"

Dir.chdir("../bin") do
	threads = []
	10.times do
		o, e, s = Open3.capture3("./a.out --test")
		if !s.success? then
			p o
			p e
			p s
			break
		else
			p s
		end
	end
end