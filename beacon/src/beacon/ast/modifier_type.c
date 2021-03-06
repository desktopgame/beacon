#include "modifier_type.h"
#include <stdio.h>

bool modifier_is_static(modifier_type type) {
	return (type & modifier_static_T);
}

bool modifier_is_native(modifier_type type) {
	return (type & modifier_native_T);
}

bool modifier_is_abstract(modifier_type type) {
	return (type & modifier_abstract_T);
}

bool modifier_is_final(modifier_type type) {
	return (type & modifier_final_T);
}

bool modifier_is_override(modifier_type type) {
	return (type & modifier_override_T);
}

void modifier_print(modifier_type type) {
	if (type == (modifier_static_T | modifier_native_T)) {
		printf("static native");
		return;
	}
	switch (type) {
		case modifier_none_T:
			printf("none");
			break;

		case modifier_static_T:
			printf("static");
			break;

		case modifier_native_T:
			printf("native");
			break;

		case modifier_abstract_T:
			printf("abstract");
			break;

		case modifier_override_T:
			printf("override");
			break;

		default:
			break;
	}
}
