#include "il_factor_super_impl.h"
#include <stdio.h>
#include "../../vm/enviroment.h"
#include "../../util/text.h"
#include "../../env/class.h"

void il_factor_super_dump(il_factor_super * self, int depth) {
	text_putindent(depth);
	printf("super");
	text_putline();
}

void il_factor_super_generate(il_factor_super * self, enviroment * env) {
}

class_ * il_factor_super_eval(il_factor_super * self, enviroment * env) {
	return NULL;
}

void il_factor_super_delete(il_factor_super * self) {
}
