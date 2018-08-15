#ifndef BEACON_IL_FACTOR_INVOKE_SUBSCRIPT_DESCRIPTOR_H
#define BEACON_IL_FACTOR_INVOKE_SUBSCRIPT_DESCRIPTOR_H

struct operator_overload;
struct symbol_entry;
struct field;
struct property;

typedef enum subscript_tag {
	subscript_local_T,
	subscript_field_T,
	subscript_property_T,
	subscript_undefined_T
} subscript_tag;

typedef struct subscript_descriptor {
	subscript_tag tag;
	struct operator_overload* opov;
	int index;
	union {
		struct symbol_entry* local;
		struct field* fi;
		struct property* prop;
	} u;
} subscript_descriptor;

struct generic_type* subscript_descriptor_receiver(const subscript_descriptor* desc);
#endif