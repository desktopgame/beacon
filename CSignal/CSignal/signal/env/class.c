#include "class.h"
#include "../util/text.h"
#include "parameter.h"
#include "../il/il_argument.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../util/mem.h"
#include "../vm/enviroment.h"
#include "../util/text.h"
#include "field.h"
#include "method.h"

//http://jumble-note.blogspot.jp/2012/09/c-vacopy.html
#ifndef va_copy
#    define va_copy(dest, src) ((dest) = (src))
#endif

//private
static void class_field_delete(vector_item item);
static void class_method_delete(vector_item item);

class_ * class_new(const char * name, class_type type) {
	assert(name != NULL);
	class_* ret = (class_*)MEM_MALLOC(sizeof(class_));
	ret->name = text_strdup(name);
	ret->type = type;
	ret->location = NULL;
	ret->state = class_none;
	ret->ref_count = 0;
	ret->super_class = NULL;
	ret->field_list = vector_new();
	ret->method_list = vector_new();
	return ret;
}

void class_dump(class_ * self, int depth) {
	text_putindent(depth);
	printf("class %s", self->name);
	text_putline();
	//フィールドの一覧をダンプ
	for (int i = 0; i < self->field_list->length; i++) {
		vector_item e = vector_at(self->field_list, i);
		field* f = (field*)e;
		field_dump(f, depth + 1);
	}
	//メソッドの一覧をダンプ
	for (int i = 0; i < self->method_list->length; i++) {
		vector_item e = vector_at(self->method_list, i);
		method* m = (method*)e;
		method_dump(m, depth + 1);
	}
}

field * class_find_field(class_* self, const char * name) {
	for (int i = 0; i < self->field_list->length; i++) {
		vector_item e = vector_at(self->field_list, i);
		field* f = (field*)e;
		if (!strcmp(name, f->name)) {
			return f;
		}
	}
	return NULL;
}

vector * class_find_method(class_* self, const char * name, int count, ...) {
	vector* v = vector_new();
	va_list args;
	va_start(args, count);

	for (int i = 0; i < self->method_list->length; i++) {
		vector_item e = vector_at(self->method_list, i);
		method* m = (method*)e;
		//名前か引数の個数が違うので無視
		if (strcmp(m->name, name) || 
			count != m->parameter_list->length) {
			continue;
		}
		//引数がひとつもないので、
		//型のチェックを行わない
		if (count == 0) {
			vector_push(v, m);
			continue;
		}
		bool match = true;
		va_list buf;
		va_copy(buf, args);
		//仮引数の型チェック
		for (int j = 0; j < count; j++) {
			vector_item d = vector_at(m->parameter_list, j);
			parameter* p = (parameter*)d;
			class_* cl = va_arg(buf, class_*);
			//互換のない型なら次へ
			if (!class_castable(cl, p->classz)) {
				match = false;
				break;
			}
		}
		va_end(buf);
		if (match) {
			vector_push(v, m);
		}
	}
	va_end(args);
	return v;
}

vector * class_find_method0(class_ * self, const char * name) {
	return class_find_method(self, name, 0);
}

vector * class_find_method1(class_ * self, const char * name, class_ * type1) {
	return class_find_method(self, name, 1, type1);
}

vector * class_find_methodv(class_ * self, const char * name, vector * args, enviroment* env) {
	vector* v = vector_new();
	if (self == NULL) {
		return v;
	}
	for (int i = 0; i < self->method_list->length; i++) {
		vector_item e = vector_at(self->method_list, i);
		method* m = (method*)e;
		//名前か引数の個数が違うので無視
		if (strcmp(m->name, name) ||
			m->parameter_list->length != args->length
			) {
			continue;
		}
		//引数がひとつもないので、
		//型のチェックを行わない
		if (args->length == 0) {
			vector_push(v, m);
			continue;
		}
		bool match = true;
		for (int j = 0; j < args->length; j++) {
			vector_item d = vector_at(args, j);
			vector_item d2 = vector_at(m->parameter_list, j);
			il_argument* p = (il_argument*)d;
			parameter* p2 = (parameter*)d2;
			if (!class_castable(il_factor_eval(p->factor, env), p2->classz)) {
				match = false;
				break;
			}
		}
		if (match) {
			vector_push(v, m);
		}
	}
	return v;
}

method * class_find_methodvf(class_ * self, const char * name, vector * args, enviroment * env, int * outIndex) {
	vector* v = class_find_methodv(self, name, args, env);
	(*outIndex) = -1;
	//メソッドが一つも見つからなかった
	if (v->length == 0) {
		vector_delete(v, vector_deleter_null);
		return NULL;
	}
	//見つかった中からもっとも一致するメソッドを選択する
	int min = 1024;
	method* ret = NULL;
	for (int i = 0; i < v->length; i++) {
		vector_item e = vector_at(v, i);
		method* m = (method*)e;
		int score = 0;
		for (int j = 0; j < m->parameter_list->length; j++) {
			vector_item d = vector_at(args, j);
			vector_item d2 = vector_at(m->parameter_list, j);
			il_argument* p = (il_argument*)d2;
			parameter* p2 = (parameter*)d;
			score += class_distance(il_factor_eval(p->factor, env), p2->classz);
			if (score < min) {
				min = score;
				ret = m;
				(*outIndex) = i;
			}
		}
	}
	vector_delete(v, vector_deleter_null);
	return ret;
}

int class_method_index_resolve(class_* self, int index) {
	assert(index >= 0);
	if (self->super_class == NULL) {
		return index;
	}
	class_* pointee = self->super_class;
	do {
		index += (pointee->method_list->length);
		pointee = pointee->super_class;
	} while (pointee != NULL);
	return index;
}

method * class_method_by_index(class_* self, int index) {
	if (self->super_class == NULL) {
		vector_item e = vector_at(self->method_list, index);
		return (method*)e;
	}
	class_* pointee = self;
	do {
		int length = pointee->method_list->length;
		int end = class_method_countall(pointee);
		int start = end - length;
		int relative = index - start;
		if (index >= start && index < end) {
			vector_item e = vector_at(pointee->method_list, relative);
			return (method*)e;
		}
		pointee = pointee->super_class;
	} while (pointee != NULL);
	return NULL;
}

int class_method_countall(class_ * self) {
	return class_method_index_resolve(self, self->method_list->length);
}

int class_field_index_resolve(class_ * self, int index) {
	assert(index >= 0);
	if (self->super_class == NULL) {
		return index;
	}
	class_* pointee = self->super_class;
	do {
		index += (pointee->field_list->length);
		pointee = pointee->super_class;
	} while (pointee != NULL);
	return index;
}

field * class_field_by_index(class_ * self, int index) {
	if (self->super_class == NULL) {
		vector_item e = vector_at(self->field_list, index);
		return (field*)e;
	}
	class_* pointee = self;
	do {
		int length = pointee->field_list->length;
		int end = class_field_countall(pointee);
		int start = end - length;
		int relative = index - start;
		if (index >= start && index < end) {
			vector_item e = vector_at(pointee->field_list, relative);
			return (field*)e;
		}
		pointee = pointee->super_class;
	} while (pointee != NULL);
	return NULL;
}

int class_field_countall(class_ * self) {
	return class_method_index_resolve(self, self->field_list->length);
}

bool class_castable(class_ * self, class_ * other) {
	assert(self != NULL && other != NULL);
	if (self == other) {
		return true;
	}
	class_* pointee = self;
	do {
		if (pointee == other) {
			return true;
		}
		pointee = pointee->super_class;
	} while (pointee != NULL);
	return false;
}

int class_distance(class_ * self, class_ * other) {
	if (self == other) {
		return 0;
	}
	int depth = 0;
	class_* pointee = self;
	do {
		if (pointee == other) {
			return depth;
		}
		pointee = pointee->super_class;
		depth++;
		if (pointee == NULL) {
			depth = -1;
			break;
		}
	} while (1);
	return depth;
}

void class_delete(class_ * self) {
	assert(self->ref_count == 0);
	MEM_FREE(self->name);
	if (self->super_class != NULL) {
		self->super_class->ref_count--;
	}
	vector_delete(self->field_list, class_field_delete);
	vector_delete(self->method_list, class_method_delete);
	MEM_FREE(self);
}

//private
static void class_field_delete(vector_item item) {
	field* e = (field*)item;
	field_delete(e);
}

static void class_method_delete(vector_item item) {
	method* e = (method*)item;
	method_delete(e);
}