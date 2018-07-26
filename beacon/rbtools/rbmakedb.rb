require "open3"
require "fileutils"
require "date"

Dir.chdir("../src") do
	o, e, s = Open3.capture3("make db")
	p o
	p e
	p s
end