#include "modifier_type.h"
#include <stdio.h>

bool IsStaticModifier(modifier_type type) {
	return (type & modifier_static_T);
}

bool IsNativeModifier(modifier_type type) {
	return (type & modifier_native_T);
}

bool IsAbstractModifier(modifier_type type) {
	return (type & modifier_abstract_T);
}

bool IsFinalModifier(modifier_type type) {
	return (type & modifier_final_T);
}

bool IsOverrideModifier(modifier_type type) {
	return (type & modifier_override_T);
}

void PrintModifier(modifier_type type) {
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
