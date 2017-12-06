#include "tree_map.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

tree_map * tree_map_new() {
	tree_map* ret = (tree_map*)malloc(sizeof(tree_map));
	ret->key = "\0";
	ret->item = NULL;
	ret->left = NULL;
	ret->right = NULL;
	return ret;
}

void tree_map_put(tree_map* self, tree_key key, tree_item item) {
	//リテラルによってキーが指定される場合は、
	//プログラムによって明示的にそれを削除する必要はありませんが、
	//この関数からは引数のキー文字列が、
	//リテラルによって与えられたものなのか
	//動的に確保されたものなのか判別がつかないので、
	//とりあえず複製し、tree_map_deleteのときに一緒に削除します。
	int comp = tree_map_compare(self, key);
	if (comp == 0) {
		self->item = item;
	} else if (comp < 0) {
		if (self->left == NULL) {
			self->left = tree_map_new();
			self->left->key = _strdup(key);
		} else {
			tree_map_put(self->left, key, item);
			return;
		}
		self->left->item = item;
	} else if (comp > 0) {
		if (self->right == NULL) {
			self->right = tree_map_new();
			self->right->key = _strdup(key);
		} else {
			tree_map_put(self->right, key, item);
			return;
		}
		self->right->item = item;
	}
}

tree_item tree_map_get(tree_map * self, tree_key key) {
	int comp = tree_map_compare(self, key);
	if (comp == 0) {
		return self->item;
	} else if (comp < 0) {
		//指定のキーが存在しない
		if (self->left == NULL) {
			return NULL;
		}
		return tree_map_get(self->left, key);
	} else if (comp > 0) {
		//指定のキーが存在しない
		if (self->right == NULL) {
			return NULL;
		}
		return tree_map_get(self->right, key);
	}
	return NULL;
}

int tree_map_compare(tree_map * self, tree_key key) {
	return strcmp(self->key, key);
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
	//printf("delete %s\n", self->key);
	if (self->item != NULL) {
		deleter(self->item);
		free(self->key);
	}
	free(self);
}

void tree_map_deleter_free(tree_item item) {
	free(item);
}

void tree_map_deleter_null(tree_item item) {
}
