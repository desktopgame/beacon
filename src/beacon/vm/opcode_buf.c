#include "opcode_buf.h"
#include <stdlib.h>
#include "../util/mem.h"
#include "../util/text.h"
#include "opcode.h"

// proto
static void delete_label(bc_VectorItem item);
static void copy_buf(bc_OpcodeBuf* src, bc_OpcodeBuf* dst);

bc_OpcodeBuf* bc_NewOpcodeBuf() {
        bc_OpcodeBuf* ret = (bc_OpcodeBuf*)MEM_MALLOC(sizeof(bc_OpcodeBuf));
        ret->LabelTable = bc_NewVector();
        ret->Instructions = bc_NewVector();
        return ret;
}

int bc_AddOpcodeBuf(bc_OpcodeBuf* self, bc_VectorItem item) {
        int len = self->Instructions->Length;
        bc_PushVector(self->Instructions, item);
        return len;
}

bc_Label* bc_AddLabelOpcodeBuf(bc_OpcodeBuf* self, int index) {
        bc_Label* ret = bc_NewLabel(index);
        bc_PushVector(self->LabelTable, ret);
        return ret;
}

int bc_AddNOPOpcodeBuf(bc_OpcodeBuf* self) {
        int len = self->Instructions->Length;
        bc_AddOpcodeBuf(self, OP_NOP);
        return len;
}

void bc_DumpOpcodeBuf(bc_OpcodeBuf* self, int depth) {
        for (int i = 0; i < self->Instructions->Length; i++) {
                bc_Printi(depth);
                i = bc_PrintOpcode(self->Instructions, i);
                bc_Println();
        }
        bc_Println();
}

bc_OpcodeBuf* bc_MergeOpcodeBuf(bc_OpcodeBuf* a, bc_OpcodeBuf* b) {
        bc_OpcodeBuf* ret = bc_NewOpcodeBuf();
        copy_buf(a, ret);
        copy_buf(b, ret);
        return ret;
}

void bc_DeleteOpcodeBuf(bc_OpcodeBuf* self) {
        if (self == NULL) {
                return;
        }
        bc_DeleteVector(self->Instructions, bc_VectorDeleterOfNull);
        bc_DeleteVector(self->LabelTable, delete_label);
        MEM_FREE(self);
}

// private
static void delete_label(bc_VectorItem item) {
        bc_Label* l = (bc_Label*)item;
        bc_DeleteLabel(l);
}

static void copy_buf(bc_OpcodeBuf* src, bc_OpcodeBuf* dst) {
        for (int i = 0; i < src->Instructions->Length; i++) {
                bc_VectorItem e = bc_AtVector(src->Instructions, i);
                if (e == OP_GOTO || e == OP_GOTO_IF_FALSE ||
                    e == OP_GOTO_IF_TRUE) {
                        bc_AddOpcodeBuf(dst, e);
                        bc_Label* lb =
                            (bc_Label*)bc_AtVector(src->Instructions, ++i);
                        bc_AddOpcodeBuf(dst, e);
                        bc_PushVector(dst->LabelTable, lb);
                } else {
                        bc_AddOpcodeBuf(dst, e);
                }
        }
}
