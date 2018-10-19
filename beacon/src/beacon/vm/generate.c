#include "generate.h"
#include "../ast/modifier_type.h"
#include "../env/type_interface.h"
#include "../env/TYPE_IMPL.h"

void GenerateGetField(OpcodeBuf* buf, field* fi, int index) {
	if(IsStaticModifier(fi->modifier)) {
		AddOpcodeBuf(buf, OP_GET_STATIC);
		AddOpcodeBuf(buf, fi->parent->absolute_index);
		AddOpcodeBuf(buf, index);
	} else {
		AddOpcodeBuf(buf, OP_GET_FIELD);
		AddOpcodeBuf(buf, index);
	}
}

void GenerateGetProperty(OpcodeBuf* buf, property* prop, int index) {
	if(prop->is_short) {
		GenerateGetField(buf, prop->source_ref, GetFieldByPropertyClass(prop->parent->u.class_, prop));
	} else {
		if(IsStaticModifier(prop->modifier)) {
			AddOpcodeBuf(buf, OP_GET_STATIC_property);
			AddOpcodeBuf(buf, prop->parent->absolute_index);
			AddOpcodeBuf(buf, index);
		} else {
			AddOpcodeBuf(buf, OP_GET_PROPERTY);
			AddOpcodeBuf(buf, index);
		}
	}
}

void GeneratePutField(OpcodeBuf* buf, field* fi, int index) {
	if(IsStaticModifier(fi->modifier)) {
		AddOpcodeBuf(buf, OP_PUT_STATIC);
		AddOpcodeBuf(buf, fi->parent->absolute_index);
		AddOpcodeBuf(buf, index);
	} else {
		AddOpcodeBuf(buf, OP_PUT_FIELD);
		AddOpcodeBuf(buf, index);
	}
}

void GeneratePutProperty(OpcodeBuf* buf, property* prop, int index) {
	if(prop->is_short) {
		GeneratePutField(buf, prop->source_ref, GetFieldByPropertyClass(prop->parent->u.class_, prop));
	} else {
		if(IsStaticModifier(prop->modifier)) {
			AddOpcodeBuf(buf, OP_PUT_STATIC_property);
			AddOpcodeBuf(buf, prop->parent->absolute_index);
			AddOpcodeBuf(buf, index);
		} else {
			AddOpcodeBuf(buf, OP_PUT_PROPERTY);
			AddOpcodeBuf(buf, index);
		}
	}
}