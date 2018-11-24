#include "generate.h"
#include "../ast/modifier_type.h"
#include "../env/TYPE_IMPL.h"
#include "../env/type_interface.h"

void bc_GenerateGetField(bc_OpcodeBuf* buf, bc_Field* fi, int index) {
        if (bc_IsStaticModifier(BC_MEMBER_MODIFIER(fi))) {
                bc_AddOpcodeBuf(buf, OP_GET_STATIC);
                bc_AddOpcodeBuf(buf, BC_MEMBER_TYPE(fi)->AbsoluteIndex);
                bc_AddOpcodeBuf(buf, index);
        } else {
                bc_AddOpcodeBuf(buf, OP_GET_FIELD);
                bc_AddOpcodeBuf(buf, index);
        }
}

void bc_GenerateGetProperty(bc_OpcodeBuf* buf, bc_Property* prop, int index) {
        if (prop->IsShort) {
                bc_GenerateGetField(
                    buf, prop->SourceRef,
                    bc_GetFieldByPropertyClass(prop->Parent->Kind.Class, prop));
        } else {
                if (bc_IsStaticModifier(prop->Modifier)) {
                        bc_AddOpcodeBuf(buf, OP_GET_STATIC_PROPERTY);
                        bc_AddOpcodeBuf(buf, prop->Parent->AbsoluteIndex);
                        bc_AddOpcodeBuf(buf, index);
                } else {
                        bc_AddOpcodeBuf(buf, OP_GET_PROPERTY);
                        bc_AddOpcodeBuf(buf, index);
                }
        }
}

void bc_GeneratePutField(bc_OpcodeBuf* buf, bc_Field* fi, int index) {
        if (bc_IsStaticModifier(BC_MEMBER_MODIFIER(fi))) {
                bc_AddOpcodeBuf(buf, OP_PUT_STATIC);
                bc_AddOpcodeBuf(buf, BC_MEMBER_TYPE(fi)->AbsoluteIndex);
                bc_AddOpcodeBuf(buf, index);
        } else {
                bc_AddOpcodeBuf(buf, OP_PUT_FIELD);
                bc_AddOpcodeBuf(buf, index);
        }
}

void bc_GeneratePutProperty(bc_OpcodeBuf* buf, bc_Property* prop, int index) {
        if (prop->IsShort) {
                bc_GeneratePutField(
                    buf, prop->SourceRef,
                    bc_GetFieldByPropertyClass(prop->Parent->Kind.Class, prop));
        } else {
                if (bc_IsStaticModifier(prop->Modifier)) {
                        bc_AddOpcodeBuf(buf, OP_PUT_STATIC_PROPERTY);
                        bc_AddOpcodeBuf(buf, prop->Parent->AbsoluteIndex);
                        bc_AddOpcodeBuf(buf, index);
                } else {
                        bc_AddOpcodeBuf(buf, OP_PUT_PROPERTY);
                        bc_AddOpcodeBuf(buf, index);
                }
        }
}