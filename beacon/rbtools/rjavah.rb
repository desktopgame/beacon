require "open3"
require "fileutils"
require "date"
in_lines = nil
in_path = "classes"
out_path = "/Users/koya/Work/VSCode/beacon/beacon/src/beacon/shared/jni"
File.open("rjavah_in.text"){|file| in_lines = file.read.lines }
Dir.chdir("/Users/koya/Work/Netbeans/Jet/jbeacon/build") do
	in_lines.each do |line|
		cmd = sprintf("javah -classpath %s -d  %s %s", in_path, out_path, line)
		o, e, s = Open3.capture3(cmd)
		p o
		p e
		p s
	end
end
Dir.foreach(out_path) do|file|
	next if !file.end_with?(".h")
	cfile = File.basename(file).gsub("\.h", "\.c");
	cfile = File.expand_path(cfile, out_path)
	next if File.exists?(cfile)
	File.open(cfile, "w") do |wfile|
		wfile.puts(sprintf("#include \"%s\"", File.basename(file)))
	end
end