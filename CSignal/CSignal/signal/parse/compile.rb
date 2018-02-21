# coding: utf-8
require_relative 'ruby_lib/make'
require_relative 'ruby_lib/build'

Make.lex()
Make.yy()
Build.compile()

#0.9秒後にクローズ
times = 0.0
frame = 0.1
length = 0.9
waiter = Thread.new do
    while(times < length)
        sleep(frame)
        times += frame
    end
    exit
end
#入力されたら即座に終了
gets()
times = length
waiter.join()
