#include "label.h"
#include <stdlib.h>
#include "../util/mem.h"

bc_Label* bc_NewLabel(int cursor) {
        bc_Label* ret = (bc_Label*)MEM_MALLOC(sizeof(bc_Label));
        ret->Cursor = cursor;
        return ret;
}

void bc_DeleteLabel(bc_Label* self) { MEM_FREE(self); }
