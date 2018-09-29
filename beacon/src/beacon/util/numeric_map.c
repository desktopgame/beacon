#include "numeric_map.h"
#include "mem.h"

static void EachNumericMapImpl(NumericMap* self, NumericMapAction a);

NumericMap* NewNumericMap() {
	NumericMap* ret = (NumericMap*)MEM_MALLOC(sizeof(NumericMap));
	ret->key = 0;
	ret->item = NULL;
	ret->parent = NULL;
	ret->left = NULL;
	ret->right = NULL;
	return ret;
}

NumericMap* PutNumericMap(NumericMap* self, NumericMapKey key, NumericMapItem item) {
	int comp = CompareNumericMap(self, key);
	if(comp == 0) {
		self->item = item;
		return self;
	} else if(comp < 0) {
		if(self->left == NULL) {
			NumericMap* nl = NewNumericMap();
			self->left = nl;
			nl->parent = self;
			nl->key = key;
			nl->item = item;
			return nl;
		} else {
			return PutNumericMap(self->left, key, item);
		}
	} else if(comp > 0) {
		if(self->right == NULL) {
			NumericMap* nr = NewNumericMap();
			self->right = nr;
			nr->parent = self;
			nr->key = key;
			nr->item = item;
			return nr;
		} else {
			return PutNumericMap(self->right, key, item);
		}
	}
	return NULL;
}

NumericMap* GetNumericMapCell(NumericMap* self, NumericMapKey key) {
	int comp = CompareNumericMap(self, key);
	if(comp == 0) {
		return self;
	} else if(comp < 0) {
		if(self->left == NULL) {
			return NULL;
		}
		return GetNumericMapCell(self->left, key);
	} else if(comp > 0) {
		if(self->right == NULL) {
			return NULL;
		}
		return GetNumericMapCell(self->right, key);
	}
	return NULL;
}

NumericMapItem GetNumericMapValue(NumericMap* self, NumericMapKey key) {
	NumericMap* cell = GetNumericMapCell(self, key);
	if(cell == NULL) {
		return NULL;
	}
	return cell->item;
}

int CompareNumericMap(NumericMap* self, NumericMapKey key) {
	return (int)self->key - (int)key;
}

void EachNumericMap(NumericMap* self, NumericMapAction a) {
	EachNumericMapImpl(self, a);
}

void DeleteNumericMap(NumericMap* self, NumericMapDeleter deleter) {
	if(self == NULL) {
		return;
	}
	//先に子要素を開放する
	if (self->left != NULL) {
		DeleteNumericMap(self->left, deleter);
		self->left = NULL;
	}
	if (self->right != NULL) {
		DeleteNumericMap(self->right, deleter);
		self->right = NULL;
	}
	if (self->item != NULL) {
		deleter(self->key, self->item);
		//MEM_FREE(self->key);
	}
	MEM_FREE(self);
}

void NumericMapDeleterOfNull(NumericMapKey name, NumericMapItem item) {
}

void NumericMapDeleterByFree(NumericMapKey name, NumericMapItem item) {
	MEM_FREE(item);
}
//private
static void EachNumericMapImpl(NumericMap* self, NumericMapAction a) {
	if (self->left != NULL) {
		EachNumericMapImpl(self->left, a);
	}
	//同じならそれはルート要素
	if (self->key != 0) {
		a(self->key, self->item);
	}
	if (self->right != NULL) {
		EachNumericMapImpl(self->right, a);
	}
}