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

bool bc_IsIncludeModifier(bc_ModifierType self, int count,
                          bc_ModifierType list[], int* outIndex) {
        (*outIndex) = -1;
        for (int i = 0; i < count; i++) {
                bc_ModifierType e = list[i];
                if ((self & e) > 0) {
                        (*outIndex) = i;
                        return true;
                }
        }
        return false;
}

bc_StringView bc_ModifierTypeToString(bc_ModifierType type) {
        switch (type) {
                case MODIFIER_NONE_T:
                        return bc_InternString("none");
                case MODIFIER_STATIC_T:
                        return bc_InternString("static");
                case MODIFIER_NATIVE_T:
                        return bc_InternString("native");
                case MODIFIER_ABSTRACT_T:
                        return bc_InternString("abstract");
                case MODIFIER_OVERRIDE_T:
                        return bc_InternString("override");
                case MODIFIER_FINAL_T:
                        return bc_InternString("final");
        }
}

bool bc_IsPairIncludeModifier(bc_ModifierType self, bc_ModifierType primary,
                              bc_ModifierType other) {
        return (self & primary) > 0 && (self & other) > 0;
}

bool bc_IsBothIncludeModifier(bc_ModifierType self, bc_ModifierType primary,
                              int count, bc_ModifierType others[],
                              int* outIndex) {
        (*outIndex) = -1;
        if ((self & primary) == 0) {
                return false;
        }
        for (int i = 0; i < count; i++) {
                if ((self & others[i]) > 0) {
                        (*outIndex) = i;
                        return true;
                }
        }
        return false;
}