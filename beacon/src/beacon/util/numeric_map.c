#include "numeric_map.h"
#include "mem.h"

static void numeric_map_eachImpl(numeric_map* self, numeric_tree_action a);

numeric_map* numeric_map_new() {
	numeric_map* ret = (numeric_map*)MEM_MALLOC(sizeof(numeric_map));
	ret->key = 0;
	ret->item = NULL;
	ret->parent = NULL;
	ret->left = NULL;
	ret->right = NULL;
	return ret;
}

numeric_map* numeric_map_put(numeric_map* self, numeric_key key, numeric_map_item item) {
	int comp = numeric_map_compare(self, key);
	if(comp == 0) {
		self->item = item;
		return self;
	} else if(comp < 0) {
		if(self->left == NULL) {
			numeric_map* nl = numeric_map_new();
			self->left = nl;
			nl->parent = self;
			nl->key = key;
			nl->item = item;
		} else {
			return numeric_map_put(self->left, key, item);
		}
	} else if(comp > 0) {
		if(self->right == NULL) {
			numeric_map* nr = numeric_map_new();
			self->right = nr;
			nr->parent = self;
			nr->key = key;
			nr->item = item;
		} else {
			return numeric_map_put(self->right, key, item);
		}
	}
	return NULL;
}

numeric_map* numeric_map_cell(numeric_map* self, numeric_key key) {
	int comp = numeric_map_compare(self, key);
	if(comp == 0) {
		return self;
	} else if(comp < 0) {
		if(self->left == NULL) {
			return NULL;
		}
		return numeric_map_cell(self->left, key);
	} else if(comp > 0) {
		if(self->right == NULL) {
			return NULL;
		}
		return numeric_map_cell(self->right, key);
	}
	return NULL;
}

numeric_map_item numeric_map_get(numeric_map* self, numeric_key key) {
	numeric_map* cell = numeric_map_cell(self, key);
	if(cell == NULL) {
		return NULL;
	}
	return cell->item;
}

int numeric_map_compare(numeric_map* self, numeric_key key) {
	return (int)self->key - (int)key;
}

void numeric_map_each(numeric_map* self, numeric_tree_action a) {
	numeric_map_eachImpl(self, a);
}

void numeric_map_delete(numeric_map* self, numeric_tree_element_deleter deleter) {
	if(self == NULL) {
		return;
	}
	//先に子要素を開放する
	if (self->left != NULL) {
		numeric_map_delete(self->left, deleter);
		self->left = NULL;
	}
	if (self->right != NULL) {
		numeric_map_delete(self->right, deleter);
		self->right = NULL;
	}
	if (self->item != NULL) {
		deleter(self->key, self->item);
		//MEM_FREE(self->key);
	}
	MEM_FREE(self);
}

void numeric_map_deleter_null(numeric_key name, numeric_map_item item) {
}

void numeric_map_deleter_free(numeric_key name, numeric_map_item item) {
	MEM_FREE(item);
}
//private
static void numeric_map_eachImpl(numeric_map* self, numeric_tree_action a) {
	if (self->left != NULL) {
		numeric_map_eachImpl(self->left, a);
	}
	//同じならそれはルート要素
	if (self->key != 0) {
		a(self->key, self->item);
	}
	if (self->right != NULL) {
		numeric_map_eachImpl(self->right, a);
	}
}