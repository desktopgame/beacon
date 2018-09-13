result = {}
Dir.glob(File.expand_path('./../src/**/*')) do | filename |
	if(!filename.end_with?(".h")) then
		next
    end
    File.open(filename, "r") do | file |
        content = file.read()
        result[filename] = []
        content.lines do |line|
            next if !line.include?("#define")
            next if line.include?("BEACON")
            #p line
            result[filename] << line
        end
        if result[filename].empty? then
            result.delete(filename)
        end
    end
end
File.open("rfinddefine.text", "w") do | file |
    result.each_pair do | k, v |
        file.puts(k)
        v.each do | e |
            file.puts(sprintf("    %s", e))
        end
    end
end