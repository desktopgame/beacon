require "open3"
require "fileutils"
require "date"
#定数宣言
VERSION = "alpha";

#ビルド
Dir.chdir("..") do
	o, e, s = Open3.capture3("go run tools/build.go")
	p o
	p e
	p s
end
#以前のリリースを削除
Dir.chdir("../package") do
	FileUtils.rm(Dir.glob('*.*'))
end
#各種ファイルを移動
Dir.chdir("..") do
	FileUtils.cp("bin/a.out","package/beacon.out")
	FileUtils.cp("bin/readme.md","package/readme.md")
	FileUtils.cp("bin/version.text","package/version.text")
	FileUtils.cp_r('bin/beacon', 'package')
	FileUtils.cp_r('bin/samples', 'package')
	#マクロを展開
	dict = {
		"$version" => "BETA",
		"$time" => Time.now.to_s
	}
	#読み込みで開いて新規書き込みで書き込む。
	content = nil
	File.open("bin/version.text", "r") do | file |
		content = file.read()
	end
	fixedContent = content
	File.open("package/version.text", "w+") do | file |
		dict.each{|key, value|
			fixedContent = fixedContent.gsub(key, value)
		}
		file.puts(fixedContent)
	end
end