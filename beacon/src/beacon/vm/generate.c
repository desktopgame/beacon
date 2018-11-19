#include "generate.h"
#include "../ast/modifier_type.h"
#include "../env/type_interface.h"
#include "../env/TYPE_IMPL.h"

void GenerateGetField(OpcodeBuf* buf, bc_Field* fi, int index) {
	if(bc_IsStaticModifier(fi->Modifier)) {
		AddOpcodeBuf(buf, OP_GET_STATIC);
		AddOpcodeBuf(buf, fi->Parent->AbsoluteIndex);
		AddOpcodeBuf(buf, index);
	} else {
		AddOpcodeBuf(buf, OP_GET_FIELD);
		AddOpcodeBuf(buf, index);
	}
}

void GenerateGetProperty(OpcodeBuf* buf, bc_Property* prop, int index) {
	if(prop->IsShort) {
		GenerateGetField(buf, prop->SourceRef, bc_GetFieldByPropertyClass(prop->Parent->Kind.Class, prop));
	} else {
		if(bc_IsStaticModifier(prop->Modifier)) {
			AddOpcodeBuf(buf, OP_GET_STATIC_PROPERTY);
			AddOpcodeBuf(buf, prop->Parent->AbsoluteIndex);
			AddOpcodeBuf(buf, index);
		} else {
			AddOpcodeBuf(buf, OP_GET_PROPERTY);
			AddOpcodeBuf(buf, index);
		}
	}
}

void GeneratePutField(OpcodeBuf* buf, bc_Field* fi, int index) {
	if(bc_IsStaticModifier(fi->Modifier)) {
		AddOpcodeBuf(buf, OP_PUT_STATIC);
		AddOpcodeBuf(buf, fi->Parent->AbsoluteIndex);
		AddOpcodeBuf(buf, index);
	} else {
		AddOpcodeBuf(buf, OP_PUT_FIELD);
		AddOpcodeBuf(buf, index);
	}
}

void GeneratePutProperty(OpcodeBuf* buf, bc_Property* prop, int index) {
	if(prop->IsShort) {
		GeneratePutField(buf, prop->SourceRef, bc_GetFieldByPropertyClass(prop->Parent->Kind.Class, prop));
	} else {
		if(bc_IsStaticModifier(prop->Modifier)) {
			AddOpcodeBuf(buf, OP_PUT_STATIC_PROPERTY);
			AddOpcodeBuf(buf, prop->Parent->AbsoluteIndex);
			AddOpcodeBuf(buf, index);
		} else {
			AddOpcodeBuf(buf, OP_PUT_PROPERTY);
			AddOpcodeBuf(buf, index);
		}
	}
}