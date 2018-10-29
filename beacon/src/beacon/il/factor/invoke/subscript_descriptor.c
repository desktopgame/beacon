#include "subscript_descriptor.h"
#include "../../../env/generic_type.h"
#include "../../../env/field.h"
#include "../../../env/property.h"
#include "../../../vm/symbol_entry.h"

GenericType* GetSubscriptReceiver(const SubscriptDescriptor* desc) {
	if(desc->Tag == SUBSCRIPT_LOCAL_T) {
		return desc->Kind.Local->GType;
	} else if(desc->Tag == SUBSCRIPT_FIELD_T) {
		return desc->Kind.Field->gtype;
	} else if(desc->Tag == SUBSCRIPT_PROPERTY_T) {
		return desc->Kind.Property->GType;
	}
	return NULL;
}