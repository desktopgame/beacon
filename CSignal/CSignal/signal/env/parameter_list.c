#include "parameter_list.h"
#include <stdlib.h>
#include "parameter.h"
#include "../util/text.h"

//proto
static void parameter_list_delete_impl(list_item item);

parameter_list * parameter_list_new() {
	return list_new();
}

void parameter_list_push(parameter_list * self, parameter * child) {
	list_add(self, child);
}

void parameter_list_delete(parameter_list * self) {
	list_delete(self, parameter_list_delete_impl);
}

//private
static void parameter_list_delete_impl(list_item item) {
	parameter_delete((parameter*)item);
}