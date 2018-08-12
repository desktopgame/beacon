require 'strscan'

def  lexical_analysis(str)
  s = StringScanner.new((str+" ").gsub!(/ /, ""))
  arr = []
  may_sign = true
  sign = ""
  while !s.eos?
    #次にマイナスがきたら単項演算子
    # +と-と数値 以外の場合は,次が単項演算子プラスマイナスの可能性
    if s.scan(/(\*\*)/)
      arr << s[0]
      may_sign = true
    end
    if s.scan(/(\*|\/|\%|\(|\))/) 
      arr << s[0]
      may_sign = true
    end
    if s.scan(/(\+|\-)/)
      if may_sign
        sign = s[0]
      else
        arr << s[0]
      end
    end
    if s.scan(/(\d+)/)
      arr << sign + s[0]
      sign = ""
      may_sign = false
    end
  end
  arr
end

def left_associate?(operator)
  return false if operator == "**"
  true
end
def shunting_yard(arr)
  #大きいほど優先される
  priority = {"*"=>3, "/"=>3, "%"=>3, "+"=>2, "-"=>2, "**"=>4}
  result = []
  stack = [] #演算子トークン
  arr.each do |data|
    if data =~ /((\d+)|(\+\d+)|(\-\d+))/
      result << data 
    elsif data =~ /(\()/ #左括弧の場合
      stack << data
    elsif data =~ /(\))/ #右括弧の場合
      exist = false
      while stack.length != 0
        a = stack.pop
        if a == "("
          exist = true
          break
        else
          result << a
        end
      end
      raise "kakko error" if !exist
    else #演算子の場合
      if stack.length != 0 && stack.last !="("
        if (left_associate?(data) && (priority[data] <= priority[stack.last])) or
            (!left_associate?(data) && (priority[data] < priority[stack.last]))
          result << stack.pop
        end
      end
      stack << data
    end 
  end
  #トークン読み込みが完了. 演算子トークンが残っている場合resultに移動する
  return result if stack.nil?

  stack.reverse!
  stack.each do |ope|
    raise "kakko error" if ope =='(' || ope == ')'
    result << ope
  end
  result
end

def _calc(num1, num2, operator)
  raise "argument is not correct" if num1.nil? || num2.nil?
  a = num1.to_f ; b = num2.to_f
  return a + b if operator == "+"
  return a - b if operator == "-" || operator == "\u2212"
  return a * b if operator == "*"
  return a / b if operator == "/"
  return a % b if operator == "%"
  return a ** b if operator == "**"
  raise "operator is not correct"
end
def calculate(datas)
  num_stack = []
  datas.each do |data|
    if data =~ /\d/
      num_stack << data 
    else
      a = num_stack.pop
      b = num_stack.pop
      num_stack << _calc(b, a, data)
    end
  end
    raise "argument is not correct" if num_stack.length != 1
    num_stack
end

arr = lexical_analysis ("  3 + 4 * 2 / ( 1 - 5 ) ** 2 ** 3")
rpn =  reverse_polish_notation = shunting_yard(arr)
p calculate(rpn)   #<= wikiに載ってる問題

question = [
  "2+3*4",
  "2*3+4",
  "2*3*4",
  "(-5)",
  "(3+4)",
  "2*(3+4)",
  "2+(3-4)*5",
  "(3-4)*5",
  "(-3-4)*5",
  "(3-4)*(-5)",
  "(-3-4)*-5",
  "(-3-4)*-5-35",
  "(-3-4)*-5*2",
  "2*(3+4)",
  "2/3",
  "(3*8)/(8-2)",
]

question.each do |q|
  p calculate ( shunting_yard ( lexical_analysis( q ) ) ) 
   #<= 参照URLに載っている問題
end