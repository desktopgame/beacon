#include "logger.h"
#include <assert.h>
#include "io.h"

static FILE* gLogFp = NULL;
static void print_level(FILE* fp, log_level level);

void logger_init() {
	#if defined(DEBUG)
	assert(gLogFp == NULL);
	gLogFp = fopen("log.text", "w+");
	#endif
}

int logger_flog(log_level level, FILE* fp, const char* filename, int lineno, const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	int ret = logger_vflog(level, fp, filename, lineno, fmt, ap);
	va_end(ap);
	return ret;
}

int logger_vflog(log_level level, FILE* fp, const char* filename, int lineno, const char* fmt, va_list ap) {
	int ret = 0;
	print_level(fp, level);
	int writes = vfprintf(fp, fmt, ap);
	int max = 32;
	if(writes < max) {
		int c = writes;
		while(c < max) {
			fprintf(fp, " ");
			c++;
		}
	}
	fprintf(fp, "    [%s<%d>]", filename, lineno);
	fprintf(fp, "\n");
	return writes;
}

int logger_log(log_level level, const char* filename, int lineno, const char* fmt, ...) {
	va_list ap;
	va_list c;
	va_start(ap, fmt);
	va_copy(c, ap);
	logger_vflog(level, stdout, filename, lineno, fmt, ap);
	#if defined(DEBUG)
	if(gLogFp != NULL) {
		logger_vflog(level, gLogFp, filename, lineno, fmt, c);
	}
	#endif
	va_end(c);
	va_end(ap);
	return 0;
}

void logger_destroy() {
	#if defined(DEBUG)
	fclose(gLogFp);
	gLogFp = NULL;
	#endif
}
//private
static void print_level(FILE* fp, log_level level) {
	switch(level) {
		case log_debug_T:
			fprintf(fp, "[debug]");
			break;
		case log_warn_T:
			fprintf(fp, "[warn]");
			break;
		case log_fetal_T:
			fprintf(fp, "[fetal]");
			break;
	}
}