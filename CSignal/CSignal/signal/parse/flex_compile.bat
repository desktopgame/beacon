cd C:\FlexYACC\bin
bison -d C:\Users\Koya\Documents\GitHub\CSignal\CSignal\CSignal\signal\parse\signal.y
flex C:\Users\Koya\Documents\GitHub\CSignal\CSignal\CSignal\signal\parse\signal.l
bison C:\Users\Koya\Documents\GitHub\CSignal\CSignal\CSignal\signal\parse\signal.y  -r all --report-file=conflict.log
move /Y C:\FlexYACC\bin\signal.tab.h C:\Users\Koya\Documents\GitHub\CSignal\CSignal\CSignal\signal\parse\signal.tab.h
move /Y C:\FlexYACC\bin\signal.tab.c C:\Users\Koya\Documents\GitHub\CSignal\CSignal\CSignal\signal\parse\signal.tab.c
move /Y C:\FlexYACC\bin\lex.yy.c C:\Users\Koya\Documents\GitHub\CSignal\CSignal\CSignal\signal\parse\lex.yy.c
move /Y C:\FlexYACC\bin\conflict.log C:\Users\Koya\Documents\GitHub\CSignal\CSignal\CSignal\signal\parse\conflict.log
set /P USR_INPUT_STR = "キーを押して終了"
