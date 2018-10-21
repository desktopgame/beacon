#include "modifier_type.h"
#include <stdio.h>

bool IsStaticModifier(ModifierType type) {
	return (type & MODIFIER_STATIC_T);
}

bool IsNativeModifier(ModifierType type) {
	return (type & MODIFIER_NATIVE_T);
}

bool IsAbstractModifier(ModifierType type) {
	return (type & MODIFIER_ABSTRACT_T);
}

bool IsFinalModifier(ModifierType type) {
	return (type & MODIFIER_FINAL_T);
}

bool IsOverrideModifier(ModifierType type) {
	return (type & MODIFIER_OVERRIDE_T);
}

void PrintModifier(ModifierType type) {
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
