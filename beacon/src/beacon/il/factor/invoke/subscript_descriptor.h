#ifndef BEACON_IL_FACTOR_INVOKE_SUBSCRIPT_DESCRIPTOR_H
#define BEACON_IL_FACTOR_INVOKE_SUBSCRIPT_DESCRIPTOR_H

struct OperatorOverload;
struct SymbolEntry;
struct Field;
struct Property;

typedef enum SubscriptTag {
	SUBSCRIPT_LOCAL_T,
	SUBSCRIPT_FIELD_T,
	SUBSCRIPT_PROPERTY_T,
	SUBSCRIPT_UNDEFINED_T
} SubscriptTag;

typedef struct SubscriptDescriptor {
	SubscriptTag tag;
	struct OperatorOverload* opov;
	int index;
	union {
		struct SymbolEntry* local;
		struct Field* fi;
		struct Property* prop;
	} u;
} SubscriptDescriptor;

struct GenericType* SubscriptDescriptor_receiver(const SubscriptDescriptor* desc);
#endif