def indent_count(line)
    indent = 0
    space = 0
    line.chars do | c |
        if(c == " ") then
            space += 1
            if(space == 4) then
                indent += 1
                space = 0
            end
        elsif (c == "\t") then
            space = 0
            indent += 1
        else
            break
        end
    end
    indent
end

result = []
Dir.glob(File.expand_path('./../src/**/*')) do | filename |
    if(!filename.end_with?(".c") || !File.file?(filename)) then
        next
    end
    #.cファイルを読み込む
    lineIndex = 0
    File.open(filename, "r") do | file |
        content = file.read()
        content.lines do | line |
            indent = indent_count(line)
            if(indent >= 3) then
                result << [filename, lineIndex, indent]
            end
            lineIndex += 1
        end
    end
end
result.sort! do |a, b|
    b[2] <=> a[2]
end
File.open("rindent.text", "w") do |file|
	result.each do | data |
		file.puts(sprintf("%d %s<%d>", data[2], data[0], data[1]))
	end
end