require "open3"
require "fileutils"
require "date"
in_lines = nil
in_path = "classes"
out_path = "/Users/koya/Work/VSCode/beacon/beacon/src/beacon/shared/jni"
buf = []
File.open("rjavap_in.text"){|file| in_lines = file.read.lines }
Dir.chdir("/Users/koya/Work/Netbeans/Jet/jbeacon/build") do
	in_lines.each do |line|
		cmd = sprintf("javap -classpath %s -s -p %s", in_path, line)
		o, e, s = Open3.capture3(cmd)
		p e
		buf << o
	end
end
File.open("rjavap_out.text", "w") do |file|
	buf.each do|e|
		file.puts(e)
		3.times{ file.puts }
	end
end