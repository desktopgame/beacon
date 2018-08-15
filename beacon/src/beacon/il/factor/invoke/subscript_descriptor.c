#include "subscript_descriptor.h"
#include "../../../env/generic_type.h"
#include "../../../env/field.h"
#include "../../../env/property.h"
#include "../../../vm/symbol_entry.h"

generic_type* subscript_descriptor_receiver(const subscript_descriptor* desc) {
	if(desc->tag == subscript_local_T) {
		return desc->u.local->gtype;
	} else if(desc->tag == subscript_field_T) {
		return desc->u.fi->gtype;
	} else if(desc->tag == subscript_property_T) {
		return desc->u.prop->gtype;
	}
	return NULL;
}