#include "modifier_type.h"
#include <stdio.h>

modifier_type modifier_static_native() {
	return modifier_static | modifier_native;
}

bool modifier_is_static(modifier_type type) {
	return (type & modifier_static);
}

bool modifier_is_native(modifier_type type) {
	return (type & modifier_native);
}

bool modifier_is_abstract(modifier_type type) {
	return (type & modifier_abstract);
}

void modifier_print(modifier_type type) {
	if (type == (modifier_static | modifier_native)) {
		text_printf("static native");
		return;
	}
	switch (type) {
		case modifier_none:
			text_printf("none");
			break;

		case modifier_static:
			text_printf("static");
			break;

		case modifier_native:
			text_printf("native");
			break;

		case modifier_abstract:
			text_printf("abstract");
			break;

		default:
			break;
	}
}
