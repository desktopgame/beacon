#include "numeric_map.h"
#include "mem.h"

static void EachNumericMapImpl(NumericMap* self, NumericMapAction a);

NumericMap* NewNumericMap() {
	NumericMap* ret = (NumericMap*)MEM_MALLOC(sizeof(NumericMap));
	ret->Key = 0;
	ret->Item = NULL;
	ret->Parent = NULL;
	ret->Left = NULL;
	ret->Right = NULL;
	return ret;
}

NumericMap* PutNumericMap(NumericMap* self, NumericMapKey key, NumericMapItem item) {
	int comp = CompareNumericMap(self, key);
	if(comp == 0) {
		self->Item = item;
		return self;
	} else if(comp < 0) {
		if(self->Left == NULL) {
			NumericMap* nl = NewNumericMap();
			self->Left = nl;
			nl->Parent = self;
			nl->Key = key;
			nl->Item = item;
			return nl;
		} else {
			return PutNumericMap(self->Left, key, item);
		}
	} else if(comp > 0) {
		if(self->Right == NULL) {
			NumericMap* nr = NewNumericMap();
			self->Right = nr;
			nr->Parent = self;
			nr->Key = key;
			nr->Item = item;
			return nr;
		} else {
			return PutNumericMap(self->Right, key, item);
		}
	}
	return NULL;
}

NumericMap* GetNumericMapCell(NumericMap* self, NumericMapKey key) {
	int comp = CompareNumericMap(self, key);
	if(comp == 0) {
		return self;
	} else if(comp < 0) {
		if(self->Left == NULL) {
			return NULL;
		}
		return GetNumericMapCell(self->Left, key);
	} else if(comp > 0) {
		if(self->Right == NULL) {
			return NULL;
		}
		return GetNumericMapCell(self->Right, key);
	}
	return NULL;
}

NumericMapItem GetNumericMapValue(NumericMap* self, NumericMapKey key) {
	NumericMap* cell = GetNumericMapCell(self, key);
	if(cell == NULL) {
		return NULL;
	}
	return cell->Item;
}

int CompareNumericMap(NumericMap* self, NumericMapKey key) {
	return (int)self->Key - (int)key;
}

void EachNumericMap(NumericMap* self, NumericMapAction a) {
	EachNumericMapImpl(self, a);
}

void DeleteNumericMap(NumericMap* self, NumericMapDeleter deleter) {
	if(self == NULL) {
		return;
	}
	//先に子要素を開放する
	if (self->Left != NULL) {
		DeleteNumericMap(self->Left, deleter);
		self->Left = NULL;
	}
	if (self->Right != NULL) {
		DeleteNumericMap(self->Right, deleter);
		self->Right = NULL;
	}
	if (self->Item != NULL) {
		deleter(self->Key, self->Item);
		//MEM_FREE(self->Key);
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
	if (self->Left != NULL) {
		EachNumericMapImpl(self->Left, a);
	}
	//同じならそれはルート要素
	if (self->Key != 0) {
		a(self->Key, self->Item);
	}
	if (self->Right != NULL) {
		EachNumericMapImpl(self->Right, a);
	}
}