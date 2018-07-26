#http://giraffydev.hatenablog.com/entry/2016/10/04/101004
#http://nantonaku-shiawase.hatenablog.com/entry/20110905/1321356759

COMPILER  = clang
CXXDEBUG	= -g -O0 -DDEBUG -MMD -Wall
CXXRELEASE	= -g -O2 -MMD -w
LDFLAGS = -L/usr/local/lib -L/opt/local/lib
LIBS      = 
INCLUDE   = -I/usr/include -I/opt/local/include
TARGETS   = a.out
TARGETDIR = ../bin
SRCROOT   = .
OBJROOT   = ../obj
SRCDIRS  := $(shell find $(SRCROOT) -type d)
SOURCES   = $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))
OBJECTS   = $(addprefix $(OBJROOT)/, $(SOURCES:.c=.o))
OBJDIRS   = $(addprefix $(OBJROOT)/, $(SRCDIRS))
DEPENDS   = $(OBJECTS:.o=.d)

#Debug Build
.PHONY : db
db : CXXFLAGS += $(CXXDEBUG)
db : all

#Release Build
.PHONY : rb
rb : CXXFLAGS += $(CXXRELEASE)
rb : all

#Clean
.PHONY: clean
clean:
	echo "a" | cd $(OBJROOT) | rm -f *.o

all : $(TARGETS)

# 依存ファイルを元に実行ファイルを作る
$(TARGETS): $(OBJECTS) $(LIBS)
	$(COMPILER) -o $(TARGETDIR)/$@ $^ $(LDFLAGS)

# 中間バイナリのディレクトリを掘りながら.cppを中間ファイル.oに
$(OBJROOT)/%.o: $(SRCROOT)/%.c
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(COMPILER) -c -o $@ $< $(CXXFLAGS) $(INCLUDE)
# https://stackoverflow.com/questions/23132047/g-cant-link-with-a-main-executable-file

# 依存関係ファイル
-include $(DEPENDS)