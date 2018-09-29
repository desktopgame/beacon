#include "tree_map.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "text.h"
#include "mem.h"
#include <assert.h>

//proto
static void EachTreeMapImpl(tree_map* self, tree_action act);

tree_map * NewTreeMap() {
	tree_map* ret = (tree_map*)MEM_MALLOC(sizeof(tree_map));
	ret->key = "\0";
	ret->item = NULL;
	ret->left = NULL;
	ret->right = NULL;
	ret->parent = NULL;
	return ret;
}

tree_map* PutTreeMap(tree_map* self, tree_key key, tree_item item) {
	assert(strcmp(key, "\0"));
	//リテラルによってキーが指定される場合は、
	//プログラムによって明示的にそれを削除する必要はありませんが、
	//この関数からは引数のキー文字列が、
	//リテラルによって与えられたものなのか
	//動的に確保されたものなのか判別がつかないので、
	//とりあえず複製し、DeleteTreeMapのときに一緒に削除します。
	int comp = CompareTreeMap(self, key);
	if (comp == 0) {
		self->item = item;
		return self;
	} else if (comp < 0) {
		if (self->left == NULL) {
			self->left = NewTreeMap();
			self->left->key = Strdup(key);
			self->left->parent = self;
		} else {
			return PutTreeMap(self->left, key, item);
		}
		self->left->item = item;
		return self->left;
	} else if (comp > 0) {
		if (self->right == NULL) {
			self->right = NewTreeMap();
			self->right->key = Strdup(key);
			self->right->parent = self;
		} else {
			return PutTreeMap(self->right, key, item);
		}
		self->right->item = item;
		return self->right;
	}
}

tree_item GetTreeMapValue(tree_map * self, tree_key key) {
	tree_map* ret = GetTreeMapCell(self, key);
	if (ret == NULL) {
		return NULL;
	}
	return ret->item;
}

tree_map * GetTreeMapCell(tree_map * self, tree_key key) {
	if (self == NULL) {
		return NULL;
	}
	int comp = CompareTreeMap(self, key);
	if (comp == 0) {
		return self;
	} else if (comp < 0) {
		//指定のキーが存在しない
		if (self->left == NULL) {
			return NULL;
		}
		return GetTreeMapCell(self->left, key);
	} else if (comp > 0) {
		//指定のキーが存在しない
		if (self->right == NULL) {
			return NULL;
		}
		return GetTreeMapCell(self->right, key);
	}
	return NULL;
}

int CompareTreeMap(tree_map * self, tree_key key) {
	return strcmp(self->key, key);
}

void EachTreeMap(tree_map * self, tree_action act) {
	assert(self != NULL);
	EachTreeMapImpl(self, act);
}

void DeleteTreeMap(tree_map * self, tree_element_deleter deleter) {
	if(self == NULL) {
		return;
	}
	//先に子要素を開放する
	if (self->left != NULL) {
		DeleteTreeMap(self->left, deleter);
		self->left = NULL;
	}
	if (self->right != NULL) {
		DeleteTreeMap(self->right, deleter);
		self->right = NULL;
	}
	//printf("delete %s\n", self->key);
	if (self->item != NULL) {
		deleter(self->key, self->item);
		MEM_FREE(self->key);
	}
	MEM_FREE(self);
}

void DeleteTreeMapr_free(const char* key, tree_item item) {
	MEM_FREE(item);
}

void DeleteTreeMapr_null(const char* key, tree_item item) {
}

//private
static void EachTreeMapImpl(tree_map* self, tree_action act) {
	if (self->left != NULL) {
		EachTreeMapImpl(self->left, act);
	}
	//同じならそれはルート要素
	if (strcmp(self->key, "\0")) {
		act(self->key, self->item);
	}

	if (self->right != NULL) {
		EachTreeMapImpl(self->right, act);
	}
}