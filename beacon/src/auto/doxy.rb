require "open3"
require "fileutils"
require "date"
require 'fileutils'

if Dir.exist?("../doc/doxy") then
    FileUtils.rm_r("../doc/doxy")
end

o, e, s = Open3.capture3("doxygen")
p o
p e
p s