#include "modifier_type.h"
#include <stdio.h>

bool bc_IsStaticModifier(bc_ModifierType type) {
	return (type & MODIFIER_STATIC_T);
}

bool bc_IsNativeModifier(bc_ModifierType type) {
	return (type & MODIFIER_NATIVE_T);
}

bool bc_IsAbstractModifier(bc_ModifierType type) {
	return (type & MODIFIER_ABSTRACT_T);
}

bool bc_IsFinalModifier(bc_ModifierType type) {
	return (type & MODIFIER_FINAL_T);
}

bool bc_IsOverrideModifier(bc_ModifierType type) {
	return (type & MODIFIER_OVERRIDE_T);
}

void bc_PrintModifier(bc_ModifierType type) {
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
