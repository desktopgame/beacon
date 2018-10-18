#include "enviroment.h"
#include "../env/class_loader.h"
#include "../env/type_interface.h"
#include "../env/TYPE_IMPL.h"
#include "../env/object.h"
#include "../env/fqcn_cache.h"
#include "../lib/beacon/lang/bc_array.h"
#include "line_range.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "../util/mem.h"
#include "../util/string_buffer.h"
#include "../util/text.h"
#include "../env/generic_type.h"

//proto
static void Enviroment_constant_pool_vec_delete(VectorItem item);
static void Enviroment_DeleteLineRange(VectorItem item);
static void Enviroment_add_constant(Enviroment* self, object* o);
static void Enviroment_DeleteObject_self(VectorItem item);
static void Enviroment_DeleteObject(object* obj);

Enviroment * NewEnviroment() {
	Enviroment* ret = (Enviroment*)MEM_MALLOC(sizeof(Enviroment));
	ret->Bytecode = NewOpcodeBuf();
	ret->ConstantPool = NewVector();
	ret->Symboles = NewSymbolTable();
	ret->ContextRef = NULL;
	ret->LineRangeTable = NewVector();
	return ret;
}

void AddRangeEnviroment(Enviroment* self, int lineno) {
	assert(lineno >= 0);
	//空なので追加
	if (IsEmptyVector(self->LineRangeTable)) {
		LineRange* lr = NewLineRange();
		lr->StartOffset = 0;
		lr->EndOffset = 0;
		lr->Lineno = lineno;
		PushVector(self->LineRangeTable, lr);
		return;
	}
	//空ではないなら、
	//最後についかしたレンジを伸ばすか新たに追加する
	LineRange* lrt = (LineRange*)TopVector(self->LineRangeTable);
	if (lrt->Lineno == lineno) {
		lrt->EndOffset = self->Bytecode->source_vec->Length;
	} else {
		LineRange* lr = NewLineRange();
		lr->StartOffset = self->Bytecode->source_vec->Length;
		lr->EndOffset = self->Bytecode->source_vec->Length;
		lr->Lineno = lineno;
		PushVector(self->LineRangeTable, lr);
	}
}

void DumpEnviromentOp(Enviroment * self, int depth) {
	opcode_buf* buf = self->Bytecode;
	LineRange* lr = NULL;
	int lrPos = -1;
	for (int i = 0; i < buf->source_vec->Length; i++) {
		Printi(depth);
		i = PrintOpcode(buf->source_vec, i);
		if (!IsEmptyVector(self->LineRangeTable)) {
			if (lr == NULL) {
				lr = AtVector(self->LineRangeTable, 0);
				lrPos = 0;
			} else {
				if (i > lr->EndOffset) {
					lrPos++;
					if (lrPos < self->LineRangeTable->Length) {
						lr = AtVector(self->LineRangeTable, lrPos);
					}
				}
			}
		}
		if (lr != NULL) {
			printf("<%d>", lr->Lineno);
		}
		Println();
	}
	Println();
}

int AddCIntEnviroment(Enviroment * self, int i) {
	int len = self->ConstantPool->Length;
	Enviroment_add_constant(self, object_int_new(i));
	return len;
}

int AddCDoubleEnviroment(Enviroment * self, double d) {
	int len = self->ConstantPool->Length;
	Enviroment_add_constant(self, object_double_new(d));
	return len;
}

int AddCCharEnviroment(Enviroment * self, char c) {
	int len = self->ConstantPool->Length;
	Enviroment_add_constant(self, object_char_new(c));
	return len;
}

int AddCStringEnviroment(Enviroment * self, StringView sv) {
	int len = self->ConstantPool->Length;
	Enviroment_add_constant(self, object_string_new(Ref2Str(sv)));
	return len;
}

VectorItem GetEnviromentSourceAt(Enviroment * self, int index) {
	return AtVector(self->Bytecode->source_vec, index);
}

object* GetEnviromentConstantAt(Enviroment * self, int index) {
	return (object*)AtVector(self->ConstantPool, index);
}

object* GetEnviromentCIntAt(Enviroment * self, int index) {
	object* e = GetEnviromentConstantAt(self, index);
	assert(e->tag == OBJECT_INT_T);
	return e;
}

object* GetEnviromentCDoubleAt(Enviroment * self, int index) {
	object* e = GetEnviromentConstantAt(self, index);
	assert(e->tag == OBJECT_DOUBLE_T);
	return e;
}

object* GetEnviromentCCharAt(Enviroment * self, int index) {
	object* e = GetEnviromentConstantAt(self, index);
	assert(e->tag == OBJECT_CHAR_T);
	return e;
}

object* GetEnviromentCStringAt(Enviroment * self, int index) {
	object* e = GetEnviromentConstantAt(self, index);
	assert(e->tag == OBJECT_STRING_T);
	return e;
}

void DeleteEnviroment(Enviroment * self) {
	if(self == NULL) {
		return;
	}
	DeleteVector(self->ConstantPool, Enviroment_constant_pool_vec_delete);
	DeleteVector(self->LineRangeTable, Enviroment_DeleteLineRange);
	DeleteOpcodeBuf(self->Bytecode);
	DeleteSymbolTable(self->Symboles);
	MEM_FREE(self);
}

//private
static void Enviroment_constant_pool_vec_delete(VectorItem item) {
	Enviroment_DeleteObject((object*)item);
}

static void Enviroment_DeleteLineRange(VectorItem item) {
	LineRange* e = (LineRange*)item;
	DeleteLineRange(e);
}

static void Enviroment_add_constant(Enviroment* self, object* o) {
	PushVector(self->ConstantPool, o);
	assert(o->paint == PAINT_ONEXIT_T);
}

static void Enviroment_DeleteObject_self(VectorItem item) {
}

static void Enviroment_DeleteObject(object* obj) {
	DestroyObject(obj);
}
