#pragma once
#ifndef SIGNAL_ENV_TYPE_IINTERFACE_H
#define SIGNAL_ENV_TYPE_IINTERFACE_H
#include "../type_interface.h"
#include "../namespace.h"
#include "../../util/vector.h"
struct method;
//struct type;
/**
 * インターフェースを表す構造体.
 */
typedef struct interface_ {
	char* name;
	vector* impl_list;
	vector* method_list;
	namespace_* location;
} interface_;

type* type_wrap_interface(interface_* self);

interface_* interface_new(const char* name);

void interface_add_method(interface_* self, struct method* m);

void interface_dump(interface_* self, int depth);

void interface_delete(interface_* self);
#endif // !SIGNAL_ENV_TYPE_IINTERFACE_H
