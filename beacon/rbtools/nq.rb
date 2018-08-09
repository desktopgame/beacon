#http://obelisk.hatenablog.com/entry/2017/07/21/164220
N = 4

class EightQueen
  class Step
    def initialize(x, y)
      @x, @y = x, y
      @parent = nil
      @depth = 0
    end
    attr_accessor :x, :y, :parent, :depth
  end
  
  def initialize(x, y)
    @stack = [Step.new(x, y)]
  end
  
  def solve
    #Step{a, nxt}, Integer{y, board[][]}
    while (a = @stack.pop)
      y = a.y + 1
      board = get_board(a)
      N.times do |x|
        next if board[y][x] == 1
        nxt = Step.new(x, y)
        nxt.parent = a
        nxt.depth = a.depth + 1
        finish(nxt) if nxt.depth == N - 1
        @stack.push(nxt)
      end
    end
    raise "No answer."
  end
  
  def get_board(a)
    #board, d, x1, x2
    board = Array.new(N) {Array.new(N, 0)}
    begin
      N.times do |i|
        board[i][a.x] = 1
        board[i] = Array.new(N, 1) if i == a.y
        d = (i - a.y).abs
        next if d.zero?
        x1 = a.x - d
        x2 = a.x + d
        board[i][x1] = 1 if x1 >= 0
        board[i][x2] = 1 if x2 < N
      end
    end while (a = a.parent)
    board
  end
  
  def finish(a)
    bd = Array.new(N) {"." * N}
    while a
      bd[a.y][a.x] = "@"
      a = a.parent
    end
    bd.map {|x| puts x}
    exit
  end
end

EightQueen.new(rand(N), 0).solve