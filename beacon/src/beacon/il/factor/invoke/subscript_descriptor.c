#include "subscript_descriptor.h"
#include "../../../env/generic_type.h"
#include "../../../env/field.h"
#include "../../../env/property.h"
#include "../../../vm/symbol_entry.h"

generic_type* subscript_descriptor_receiver(const subscript_descriptor* desc) {
	if(desc->tag == SUBSCRIPT_LOCAL_T) {
		return desc->u.local->GType;
	} else if(desc->tag == SUBSCRIPT_FIELD_T) {
		return desc->u.fi->gtype;
	} else if(desc->tag == SUBSCRIPT_PROPERTY_T) {
		return desc->u.prop->gtype;
	}
	return NULL;
}