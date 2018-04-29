#getopt_longがあまりにも何度も同じことを書かせる仕様なので自動生成させることにした
require 'fileutils'
LN = "\n"
TAB = "\t"
MODE_OPT = "optional_argument"
MODE_REQ = "required_argument"
MODE_NOA = "no_argument"
IN_FILENAME = "getopt_in.text"
OUT_FILENAME = "getopt_out.text"

source = ""
shortopt = ""
shortnames = []
longnames = []
table = []
variables = {
	"OPT" => MODE_OPT,
	"REQ" => MODE_REQ,
	"NOA" => MODE_NOA
}

if !File.exists?(IN_FILENAME) then
	FileUtils.touch(IN_FILENAME)
	return
end
if !File.exists?(OUT_FILENAME) then
	FileUtils.touch(OUT_FILENAME)
end
#struct option longopts[] = {
source << "struct option longopts[] = {"
source << LN
File.open(IN_FILENAME) do | file |
	content = file.read()
	content.lines do | line |
		#"  :a, b, c" -> ":a, b, c"
		line = line.lstrip.rstrip
		if(!line.start_with?(":")) then
			raise "must be line a start with colon"
		end
		source << TAB
		#":a, b, c" -> "a, b, c"
		pos = line.index(":") + 1
		range = line.slice(pos, line.length - pos)
		words = range.gsub(" ", "").split(",")
		#一応長さを確認する
		if(words.length > 3) then
			raise "argument too many"
		end
		#変数の変換
		mode = words[2]
		if variables.has_key?(mode) then
			mode = variables[mode]
		end
		longname = words[0]
		shortname = words[1]
		shortnames << shortname
		longnames << longname
		#モードに対応してオプションを作成
		shortopt << shortname
		if(mode == MODE_OPT) then
			shortopt << "::"
		elsif (mode == MODE_REQ)
			shortopt << ":"
		end
		#オプションを追加
		source << "{ "
		source << sprintf("\"%s\", %s, NULL, '%s'", words[0], mode, words[1])
		source << " },"
		source << LN
		table.push words
	end
end
source << TAB << "{ 0, 0, 0, 0 }" << LN
source << "};" << LN
source << "extern char *optarg;" << LN
source << "extern int optind, opterr;" << LN
source << "int opt = 0;" << LN
source << "int longindex = 0;" << LN
source << sprintf("while ((opt = getopt_long(argc, argv, \"%s\", longopts, &longindex)) != -1) {", shortopt) << LN
source << TAB << "switch(opt) {" << LN
index = 0
shortnames.each do | e |
	#data = sprintf("\"%s\", \"%s\"", shortnames[index], longnames[index])
	source << TAB << TAB << sprintf("case '%s':", e) << LN
	source << TAB << TAB << TAB << sprintf("printf(\":%s :%s\\n\");", shortnames[index], longnames[index]) << LN
	source << TAB << TAB << TAB << "break;" << LN
	index = index + 1
end
source << TAB << TAB << sprintf("default:") << LN
source << TAB << TAB << TAB << "printf(\"error! :%c :%c\", opt, optopt);" << LN
source << TAB << TAB << TAB << "break;" << LN
source << TAB << "}" << LN
source << "}"
File.open(OUT_FILENAME, "w") do | file |
	file.puts(source)
end