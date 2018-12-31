#include "value.h"
#include <assert.h>
#include "../lib/bc_library_interface.h"

// beacon -> C
short bc_ObjectToShort(bc_Object* self) { return 0; }

int bc_ObjectToInt(bc_Object* self) {
        assert(bc_IsIntValue(self));
        return ((bc_Integer*)self)->Value;
}

long bc_ObjectToLong(bc_Object* self) {
        // assert(self->Tag == OBJECT_LONG_T);
        return ((bc_Long*)self)->Value;
}

float bc_ObjectToFloat(bc_Object* self) { return 0.0f; }

double bc_ObjectToDouble(bc_Object* self) {
        assert(bc_IsDoubleValue(self));
        return ((bc_Double*)self)->Value;
}

bool bc_ObjectToBool(bc_Object* self) {
        assert(bc_IsBoolValue(self));
        return ((bc_Bool*)self)->Value;
}

char bc_ObjectToChar(bc_Object* self) {
        assert(bc_IsCharValue(self));
        return ((bc_Char*)self)->Value;
}

// C -> beacon
bc_Object* bc_ShortToObject(short s) { return NULL; }

bc_Object* bc_IntToObject(int i) { return (bc_Object*)bc_NewInteger(i); }

bc_Object* bc_LongToObject(long l) { return (bc_Object*)bc_NewLong(l); }

bc_Object* bc_FloatToObject(float f) { return NULL; }

bc_Object* bc_DoubleToObject(double d) { return (bc_Object*)bc_NewDouble(d); }

bc_Object* bc_BoolToObject(bool b) { return bc_GetBoolObject(b); }

bc_Object* bc_CharToObject(char c) { return (bc_Object*)bc_NewChar(c); }
