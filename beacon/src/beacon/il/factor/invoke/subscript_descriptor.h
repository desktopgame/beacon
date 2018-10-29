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
	SubscriptTag Tag;
	struct OperatorOverload* Operator;
	int Index;
	union {
		struct SymbolEntry* Local;
		struct Field* Field;
		struct Property* Property;
	} Kind;
} SubscriptDescriptor;

struct GenericType* GetSubscriptReceiver(const SubscriptDescriptor* desc);
#endif