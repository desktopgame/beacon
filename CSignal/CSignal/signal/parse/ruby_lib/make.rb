# coding: utf-8
#
#makeconfigから .l .y を自動生成する。
#.l .y では使用出来ない構文を使用できる別ファイルから、
#yacc/bison に適合する形式に変換された .l .y を自動生成する。
#これの後にさらに yacc/bison 自体のビルドを行う。
#
class Make
	def self.__parsecode__(code)
		ret = eval(code)
		if(ret.nil?() || ret.empty?()) then
			return ""
		end
		if(ret.instance_of?(String)) then
			return ret
		else
			return ret.to_s
		end
	end

	#
	#定義ファイルを読み込む関数
	#.l や .y にはコメントを埋められないので、
	#自分で定義した makeconfig という専用ファイルから ; から始まる行だけを取り除き、
	#.l .y を自動生成する。
	#あとファイルを分割したいので、一行区切りでファイル名を記述させる。
	#
	def self.__readstr__(line)
		buffer = ""
		file = File.open(line.strip, "r")

		inCode = false
		buffCode = ""
		lineno = 0
		file.each do |line|
			lineno += 1
			#整形していろいろやる
			#;;から始まる行は無視
			styledText = line.strip
			if(styledText.start_with?(";;")) then
				printf "comment: " + styledText
				printf "\n"
				next
			end
			#既にコードの中なら終了を検出する
			if(inCode) then
				if(styledText == "$$}") then
					inCode = false
					buffer += __parsecode__(buffCode)
				else
					buffCode += line
				end
			#コードの外なら開始を検出する
			else
				#コードを開始
				if(styledText == "$${") then
					inCode = true
					buffCode = ""
				else
					buffer += line
				end
			end
		end
		if(inCode) then
			raise "コードブロック $${ ... $$} が終了していません。[" + (line.strip + ":" + lineno.to_s) + "]"
		end
		buffer += "\n"
		file.close()
		return buffer
	end

	def self.__config_out__(input, output)
		#入力ファイルからソースを自動生成
		buffer = ""
		iFile = File.open(input,"r")
		iFile.each do |line|
			buffer += __readstr__(line)
		end
		iFile.close()
		#出力ファイルへ上書き
		File.open(output, "w") do |oFile| 
			oFile.puts(buffer)
		end
	end

	#
	#CFG_LEXの解析
	#
	def self.lex()
		__config_out__("lex.makeconfig", "signal.l")
	end

	#
	#CFG_YYの解析
	#
	def self.yy()
		__config_out__("yy.makeconfig", "signal.y")
	end
end