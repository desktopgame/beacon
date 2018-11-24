#include "subscript_descriptor.h"
#include "../../../env/field.h"
#include "../../../env/generic_type.h"
#include "../../../env/property.h"
#include "../../../vm/symbol_entry.h"

bc_GenericType* bc_GetSubscriptReceiver(const bc_SubscriptDescriptor* desc) {
        if (desc->Tag == SUBSCRIPT_LOCAL_T) {
                return desc->Kind.Local->GType;
        } else if (desc->Tag == SUBSCRIPT_FIELD_T) {
                return desc->Kind.Field->GType;
        } else if (desc->Tag == SUBSCRIPT_PROPERTY_T) {
                return desc->Kind.Property->GType;
        }
        return NULL;
}