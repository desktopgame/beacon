require "open3"
require "fileutils"
require "date"
#検索語句と置換語の単語を入力する
printf("find word: ")
@find = STDIN.gets.lstrip.rstrip
printf("replace word: ")
@replace = STDIN.gets.lstrip.rstrip

class Token
    attr_accessor :offset, :length, :text, :line

    def initialize(offset, length, text)
        @offset = offset
        @length = length
        @text = text
    end
end

def forward_line_pos(content, pos)
    ret = pos
    while(content[ret] != "\n")
        ret += 1
        if(ret >= content.length) then
            return content.length
        end
    end
    ret - 1
end

def backward_line_pos(content, pos)
    ret = pos
    while(content[ret] != "\n")
        ret -= 1
        if(ret < 0) then
            return 0
        end
    end
    ret + 1
end

def tokenize_text(content)
    ret = []
    operands = " \t\n{}(),.;+-*/%<>=#\"\'"
    buff = ""
    content.chars.each_with_index do |c, i|
        len = 0
        if operands.include?(c) then
            if !buff.empty? then
                ret << Token.new(i-buff.length, buff.length, buff)
            end
            len = 0
            buff = ""
        else
            len += 1
            buff << c
        end
    end
    ret
end

def tokenize_file(file)
    ret = nil
    File.open(file, "r") do |fp|
        content = fp.read
        ret = tokenize_text(content)
        ret.each do |e|
            #行の最初を求める
            lstart = backward_line_pos(content, e.offset)
            lend = forward_line_pos(content, e.offset)
            e.line = content.slice(lstart, lend-lstart)
            raise (e.text + ":" + e.line.to_s + ":" + lstart.to_s + "~" + lend.to_s) if e.line == nil || e.line.include?("\n")
        end
    end
    ret.each do |e|
        puts e.text + "[" + e.line + "]"
    end
    ret
end
#行をすべてファイルへ出力する
def tokens_map(file, tokens)
    content = File.open(file, "r") {|fp| fp.read }
    hits = tokens.map{|e| e.text.include?(@find)}
    hits.each do |token|
        content[token.offset, token.offset + token.length] = ''
    end
    File.open(file, "w") {|fp| fp.write(content) }
end

Dir.glob("**/*") do |file|
    next if !file.end_with?(".h") && !file.end_with?(".c")
    tokens_map(file, tokenize_file(file))
end