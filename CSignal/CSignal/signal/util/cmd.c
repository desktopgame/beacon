#include "cmd.h"
#include "text.h"
#include "mem.h"
#include "tool/dump.h"
#include <assert.h>
#include <string.h>
#include "../parse/parser.h"

//proto
static char* cmd_next(cmd_line* self, char* argv[]);
static void cmd_signal_signal(cmd_line* self, char* argv);
static void cmd_signal_sline(cmd_line* self, char* argv);
static void cmd_signal_dump(cmd_line* self, char* argv);

cmd_line * cmd_line_new(int argc) {
	cmd_line* ret = (cmd_line*)MEM_MALLOC(sizeof(cmd_line));
	ret->argc = argc;
	ret->index = 0;
	return ret;
}

char * cmd_nexts(cmd_line * self, char * argv[]) {
	return cmd_next(self, argv);
}

int cmd_nexti(cmd_line * self, char * argv[]) {
	return atoi(cmd_next(self, argv));
}

float cmd_nextf(cmd_line * self, char * argv[]) {
	double d = atof(cmd_next(self, argv));
	return (float)d;
}

bool cmd_nextb(cmd_line * self, char * argv[]) {
	char* str = cmd_nexts(self, argv);
	if (!strcmp(str, "true") || 
		!strcmp(str, "TRUE")
	) {
		return true;
	}
	if (!strcmp(str, "false") || 
		!strcmp(str, "FALSE") ||
		!strcmp(str, "0")
	) {
		return false;
	}
	return false;
}

char * cmd_nextw(cmd_line * self, char * argv[]) {
	char* str = cmd_nexts(self, argv);
	if (str[0] == '-') {
		char* p = str;
		p++;
		return text_strdup(p);
	} else {
		return text_strdup(str);
	}
	return NULL;
}

bool cmd_nexteq(cmd_line * self, char* argv[], char * word) {
	char* e = cmd_nexts(self, argv);
	return !strcmp(e, word);
}

bool cmd_nexteqany(cmd_line * self, char * argv[], int params, ...) {
	va_list ap;
	va_start(ap, params);
	char* e = cmd_nexts(self, argv);
	bool found = false;
	for (int i = 0; i < params; i++) {
		if (!strcmp(e, va_arg(ap, char*))) {
			found = true;
			break;
		}
//		ap++;
	}
	va_end(ap);
	return found;
}

void cmd_signal(int argc, char * argv[]) {
	cmd_line* cmdl = cmd_line_new(argc);
	while (cmdl->index < cmdl->argc) {
		if (cmdl->index == 0) {
			cmd_nexts(cmdl, argv);
			continue;
		}
		char* action = cmd_nexts(cmdl, argv);
		//signal
		if (!strcmp(action, "signal")) {
			cmd_signal_signal(cmdl, argv);
			break;
		//sline
		} else if(!strcmp(action, "sline")) {
			cmd_signal_sline(cmdl, argv);
			break;
		//dump
		} else if(!strcmp(action, "dump")) {
			cmd_signal_dump(cmdl, argv);
			break;
		} else {
			printf("指定の命令を解釈出来ません(%s)", action);
			text_putline();
			break;
		}
	}
}

void cmd_dump(int argc, const char* const argv[]) {
	printf("--- args ---");
	text_putline();
	for (int i = 0; i < argc; i++) {
		char* e = argv[i];
		printf("argv[%d] = %s", i, argv[i]);
		text_putline();
	}
	text_putline();
}

//private
static char* cmd_next(cmd_line* self, char* argv[]) {
	assert(self->index < self->argc);
	char* ret = argv[self->index];
	self->index++;
	return ret;
}

static void cmd_signal_signal(cmd_line* self, char* argv) {
	char* filename = NULL;
	bool strict = false;
	while (self->index < self->argc) {
		char* param = cmd_nexts(self, argv);
		//-file
		if (!strcmp(param, "-file")) {
			filename = cmd_nexts(self, argv);
		}
		//-strict
		if (!strcmp(param, "-strict")) {
			strict = true;
		}
	}
	if (filename == NULL) {
		//定数が二行目に続いているとか出たのでとりあえず消す
		//printf("-fileオプションでファイルを指定してください。");
		//
		text_putline();
		return;
	}
}

static void cmd_signal_sline(cmd_line* self, char* argv) {
	while (self->index < self->argc) {
	}
}

static void cmd_signal_dump(cmd_line* self, char* argv) {
	dump_option opt;
	char* filename = NULL;
	
	while (self->index < self->argc) {
		char* param = cmd_nexts(self, argv);
		//-file
		if (!strcmp(param, "-file")) {
			if (self->index >= self->argc) {
				//定数が二行目に続いているとか出たのでとりあえず消す
				//printf("-fileオプションでファイルを指定してください。");
				//
				text_putline();
				break;
			}
			opt.filename = cmd_nexts(self, argv);
		}
		//-ast
		if (!strcmp(param, "-ast")) {
			opt.ast = true;
		}
		//-il
		if (!strcmp(param, "-il")) {
			opt.il = true;
		}
		//-sg
		if (!strcmp(param, "-sg")) {
			opt.sg = true;
		}
	}
	cmd_tool_dump(&opt);
}