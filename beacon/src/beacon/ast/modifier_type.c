#include "modifier_type.h"
#include <stdio.h>

bool IsStaticModifier(modifier_type type) {
	return (type & MODIFIER_STATIC_T);
}

bool IsNativeModifier(modifier_type type) {
	return (type & MODIFIER_NATIVE_T);
}

bool IsAbstractModifier(modifier_type type) {
	return (type & MODIFIER_ABSTRACT_T);
}

bool IsFinalModifier(modifier_type type) {
	return (type & MODIFIER_FINAL_T);
}

bool IsOverrideModifier(modifier_type type) {
	return (type & MODIFIER_OVERRIDE_T);
}

void PrintModifier(modifier_type type) {
	if (type == (MODIFIER_STATIC_T | MODIFIER_NATIVE_T)) {
		printf("static native");
		return;
	}
	switch (type) {
		case MODIFIER_NONE_T:
			printf("none");
			break;

		case MODIFIER_STATIC_T:
			printf("static");
			break;

		case MODIFIER_NATIVE_T:
			printf("native");
			break;

		case MODIFIER_ABSTRACT_T:
			printf("abstract");
			break;

		case MODIFIER_OVERRIDE_T:
			printf("override");
			break;

		default:
			break;
	}
}
