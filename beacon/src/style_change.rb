require "open3"
require "fileutils"
require "date"
class Function
    attr_accessor :name, :parameters, :return_type
    def initialize()
        @name = nil
        @parameters = []
        @return_type = []
    end

    def to_s()
        buf = ""
        buf << return_type + " "
        buf << name + "("
        parameters.each_with_index do |e,i|
            if(e.type == "...") then
                buf << "..."
                break
            end
            buf << e.type + " "
            buf << e.name
            if(i != parameters.length - 1) then
                buf << ", "
            end
        end
        buf << ")"
        buf
    end

    def clone()
        ret = Function.new()
        ret.name = @name
        ret.return_type = @return_type
        @parameters.each do |e|
            ret.parameters << e.clone
        end
        ret
    end

    def ==(other)
        return false if(@name != other.name || @return_type != other.return_type)
        return false if(@parameters.length != other.parameters.length)
        @parameters.each_with_index do |a, i|
            b = other.parameters[i]
            if (a != b)
                return false
            end
        end
        return true
    end

    def !=(other)
        return !(self == other)
    end
end

class Parameter
    attr_accessor :type, :name
    def initialize(type, name)
        @type = type
        @name = name
    end

    def clone()
        Parameter.new(@type, @name)
    end

    def ==(other)
        return @type == other.type && @name == other.name
    end

    def !=(other)
        return !(self == other)
    end
end

def get_first_word(line)
    buffer = ""
    line.chars.each_with_index do |c, i|
        if(i == 0 && c =~ /[a-zA-Z]|_/) then
            buffer << c
        elsif(i > 0 && c =~ /[a-zA-Z0-9]|_/)
            buffer << c
        else
            break
        end
    end
    return buffer, line.slice(buffer.length, line.length - buffer.length).lstrip
end

def get_next_word(line, word)
    return get_first_word(line)
end

def get_char(line, a)
    raise "illegal argument" if a.length != 1
    if(line.chars.first == a) then
        return a, line.slice(1, line.length).lstrip
    else
        return "", line.lstrip
    end
end

def get_pointer(line)
    get_char(line, "*")
end

def get_lparen(line)
    get_char(line, "(")
end

def get_rparen(line)
    get_char(line, ")")
end

def get_comma(line)
    get_char(line, ",")
end

def get_typename(line)
    word, line = get_first_word(line)
    if(word.empty? && line.start_with?("...")) then
        word = "..."
        line = line.slice(3, line.length - 3)
    end
    return "", line if(word.empty?)
    return "", line if(word == "typedef")
    if word == "const" then
        word, line = get_next_word(line, word)
        word = (" const " + word)
    end
    if word == "struct" then
        word, line = get_next_word(line, word)
        word = ("struct " + word)
    end
    #ポインター修飾されているか
    ptr, line = get_pointer(line)
    word << ptr
    while(!ptr.empty?)
        ptr, line = get_pointer(line)
        word << ptr
    end
    return word, line
end

def diff(origin, update)
    if origin.length != update.length
        raise "invalid argument"
    end
    ret = []
    origin.each_with_index do |o_item, i|
        u_item = update[i]
        if(o_item != u_item) then
            ret << u_item
        end
    end
    ret
end

def apply(files, origin, update)
    files.each do |file|
        src = nil
        File.open(file, "r") do |fp|
            src = fp.read()
            origin.each_with_index do |e, i|
                next if !src.include?(e.name)
                o = e
                u = update[i]
                src = src.gsub(o.name, u.name)
            end
        end
        File.open(file, "w") {|fp| fp.write(src) }
    end
end

def find_word(name)
    count = 0
    name.chars.each_with_index do |c,i|
        if(c =~ /[A-Z]/) then
            count += 1
            if(count == 2) then
                return i
            end
        end
    end
end

def rename_special(name, key)
    name = name.downcase
    action_pos = name.rindex("_")
    action = name.slice(action_pos + 1, name.length - action_pos).capitalize
    type = name.slice(0, action_pos)
    words = type.split("_").delete_if{|e| e == key}
    new_name = action + words.map{|e| if e == "il" then "IL" else e.capitalize end }.join
    new_name = new_name.gsub("Instanceof", "InstanceOf")
    new_name = new_name.gsub("Jni", "JNI")
    if(new_name.start_with?("Tostr")) then
        new_name = new_name.slice("Tostr".length, new_name.length - "Tostr".length)
        new_name << "ToString"
    end
    return new_name
end

def rename(name)
    if name.include?("il_factor")
        return rename_special(name, "factor")
    elsif name.include?("il_stmt")
        return rename_special(name, "stmt")
    end
    buf = ""
    cut = true
    name.chars.each do |c|
        if cut then
            c = c.upcase
            cut = false
        end
        if c == "_" then
            cut = true
            next
        end
        buf << c
    end
    #動詞が先に来るように
    pos = find_word(buf)
    action = buf.slice(pos, buf.length - pos)
    type = buf.slice(0, pos)
    buf = action + type
    #ast,fqcnは例外的に全て大文字
    buf.gsub!("Ast", "AST")
    buf.gsub!("Fqcn", "FQCN")
    buf.gsub!("Vm", "VM")
    buf.gsub!("Il", "IL")
    #newが含まれる場合にも例外
    if(buf.start_with?("New") && buf.include?("AST")) then
        pos = buf.index("AST")
        ast_type = buf.slice(3, pos - 3)
        first = buf.slice(0, 3)
        rest = buf.slice(pos, buf.length - pos)
        buf = first + rest + ast_type
    elsif(buf.include?("New") && buf.include?("IL")) then
        pos = buf.index("IL")
        pos2 = buf.index("New")
        ast_type = buf.slice(pos2, pos - pos2)
        first = buf.slice(0, pos2)
        rest = buf.slice(pos, buf.length - pos)
        buf = ast_type + rest + first
    end
    buf
end

decl_files = []
impl_files = []
functions = []
functions_edits = []
Dir.glob("**/*") do |file|
    if(ARGV.length == 0 ||
      (ARGV.length > 0 && ARGV.detect(){|e| file.include?(e)})) then
        decl_files << file if file.end_with?(".h")
        impl_files << file if file.end_with?(".c")
        impl_files << file if file.end_with?(".l")
        impl_files << file if file.end_with?(".y")
    end
end
decl_files.each do |file|
    puts "started " + file
    File.open(file, "r") do |fp|
        src = fp.read()
        src = src.gsub("\[\]", "")
        src = src.gsub(/\/\*[\s\S]*?\*\//m, "")
        src.lines do |line|
            next if line.empty?
            func = Function.new
            #戻り値の型を得る
            return_type, line = get_typename(line)
            word = return_type
            next if return_type.empty?
            func.return_type = word.dup
            #関数名があるか
            name, line = get_next_word(line, return_type)
            word << " " + name
            next if name.empty?
            func.name = name
            #引数並びで開始するか
            lparen, line = get_lparen(line)
            word << lparen
            next if lparen.empty?
            #引数並びで終了するか
            rparen, line = get_rparen(line)
            word << rparen
            if(rparen.length > 0) then
                functions << func
                next
            end
            #引数名をとる
            reader = lparen
            crash = false
            while(true)
                #int
                param_type, line = get_typename(line)
                reader = param_type
                word << param_type
                #引数並びが改行されている場合
                if(param_type.empty?) then
                    crash = true
                    break
                end
                #count
                param_name, line = get_next_word(line, reader)
                reader = param_name
                word << " " + param_name
                #引数並びが改行されている場合
                if(param_name.empty?) then
                    crash = true
                    break
                end
                #パラメータ追加
                param = Parameter.new(param_type, param_name)
                func.parameters << param
                #) のチェック
                rparen, line = get_rparen(line)
                if(!rparen.empty?) then
                    word << rparen
                    break
                end
                #, のチェック
                comma, line = get_comma(line)
                if(!comma.empty?) then
                    word << comma + " "
                end
            end
            functions << func if !crash
        end
    end
end
puts "style change loop ---"
functions.sort! do |a, b|
    a.name.length <=> b.name.length
end
functions_edits << functions
commands = {
    "select" => lambda do
        printf "input selector: "
        selector = STDIN.gets.lstrip.rstrip
        functions_edits.last.select{|e| e.name.include?(selector)}.each{|e| puts e}
    end,
    "all" => lambda do
        functions_edits.last.each{|e| puts e.to_s }
    end,
    "update" => lambda do
        printf "input selector: "
        selector = STDIN.gets.lstrip.rstrip
        printf "input changed: "
        changed = STDIN.gets.lstrip.rstrip
        edited = functions_edits.last.map{|e| e.clone }
        edited.select{|e| e.name.include?(selector)}.each {|e| e.name = e.name.gsub(selector, changed)}
        functions_edits.last.select{|e| e.name.include?(selector)}.each{|e| puts e.name + " => " + e.name.gsub(selector, changed)}
        functions_edits << edited
    end,
    "commit" => lambda do
        edits = functions_edits.last
        functions_edits.clear
        functions_edits << edits
    end,
    "undo" => lambda do
        if(functions_edits.length == 1) then
            puts "can't undo"
        else
            functions_edits.pop
        end
    end,
    "apply" => lambda do
        if functions_edits.length > 1 then
            puts "do not committed"
        else
            apply(decl_files + impl_files, functions, functions_edits.last)
        end
    end,
    "help" => lambda do
        commands.each_pair do |key, val|
            puts "    -" + key
        end
    end,
    "abort" => lambda do
        abort
    end,
    "auto" => lambda do
        edited = []
        printf "input selector: "
        selector = STDIN.gets.lstrip.rstrip
        term = false
        functions_edits.last.each_with_index do |e, i|
            if term || !e.name.include?(selector) then
                edited << e.clone
                next
            end
            auto_name = rename(e.name)
            printf("%s => ($%s)", e.name, auto_name)
            new_name = STDIN.gets.lstrip.rstrip
            #新しい名前を入力する
            clone = e.clone
            edited << clone
            if new_name == ":skip" || new_name.empty? then
                next
            elsif new_name == ":break" then
                term = true
                next
            elsif new_name == "$" then
                clone.name = auto_name
            else
                clone.name = new_name
            end
        end
        functions_edits << edited
    end,
    "dump" => lambda do
        File.open("style_dump.text", "w") do |fp|
            functions_edits.last.each do |e|
                fp.puts e
            end
        end
    end
}
while(true)
    input = STDIN.gets.lstrip.rstrip
    if(input == "quit" || input == "exit") then
        puts "bye."
        break
    end
    if(commands.has_key?(input)) then
        commands[input].()
    else
        puts sprintf("undefined command: %s", input)
    end
end