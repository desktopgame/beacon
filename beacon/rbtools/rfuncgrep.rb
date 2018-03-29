#srcの中の全ての関数宣言を取り出して、
#未使用の関数をを rfuncgrep_unused.text へ出力するプログラム
require './rgrep'
p "target: " + File.expand_path('./../src')
func_list = []
Dir.glob(File.expand_path('./../src/**/*')) do | filename |
	if(!filename.end_with?(".h")) then
		next
	end
	File.open(filename) do | file |
		content = file.read()
		matches = content.scan(/[a-zA-Z_][a-zA-Z_0-9*]*\s+[a-zA-Z_][a-zA-Z_0-9]*\(.+\)/)
		matches.each do |e|
			fixed = filename.slice(0, filename.length - 5)
			func_list << [fixed, e]
		end
	end
end
#関数名だけ取り出す
copy_buff = []
func_list.each do |e|
	fn = e[0]
	str = e[1]
	matches = str.scan(/[a-zA-Z_][a-zA-Z_0-9*]*\s+([a-zA-Z_][a-zA-Z_0-9]*)\(.+\)/)
	matches.each do |gr|
		if gr[0] == "void" then
			next
		end
		copy_buff << [fn, gr[0]]
	end
end
func_list = copy_buff
copy_buff = []
info_list = []
Dir.glob(File.expand_path('./../src/**/*')) do | filename |
	if(!filename.end_with?(".c")) then
		next
	end
	File.open(filename) do | file |
		content = file.read()
		func_list.each do |item|
			fn = item[0]
			str = item[1]
			if filename.start_with?(fn) then
				next
			end
			pos = 0
			while true
				ret = content.index(str, pos)
				if ret == nil
					break
				end
				#fixme: 場合によってはエラー
				loc = RGrep::location(content, pos)
				lastname = filename.slice(filename.length() - 20, 20)
				info_list << [lastname, str, loc[0], loc[1]]
				pos = (ret + str.length)
			end
		end
	end
end

File.open("rfuncgrep_used.text", "w") do |file|
	info_list.each do | info |
		file.puts(info.to_s)
	end
end
File.open("rfuncgrep_unused.text", "w") do |file|
	func_list.each do |item|
		fn = item[0]
		str = item[1]
		find = false
		#見つかったか?
		info_list.each do |info|
			if(info[1] == str) then
				find = true
				break
			end
		end
		if !find then
			file.puts(str)
		end
	end
end