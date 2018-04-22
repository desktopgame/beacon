#include <stdbool.h>

static bool gGenTop = false;

void debug_set_gen_top(bool gen_top) {
	gGenTop = gen_top;
}

bool debug_get_gen_top() {
	return gGenTop;
}