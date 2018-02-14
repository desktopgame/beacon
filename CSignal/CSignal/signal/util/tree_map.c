#include "tree_map.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "text.h"
#include "mem.h"
#include <assert.h>

//proto
static void tree_map_eachImpl(tree_map* self, tree_action act);

tree_map * tree_map_new() {
	tree_map* ret = (tree_map*)MEM_MALLOC(sizeof(tree_map));
	ret->key = "\0";
	ret->item = NULL;
	ret->left = NULL;
	ret->right = NULL;
	ret->parent = NULL;
	return ret;
}

tree_map* tree_map_put(tree_map* self, tree_key key, tree_item item) {
	assert(strcmp(key, "\0"));
	//リテラルによってキーが指定される場合は、
	//プログラムによって明示的にそれを削除する必要はありませんが、
	//この関数からは引数のキー文字列が、
	//リテラルによって与えられたものなのか
	//動的に確保されたものなのか判別がつかないので、
	//とりあえず複製し、tree_map_deleteのときに一緒に削除します。
	int comp = tree_map_compare(self, key);
	if (comp == 0) {
		self->item = item;
		return self;
	} else if (comp < 0) {
		if (self->left == NULL) {
			self->left = tree_map_new();
			self->left->key = text_strdup(key);
			self->left->parent = self;
		} else {
			return tree_map_put(self->left, key, item);
		}
		self->left->item = item;
		return self->left;
	} else if (comp > 0) {
		if (self->right == NULL) {
			self->right = tree_map_new();
			self->right->key = text_strdup(key);
			self->right->parent = self;
		} else {
			return tree_map_put(self->right, key, item);
		}
		self->right->item = item;
		return self->right;
	}
}

tree_item tree_map_get(tree_map * self, tree_key key) {
	tree_map* ret = tree_map_cell(self, key);
	if (ret == NULL) {
		return NULL;
	}
	return ret->item;
}

tree_map * tree_map_cell(tree_map * self, tree_key key) {
	if (self == NULL) {
		return NULL;
	}
	int comp = tree_map_compare(self, key);
	if (comp == 0) {
		return self;
	} else if (comp < 0) {
		//指定のキーが存在しない
		if (self->left == NULL) {
			return NULL;
		}
		return tree_map_cell(self->left, key);
	} else if (comp > 0) {
		//指定のキーが存在しない
		if (self->right == NULL) {
			return NULL;
		}
		return tree_map_cell(self->right, key);
	}
	return NULL;
}

int tree_map_compare(tree_map * self, tree_key key) {
	return strcmp(self->key, key);
}

void tree_map_each(tree_map * self, tree_action act) {
	tree_map_eachImpl(self, act);
}

void tree_map_delete(tree_map * self, tree_element_deleter deleter) {
	//先に子要素を開放する
	if (self->left != NULL) {
		tree_map_delete(self->left, deleter);
		self->left = NULL;
	}
	if (self->right != NULL) {
		tree_map_delete(self->right, deleter);
		self->right = NULL;
	}
	//text_printf("delete %s\n", self->key);
	if (self->item != NULL) {
		deleter(self->item);
		MEM_FREE(self->key);
	}
	MEM_FREE(self);
}

void tree_map_deleter_free(tree_item item) {
	MEM_FREE(item);
}

void tree_map_deleter_null(tree_item item) {
}

//private
static void tree_map_eachImpl(tree_map* self, tree_action act) {
	if (self->left != NULL) {
		tree_map_eachImpl(self->left, act);
	}
	//同じならそれはルート要素
	if (strcmp(self->key, "\0")) {
		act(self->key, self->item);
	}

	if (self->right != NULL) {
		tree_map_eachImpl(self->right, act);
	}
}