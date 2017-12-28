#include "modifier_type.h"
#include <stdio.h>

void modifier_print(modifier_type type) {
	switch (type) {
		case modifier_static:
			printf("static");
			break;

		case modifier_native:
			printf("native");
			break;

		default:
			break;
	}
}
