#srcの中の全ての列挙宣言を取り出して、
#使用箇所を renumgrep_used.text
#未使用の列挙を renumgrep_unused.text へ出力するプログラム
def location(content, offs)
	row = 0
	col = 0
	ptr = 0
	content.chars do |x|
		ptr = ptr + 1
		if x.match(/\n/)
			row = row + 1
			col = 0
			next
		end
		if ptr >= offs then
			break
		end
		col = col + 1
	end
	return [row, col]
end
p "target: " + File.expand_path('./../src')
enum_list = []
Dir.glob(File.expand_path('./../src/**/*')) do | filename |
	if(!filename.end_with?(".h")) then
		next
	end
	File.open(filename) do | file |
		content = file.read()
		matches = content.scan(/enum\s*[a-zA-Z_][a-zA-Z_0-9]*\s*{[^}]*}/)
		matches.each do |e|
			enum_list << e
		end
	end
end
#enum Hpge { ... } の ... をcopy_buffへ
copy_buff = []
enum_list.each do |e|
	matches = e.scan(/.+([^}]*)}/)
	matches.each do |mat|
		copy_buff << mat[0]
	end
end
#copy_buff の全ての要素を , で分割する
enum_list = copy_buff
copy_buff = []
enum_list.each do |e|
	words = e.split(",")
	words.each do |word|
		if word.start_with?("//") || word == "" then
			next
		end
		copy_buff << word.lstrip().rstrip()
	end
end
#識別子として認識できる部分だけを取り出す
enum_list = copy_buff
copy_buff = []
enum_list.each do |e|
	str = ""
	e.chars do |ch|
		if ch.match(/[a-zA-Z_][a-zA-Z_0-9]*/) then
			str << ch
		else
			break
		end
	end
	if str.length > 0 then
		copy_buff << str
	end
end
#最初に調べたディレクトリをもう一度操作
enum_list = copy_buff
copy_buff = []
info_list = []
p "process..."
Dir.glob(File.expand_path('./../src/**/*')) do | filename |
	if(!filename.end_with?(".c")) then
		next
	end
	File.open(filename) do | file |
		content = file.read()
		enum_list.each do |item|
			pos = 0
			while true
				ret = content.index(item, pos)
				if ret == nil
					break
				end
				#fixme: 場合によってはエラー
				loc = location(content, pos)
				lastname = filename.slice(filename.length() - 20, 20)
				info_list << [lastname, item, loc[0], loc[1]]
				pos = (ret + item.length)
			end
		end
	end
end
File.open("renumgrep_used.text", "w") do |file|
	info_list.each do | info |
		file.puts(info.to_s)
	end
end
File.open("renumgrep_unused.text", "w") do |file|
	enum_list.each do |item|
		find = false
		#見つかったか?
		info_list.each do |info|
			if(info[1] == item) then
				find = true
				break
			end
		end
		if !find then
			file.puts(item)
		end
	end
end