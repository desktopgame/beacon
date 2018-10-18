require "open3"
require "fileutils"
require "date"
#検索語句と置換語の単語を入力する
printf("find word: ")
@find = STDIN.gets.lstrip.rstrip
printf("replace word: ")
@replace = STDIN.gets.lstrip.rstrip

class Token
    attr_accessor :offset, :length, :text, :line, :column_start, :column_end

    def initialize(offset, length, text)
        @offset = offset
        @length = length
        @text = text
    end
end

def make_hit_line(tok)
    buff = ""
    tok.column_start.times do |i|
        buff << " "
    end
    buff << "^"
    buff
end

def forward_line_pos(content, pos)
    ret = pos
    col_end = 0
    while(content[ret] != "\n")
        ret += 1
        col_end += 1
        if(ret >= content.length) then
            return [content.length, col_end]
        end
    end
    [ret - 1, col_end]
end

def backward_line_pos(content, pos)
    ret = pos
    col_start = 0
    while(content[ret] != "\n")
        ret -= 1
        col_start += 1
        if(ret < 0) then
            return [0, col_start]
        end
    end
    [ret + 1, col_start]
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
            lstart, cstart = backward_line_pos(content, e.offset)
            lend, cend = forward_line_pos(content, e.offset)
            e.line = content.slice(lstart, lend-lstart).lstrip.rstrip
            e.column_start = cstart
            e.column_end = cend
            raise (e.text + ":" + e.line.to_s + ":" + lstart.to_s + "~" + lend.to_s) if e.line == nil || e.line.include?("\n")
        end
    end
    ret
end
#行をすべてファイルへ出力する
def tokens_map(file, tokens)
    content = File.open(file, "r") {|fp| fp.read }
    hits = tokens.select{|e| e.text.include?(@find)}
    if(hits.length == 0) then
        return
    end
    puts sprintf("file: %s hits: %d", file, hits.length)
    hits = hits.select do |token|
        puts ("    " + token.line)
        puts ("    " + make_hit_line(token))
        puts
        #トークンを変換するかどうか
        cmd = nil
        while(cmd == nil)
            cmd = STDIN.gets.lstrip.rstrip
            if cmd == "y" then
                next true
            elsif cmd == "n" then
                next false
            elsif cmd == "abort" then
                abort()
            else
                cmd = nil
                puts(sprintf("undefined command: %s", cmd))
            end
        end
    end
end

Dir.glob("**/*") do |file|
    next if !file.end_with?(".h") && !file.end_with?(".c")
    tokens_map(file, tokenize_file(file))
end