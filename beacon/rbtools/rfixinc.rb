
symbol = "SIGNAL_"
Dir.glob(File.expand_path('./../src/**/*')) do | filename |
	if(!filename.end_with?(".h")) then
		next
	end
	File.open(filename) do | file |
		content = file.read()
		lineno = 0
		includeLineno = -1
		#全ての行を lines へ格納しつつ
		#ifndefを見つけたら保存
		lines = []
		content.lines do |line|
			lines << line
			if includeLineno == -1 && line.start_with?("#ifndef") then
				includeLineno = lineno
			end
			lineno = lineno + 1
		end
		#ifndefがないなら終了
		if includeLineno == -1 then
			next
		end
		#ifndefが SIGNAL_ から開始しないなら無視
		words = lines[includeLineno].split(" ")
		if !words[1].start_with?(symbol) then
			next
		end
		#SIGNAL_ を BEACON_ へ置き換えて上書き保存
		words[1] = words[1].slice(symbol.length(), words[1].length - symbol.length)
		words[1] = ("BEACON_" + words[1])
		fixedInclude = (words[0] + " " + words[1])
		lines[includeLineno] = fixedInclude
		lines.each do |eline|
			file.puts(eline)
		end
	end
end