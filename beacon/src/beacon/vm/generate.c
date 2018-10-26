#include "generate.h"
#include "../ast/modifier_type.h"
#include "../env/type_interface.h"
#include "../env/TYPE_IMPL.h"

void GenerateGetField(OpcodeBuf* buf, Field* fi, int index) {
	if(IsStaticModifier(fi->modifier)) {
		AddOpcodeBuf(buf, OP_GET_STATIC);
		AddOpcodeBuf(buf, fi->parent->absolute_index);
		AddOpcodeBuf(buf, index);
	} else {
		AddOpcodeBuf(buf, OP_GET_FIELD);
		AddOpcodeBuf(buf, index);
	}
}

void GenerateGetProperty(OpcodeBuf* buf, Property* prop, int index) {
	if(prop->IsShort) {
		GenerateGetField(buf, prop->SourceRef, GetFieldByPropertyClass(prop->Parent->u.class_, prop));
	} else {
		if(IsStaticModifier(prop->Modifier)) {
			AddOpcodeBuf(buf, OP_GET_STATIC_PROPERTY);
			AddOpcodeBuf(buf, prop->Parent->absolute_index);
			AddOpcodeBuf(buf, index);
		} else {
			AddOpcodeBuf(buf, OP_GET_PROPERTY);
			AddOpcodeBuf(buf, index);
		}
	}
}

void GeneratePutField(OpcodeBuf* buf, Field* fi, int index) {
	if(IsStaticModifier(fi->modifier)) {
		AddOpcodeBuf(buf, OP_PUT_STATIC);
		AddOpcodeBuf(buf, fi->parent->absolute_index);
		AddOpcodeBuf(buf, index);
	} else {
		AddOpcodeBuf(buf, OP_PUT_FIELD);
		AddOpcodeBuf(buf, index);
	}
}

void GeneratePutProperty(OpcodeBuf* buf, Property* prop, int index) {
	if(prop->IsShort) {
		GeneratePutField(buf, prop->SourceRef, GetFieldByPropertyClass(prop->Parent->u.class_, prop));
	} else {
		if(IsStaticModifier(prop->Modifier)) {
			AddOpcodeBuf(buf, OP_PUT_STATIC_PROPERTY);
			AddOpcodeBuf(buf, prop->Parent->absolute_index);
			AddOpcodeBuf(buf, index);
		} else {
			AddOpcodeBuf(buf, OP_PUT_PROPERTY);
			AddOpcodeBuf(buf, index);
		}
	}
}