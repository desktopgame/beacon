#include "tree_map.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "text.h"
#include "mem.h"
#include <assert.h>

//proto
static void each_impl(bc_TreeMap* self, bc_TreeAction act);

bc_TreeMap * bc_NewTreeMap() {
	bc_TreeMap* ret = (bc_TreeMap*)MEM_MALLOC(sizeof(bc_TreeMap));
	ret->Key = "\0";
	ret->Item = NULL;
	ret->Left = NULL;
	ret->Right = NULL;
	ret->Parent = NULL;
	return ret;
}

bc_TreeMap* bc_PutTreeMap(bc_TreeMap* self, bc_TreeKey key, bc_TreeItem item) {
	assert(strcmp(key, "\0"));
	//リテラルによってキーが指定される場合は、
	//プログラムによって明示的にそれを削除する必要はありませんが、
	//この関数からは引数のキー文字列が、
	//リテラルによって与えられたものなのか
	//動的に確保されたものなのか判別がつかないので、
	//とりあえず複製し、DeleteTreeMapのときに一緒に削除します。
	int comp = bc_CompareTreeMap(self, key);
	if (comp == 0) {
		self->Item = item;
		return self;
	} else if (comp < 0) {
		if (self->Left == NULL) {
			self->Left = bc_NewTreeMap();
			self->Left->Key = bc_Strdup(key);
			self->Left->Parent = self;
		} else {
			return bc_PutTreeMap(self->Left, key, item);
		}
		self->Left->Item = item;
		return self->Left;
	} else if (comp > 0) {
		if (self->Right == NULL) {
			self->Right = bc_NewTreeMap();
			self->Right->Key = bc_Strdup(key);
			self->Right->Parent = self;
		} else {
			return bc_PutTreeMap(self->Right, key, item);
		}
		self->Right->Item = item;
		return self->Right;
	}
}

bc_TreeItem bc_GetTreeMapValue(bc_TreeMap * self, bc_TreeKey key) {
	bc_TreeMap* ret = bc_GetTreeMapCell(self, key);
	if (ret == NULL) {
		return NULL;
	}
	return ret->Item;
}

bc_TreeMap * bc_GetTreeMapCell(bc_TreeMap * self, bc_TreeKey key) {
	if (self == NULL) {
		return NULL;
	}
	int comp = bc_CompareTreeMap(self, key);
	if (comp == 0) {
		return self;
	} else if (comp < 0) {
		//指定のキーが存在しない
		if (self->Left == NULL) {
			return NULL;
		}
		return bc_GetTreeMapCell(self->Left, key);
	} else if (comp > 0) {
		//指定のキーが存在しない
		if (self->Right == NULL) {
			return NULL;
		}
		return bc_GetTreeMapCell(self->Right, key);
	}
	return NULL;
}

int bc_CompareTreeMap(bc_TreeMap * self, bc_TreeKey key) {
	return strcmp(self->Key, key);
}

void bc_EachTreeMap(bc_TreeMap * self, bc_TreeAction act) {
	assert(self != NULL);
	each_impl(self, act);
}

void bc_DeleteTreeMap(bc_TreeMap * self, bc_TreeElementDeleter deleter) {
	if(self == NULL) {
		return;
	}
	//先に子要素を開放する
	if (self->Left != NULL) {
		bc_DeleteTreeMap(self->Left, deleter);
		self->Left = NULL;
	}
	if (self->Right != NULL) {
		bc_DeleteTreeMap(self->Right, deleter);
		self->Right = NULL;
	}
	//printf("delete %s\n", self->Key);
	if (self->Item != NULL) {
		deleter(self->Key, self->Item);
		MEM_FREE(self->Key);
	}
	MEM_FREE(self);
}

void bc_TreeMapDeleterByFree(const char* key, bc_TreeItem item) {
	MEM_FREE(item);
}

void bc_TreeMapDeleterOfNull(const char* key, bc_TreeItem item) {
}

//private
static void each_impl(bc_TreeMap* self, bc_TreeAction act) {
	if (self->Left != NULL) {
		each_impl(self->Left, act);
	}
	//同じならそれはルート要素
	if (strcmp(self->Key, "\0")) {
		act(self->Key, self->Item);
	}

	if (self->Right != NULL) {
		each_impl(self->Right, act);
	}
}