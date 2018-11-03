#include "tree_map.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "text.h"
#include "mem.h"
#include <assert.h>

//proto
static void each_impl(TreeMap* self, TreeAction act);

TreeMap * NewTreeMap() {
	TreeMap* ret = (TreeMap*)MEM_MALLOC(sizeof(TreeMap));
	ret->Key = "\0";
	ret->Item = NULL;
	ret->Left = NULL;
	ret->Right = NULL;
	ret->Parent = NULL;
	return ret;
}

TreeMap* PutTreeMap(TreeMap* self, TreeKey key, TreeItem item) {
	assert(strcmp(key, "\0"));
	//リテラルによってキーが指定される場合は、
	//プログラムによって明示的にそれを削除する必要はありませんが、
	//この関数からは引数のキー文字列が、
	//リテラルによって与えられたものなのか
	//動的に確保されたものなのか判別がつかないので、
	//とりあえず複製し、DeleteTreeMapのときに一緒に削除します。
	int comp = CompareTreeMap(self, key);
	if (comp == 0) {
		self->Item = item;
		return self;
	} else if (comp < 0) {
		if (self->Left == NULL) {
			self->Left = NewTreeMap();
			self->Left->Key = Strdup(key);
			self->Left->Parent = self;
		} else {
			return PutTreeMap(self->Left, key, item);
		}
		self->Left->Item = item;
		return self->Left;
	} else if (comp > 0) {
		if (self->Right == NULL) {
			self->Right = NewTreeMap();
			self->Right->Key = Strdup(key);
			self->Right->Parent = self;
		} else {
			return PutTreeMap(self->Right, key, item);
		}
		self->Right->Item = item;
		return self->Right;
	}
}

TreeItem GetTreeMapValue(TreeMap * self, TreeKey key) {
	TreeMap* ret = GetTreeMapCell(self, key);
	if (ret == NULL) {
		return NULL;
	}
	return ret->Item;
}

TreeMap * GetTreeMapCell(TreeMap * self, TreeKey key) {
	if (self == NULL) {
		return NULL;
	}
	int comp = CompareTreeMap(self, key);
	if (comp == 0) {
		return self;
	} else if (comp < 0) {
		//指定のキーが存在しない
		if (self->Left == NULL) {
			return NULL;
		}
		return GetTreeMapCell(self->Left, key);
	} else if (comp > 0) {
		//指定のキーが存在しない
		if (self->Right == NULL) {
			return NULL;
		}
		return GetTreeMapCell(self->Right, key);
	}
	return NULL;
}

int CompareTreeMap(TreeMap * self, TreeKey key) {
	return strcmp(self->Key, key);
}

void EachTreeMap(TreeMap * self, TreeAction act) {
	assert(self != NULL);
	each_impl(self, act);
}

void DeleteTreeMap(TreeMap * self, TreeElementDeleter deleter) {
	if(self == NULL) {
		return;
	}
	//先に子要素を開放する
	if (self->Left != NULL) {
		DeleteTreeMap(self->Left, deleter);
		self->Left = NULL;
	}
	if (self->Right != NULL) {
		DeleteTreeMap(self->Right, deleter);
		self->Right = NULL;
	}
	//printf("delete %s\n", self->Key);
	if (self->Item != NULL) {
		deleter(self->Key, self->Item);
		MEM_FREE(self->Key);
	}
	MEM_FREE(self);
}

void TreeMapDeleterByFree(const char* key, TreeItem item) {
	MEM_FREE(item);
}

void TreeMapDeleterOfNull(const char* key, TreeItem item) {
}

//private
static void each_impl(TreeMap* self, TreeAction act) {
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