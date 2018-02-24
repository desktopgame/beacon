#include "generic_type.h"
#include "type_interface.h"
#include "../util/mem.h"

//proto
static void generic_type_tree_delete(vector_item item);

generic_type * generic_type_new(type * core_type) {
	generic_type* ret = (generic_type*)MEM_MALLOC(sizeof(generic_type));
	ret->core_type = core_type;
	ret->type_args_list = vector_new();
	return ret;
}

bool generic_type_assignable(generic_type * left, generic_type * right) {
	//Š®‘S‚É“¯‚¶ƒ|ƒCƒ“ƒ^‚È‚ç”äŠr‚Í•s—v
	if (left == right) {
		return true;
	}
	//Šî–{Œ^‚©Œ^ˆø”‚Ì”‚ªˆá‚¤‚È‚ç false
	if (left->core_type != right->core_type ||
		left->type_args_list->length != right->type_args_list) {
		return false;
	}
	//Œ^ˆø”‚ª 0 ŒÂ‚È‚ç”äŠr•s—v
	if (left->type_args_list->length == 0 &&
		right->type_args_list->length == 0) {
		return true;
	}
	//TODO: in/out ‚Ìl—¶
	//Šî–{Œ^‚ÆŒ^ˆø”‚ª0ŒÂˆÈã‚Åˆê’v‚·‚é‚È‚ç‚»‚ê‚ç‚ğ”äŠr
	bool ret = true;
	for (int i = 0; i < left->type_args_list->length; i++) {
		generic_type* le = (generic_type*)vector_at(left->type_args_list, i);
		generic_type* re = (generic_type*)vector_at(right->type_args_list, i);
		if (!generic_type_assignable(le, re)) {
			ret = false;
			break;
		}
	}
	return ret;
}

void generic_type_delete(generic_type * self) {
	vector_delete(self->type_args_list, generic_type_tree_delete);
	MEM_FREE(self);
}

//private
static void generic_type_tree_delete(vector_item item) {
	generic_type* e = (generic_type*)item;
	generic_type_delete(e);
}