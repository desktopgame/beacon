#include "stack.h"
#include <assert.h>
#include <stdlib.h>
#include "../util/mem.h"

bc_Stack* bc_NewStack() {
        bc_Stack* ret = (bc_Stack*)MEM_MALLOC(sizeof(bc_Stack));
        ret->Item = NULL;
        ret->Prev = NULL;
        ret->Next = NULL;
        return ret;
}

void bc_PushStack(bc_Stack* self, bc_StackItem item) {
        assert(self != NULL);
        assert(item != NULL);
        if (self->Item == NULL) {
                self->Item = item;
                return;
        }
        if (self->Next == NULL) {
                bc_Stack* next_elem = bc_NewStack();
                self->Next = next_elem;
                next_elem->Prev = self;
                next_elem->Item = item;
        } else {
                bc_PushStack(self->Next, item);
        }
}

bc_StackItem bc_TopStack(bc_Stack* self) {
        assert(self != NULL);
        if (self->Next == NULL) {
                return self->Item;
        } else {
                return bc_TopStack(self->Next);
        }
}

bc_StackItem bc_PopStack(bc_Stack* self) {
        assert(self != NULL);
        if (self->Next == NULL) {
                if (self->Prev == NULL) {
                        bc_StackItem ret = self->Item;
                        self->Item = NULL;
                        return ret;
                } else {
                        bc_Stack* prev_elem = self->Prev;
                        prev_elem->Next = NULL;
                        self->Prev = NULL;
                        bc_StackItem ret = self->Item;
                        MEM_FREE(self);
                        return ret;
                }
        } else {
                return bc_PopStack(self->Next);
        }
}

bool bc_IsEmptyStack(bc_Stack* self) {
        assert(self != NULL);
        return (self->Item == NULL);
}

void bc_DeleteStack(bc_Stack* self, bc_StackElementDeleter deleter) {
        assert(self != NULL);
        bc_Stack* pointee = self;
        while (1) {
                bc_Stack* next = pointee->Next;
                pointee->Next = NULL;
                if (next) {
                        next->Prev = NULL;
                }
                bc_StackItem item = pointee->Item;
                pointee->Item = NULL;
                if (item) {
                        deleter(item);
                }
                MEM_FREE(pointee);
                pointee = next;
                if (!next) {
                        break;
                }
        }
}

void bc_StackDeleterByFree(bc_StackItem item) { MEM_FREE(item); }

void bc_StackDeleterOfNull(bc_StackItem item) {}
