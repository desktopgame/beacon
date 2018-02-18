#include "bench_mark.h"
#include <stdlib.h>
#include <assert.h>

#include "vector.h"
#include "mem.h"
#include "text.h"

//proto
static void time_ref_vec_delete(vector_item item);

static vector* gTimeRefVec = NULL;

void bench_start() {
	if (gTimeRefVec == NULL) {
		gTimeRefVec = vector_new();
	}
	vector_push(gTimeRefVec, time_ref_get());
}

void bench_end(const char * name, time_printer printer) {
	time_ref* befor = (time_ref*)vector_pop(gTimeRefVec);
	time_ref* after = time_ref_get();

	printer(name, befor, after);

	if (gTimeRefVec->length == 0) {
		vector_delete(gTimeRefVec, time_ref_vec_delete);
		gTimeRefVec = NULL;
	}
	time_ref_delete(befor);
	time_ref_delete(after);
}

void bench_simple(const char * name, time_ref * befor, time_ref * after) {
#if defined(_MSC_VER)
	//https://stackoverflow.com/questions/17250932/how-to-get-the-time-elapsed-in-c-in-milliseconds-windows
	struct timeb start = befor->time;
	struct timeb end = after->time;
	int diff = (int)(1000.0 * (end.time - start.time)
				 + (end.millitm - start.millitm));

	text_printf("%s: %u ミリ秒", name, diff);
	text_putline();
#else
	double diff = difftime(after->time, befor->time);
	text_printf("%s: %f秒", name, diff);
	text_putline();
#endif
}

time_ref * time_ref_get() {
	time_ref* ret = (time_ref*)MEM_MALLOC(sizeof(time_ref));
#if defined(_MSC_VER)
	ftime(&ret->time);
#else
	time(&ret->time);
#endif
	return ret;
}

void time_ref_delete(time_ref * self) {
	MEM_FREE(self);
}
//private
static void time_ref_vec_delete(vector_item item) {
	time_ref* e = (time_ref*)item;
	time_ref_delete(e);
}