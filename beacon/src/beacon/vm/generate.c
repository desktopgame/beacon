#include "generate.h"
#include "../ast/modifier_type.h"
#include "../env/type_interface.h"
#include "../env/type_impl.h"

void generate_get_field(opcode_buf* buf, field* fi, int index) {
	if(modifier_is_static(fi->modifier)) {
		opcode_buf_add(buf, op_get_static);
		opcode_buf_add(buf, fi->parent->absolute_index);
		opcode_buf_add(buf, index);
	} else {
		opcode_buf_add(buf, op_get_field);
		opcode_buf_add(buf, index);
	}
}

void generate_get_property(opcode_buf* buf, property* prop, int index) {
	if(prop->is_short) {
		generate_get_field(buf, prop->source_ref, class_get_field_by_property(prop->parent->u.class_, prop));
	} else {
		if(modifier_is_static(prop->modifier)) {
			opcode_buf_add(buf, op_get_static_property);
			opcode_buf_add(buf, prop->parent->absolute_index);
			opcode_buf_add(buf, index);
		} else {
			opcode_buf_add(buf, op_get_property);
			opcode_buf_add(buf, index);
		}
	}
}

void generate_put_field(opcode_buf* buf, field* fi, int index) {
	if(modifier_is_static(fi->modifier)) {
		opcode_buf_add(buf, op_put_static);
		opcode_buf_add(buf, fi->parent->absolute_index);
		opcode_buf_add(buf, index);
	} else {
		opcode_buf_add(buf, op_put_field);
		opcode_buf_add(buf, index);
	}
}

void generate_put_property(opcode_buf* buf, property* prop, int index) {
	if(prop->is_short) {
		generate_put_field(buf, prop->source_ref, class_get_field_by_property(prop->parent->u.class_, prop));
	} else {
		if(modifier_is_static(prop->modifier)) {
			opcode_buf_add(buf, op_put_static_property);
			opcode_buf_add(buf, prop->parent->absolute_index);
			opcode_buf_add(buf, index);
		} else {
			opcode_buf_add(buf, op_put_property);
			opcode_buf_add(buf, index);
		}
	}
}