from_list = []
to_list = []
File.open("rgenrule_in.text", "r") do |file|
	str = file.read();
	str.lines do |line|
		line = line.lstrip.rstrip
		if line.length == 0 || line.start_with?("//") then
			next
		end
		if(line.include?(",")) then
			line = line.gsub(",", "");
		end
		to_list << (line + ":=" + line + "_T")
	end
end
File.open("rgenrule_out.text", "w") do |file|
	to_list.each do|e|
		file.puts(e)
	end
end