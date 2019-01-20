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