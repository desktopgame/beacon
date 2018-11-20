#include "numeric_map.h"
#include "mem.h"

static void each_impl(bc_NumericMap* self, bc_NumericMapAction a);

bc_NumericMap* bc_NewNumericMap() {
	bc_NumericMap* ret = (bc_NumericMap*)MEM_MALLOC(sizeof(bc_NumericMap));
	ret->Key = 0;
	ret->Item = NULL;
	ret->Parent = NULL;
	ret->Left = NULL;
	ret->Right = NULL;
	return ret;
}

bc_NumericMap* bc_PutNumericMap(bc_NumericMap* self, bc_NumericMapKey key, bc_NumericMapItem item) {
	int comp = bc_CompareNumericMap(self, key);
	if(comp == 0) {
		self->Item = item;
		return self;
	} else if(comp < 0) {
		if(self->Left == NULL) {
			bc_NumericMap* nl = bc_NewNumericMap();
			self->Left = nl;
			nl->Parent = self;
			nl->Key = key;
			nl->Item = item;
			return nl;
		} else {
			return bc_PutNumericMap(self->Left, key, item);
		}
	} else if(comp > 0) {
		if(self->Right == NULL) {
			bc_NumericMap* nr = bc_NewNumericMap();
			self->Right = nr;
			nr->Parent = self;
			nr->Key = key;
			nr->Item = item;
			return nr;
		} else {
			return bc_PutNumericMap(self->Right, key, item);
		}
	}
	return NULL;
}

bc_NumericMap* bc_GetNumericMapCell(bc_NumericMap* self, bc_NumericMapKey key) {
	int comp = bc_CompareNumericMap(self, key);
	if(comp == 0) {
		return self;
	} else if(comp < 0) {
		if(self->Left == NULL) {
			return NULL;
		}
		return bc_GetNumericMapCell(self->Left, key);
	} else if(comp > 0) {
		if(self->Right == NULL) {
			return NULL;
		}
		return bc_GetNumericMapCell(self->Right, key);
	}
	return NULL;
}

bc_NumericMapItem bc_GetNumericMapValue(bc_NumericMap* self, bc_NumericMapKey key) {
	bc_NumericMap* cell = bc_GetNumericMapCell(self, key);
	if(cell == NULL) {
		return NULL;
	}
	return cell->Item;
}

int bc_CompareNumericMap(bc_NumericMap* self, bc_NumericMapKey key) {
	return (int)self->Key - (int)key;
}

void bc_EachNumericMap(bc_NumericMap* self, bc_NumericMapAction a) {
	each_impl(self, a);
}

void bc_DeleteNumericMap(bc_NumericMap* self, bc_NumericMapDeleter deleter) {
	if(self == NULL) {
		return;
	}
	//先に子要素を開放する
	if (self->Left != NULL) {
		bc_DeleteNumericMap(self->Left, deleter);
		self->Left = NULL;
	}
	if (self->Right != NULL) {
		bc_DeleteNumericMap(self->Right, deleter);
		self->Right = NULL;
	}
	if (self->Item != NULL) {
		deleter(self->Key, self->Item);
		//MEM_FREE(self->Key);
	}
	MEM_FREE(self);
}

void bc_NumericMapDeleterOfNull(bc_NumericMapKey name, bc_NumericMapItem item) {
}

void bc_NumericMapDeleterByFree(bc_NumericMapKey name, bc_NumericMapItem item) {
	MEM_FREE(item);
}
//private
static void each_impl(bc_NumericMap* self, bc_NumericMapAction a) {
	if (self->Left != NULL) {
		each_impl(self->Left, a);
	}
	//同じならそれはルート要素
	if (self->Key != 0) {
		a(self->Key, self->Item);
	}
	if (self->Right != NULL) {
		each_impl(self->Right, a);
	}
}