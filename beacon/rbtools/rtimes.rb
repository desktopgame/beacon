File.open("times.text", "w") do|file|
	(-30..150).each do |e|
		file.puts(sprintf("Console.writeLine(%d)", e));
	end
end