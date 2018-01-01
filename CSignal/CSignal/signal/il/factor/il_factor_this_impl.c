#include "il_factor_this_impl.h"
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/class.h"

void il_factor_this_dump(il_factor_this * self, int depth) {
	text_putindent(depth);
	printf("this");
	text_putline();
}

void il_factor_this_generate(il_factor_this * self, enviroment * env) {
}

class_ * il_factor_this_eval(il_factor_this * self, enviroment * env) {
	return NULL;
}

void il_factor_this_delete(il_factor_this * self) {
}
