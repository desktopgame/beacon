#include "enviroment.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../env/TYPE_IMPL.h"
#include "../env/class_loader.h"
#include "../env/fqcn_cache.h"
#include "../env/generic_type.h"
#include "../env/object.h"
#include "../env/type_interface.h"
#include "../lib/bc_library_interface.h"
#include "../util/mem.h"
#include "../util/string_buffer.h"
#include "../util/text.h"
#include "line_range.h"

// proto
static void delete_constant(bc_VectorItem item);
static void delete_line_range(bc_VectorItem item);
static void add_constant(bc_Enviroment* self, bc_Object* o);
static void delete_object_self(bc_VectorItem item);
static void delete_object(bc_Object* obj);

bc_Enviroment* bc_NewEnviroment() {
        bc_Enviroment* ret = (bc_Enviroment*)MEM_MALLOC(sizeof(bc_Enviroment));
        ret->Bytecode = bc_NewOpcodeBuf();
        ret->ConstantPool = bc_NewVector();
        ret->Symboles = bc_NewSymbolTable();
        ret->ContextRef = NULL;
        ret->LineRangeTable = bc_NewVector();
        return ret;
}

void bc_AddRangeEnviroment(bc_Enviroment* self, int lineno) {
        assert(lineno >= 0);
        //空なので追加
        if (bc_IsEmptyVector(self->LineRangeTable)) {
                bc_LineRange* lr = bc_NewLineRange();
                lr->StartOffset = 0;
                lr->EndOffset = 0;
                lr->Lineno = lineno;
                bc_PushVector(self->LineRangeTable, lr);
                return;
        }
        //空ではないなら、
        //最後についかしたレンジを伸ばすか新たに追加する
        bc_LineRange* lrt = (bc_LineRange*)bc_TopVector(self->LineRangeTable);
        if (lrt->Lineno == lineno) {
                lrt->EndOffset = self->Bytecode->Instructions->Length;
        } else {
                bc_LineRange* lr = bc_NewLineRange();
                lr->StartOffset = self->Bytecode->Instructions->Length;
                lr->EndOffset = self->Bytecode->Instructions->Length;
                lr->Lineno = lineno;
                bc_PushVector(self->LineRangeTable, lr);
        }
}

void bc_DumpEnviromentOp(bc_Enviroment* self, int depth) {
        bc_OpcodeBuf* buf = self->Bytecode;
        bc_LineRange* lr = NULL;
        int lrPos = -1;
        for (int i = 0; i < buf->Instructions->Length; i++) {
                bc_Printi(depth);
                i = bc_PrintOpcode(buf->Instructions, i);
                if (!bc_IsEmptyVector(self->LineRangeTable)) {
                        if (lr == NULL) {
                                lr = bc_AtVector(self->LineRangeTable, 0);
                                lrPos = 0;
                        } else {
                                if (i > lr->EndOffset) {
                                        lrPos++;
                                        if (lrPos <
                                            self->LineRangeTable->Length) {
                                                lr = bc_AtVector(
                                                    self->LineRangeTable,
                                                    lrPos);
                                        }
                                }
                        }
                }
                if (lr != NULL) {
                        printf("<%d>", lr->Lineno);
                }
                bc_Println();
        }
        bc_Println();
}

int bc_AddCIntEnviroment(bc_Enviroment* self, int i) {
        int len = self->ConstantPool->Length;
        add_constant(self, (bc_Object*)bc_NewInteger(i));
        return len;
}

int bc_AddCDoubleEnviroment(bc_Enviroment* self, double d) {
        int len = self->ConstantPool->Length;
        add_constant(self, (bc_Object*)bc_NewDouble(d));
        return len;
}

int bc_AddCCharEnviroment(bc_Enviroment* self, char c) {
        int len = self->ConstantPool->Length;
        add_constant(self, (bc_Object*)bc_NewChar(c));
        return len;
}

int bc_AddCStringEnviroment(bc_Enviroment* self, bc_StringView sv) {
        int len = self->ConstantPool->Length;
        add_constant(self, (bc_Object*)bc_NewString(bc_Ref2Str(sv)));
        return len;
}

bc_VectorItem bc_GetEnviromentSourceAt(bc_Enviroment* self, int index) {
        return bc_AtVector(self->Bytecode->Instructions, index);
}

bc_Object* bc_GetEnviromentConstantAt(bc_Enviroment* self, int index) {
        return (bc_Object*)bc_AtVector(self->ConstantPool, index);
}

bc_Object* bc_GetEnviromentCIntAt(bc_Enviroment* self, int index) {
        bc_Object* e = bc_GetEnviromentConstantAt(self, index);
        assert(bc_IsIntValue(e));
        return e;
}

bc_Object* bc_GetEnviromentCDoubleAt(bc_Enviroment* self, int index) {
        bc_Object* e = bc_GetEnviromentConstantAt(self, index);
        assert(bc_IsDoubleValue(e));
        return e;
}

bc_Object* bc_GetEnviromentCCharAt(bc_Enviroment* self, int index) {
        bc_Object* e = bc_GetEnviromentConstantAt(self, index);
        assert(bc_IsCharValue(e));
        return e;
}

bc_Object* bc_GetEnviromentCStringAt(bc_Enviroment* self, int index) {
        bc_Object* e = bc_GetEnviromentConstantAt(self, index);
        assert(bc_IsStringValue(e));
        return e;
}

void bc_DeleteEnviroment(bc_Enviroment* self) {
        if (self == NULL) {
                return;
        }
        bc_DeleteVector(self->ConstantPool, delete_constant);
        bc_DeleteVector(self->LineRangeTable, delete_line_range);
        bc_DeleteOpcodeBuf(self->Bytecode);
        bc_DeleteSymbolTable(self->Symboles);
        MEM_FREE(self);
}

// private
static void delete_constant(bc_VectorItem item) {
        delete_object((bc_Object*)item);
}

static void delete_line_range(bc_VectorItem item) {
        bc_LineRange* e = (bc_LineRange*)item;
        bc_DeleteLineRange(e);
}

static void add_constant(bc_Enviroment* self, bc_Object* o) {
        bc_PushVector(self->ConstantPool, o);
        assert(o->Paint == PAINT_ONEXIT_T);
}

static void delete_object_self(bc_VectorItem item) {}

static void delete_object(bc_Object* obj) { bc_DestroyObject(obj); }
