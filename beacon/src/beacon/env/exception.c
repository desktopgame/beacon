#include "exception.h"
#include <assert.h>
#include "../lib/bc_library_interface.h"
#include "../util/text.h"
#include "../vm/frame.h"
#include "TYPE_IMPL.h"
#include "namespace.h"
#include "object.h"
#if defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif

// proto
static bc_Class* exception_class();

bc_Object* bc_NewSimpleException(bc_Frame* fr, const char* message) {
        bc_Class* excClass = exception_class();
        bc_Vector* args = bc_NewVector();
        bc_PushVector(args, bc_NewString(message));
        bc_Object* e = bc_NewInstanceClass(excClass, fr, args, NULL);
        bc_DeleteVector(args, bc_VectorDeleterOfNull);
        return e;
}

bc_Object* bc_NewSimplefException(bc_Frame* fr, const char* message, ...) {
        va_list ap;
        va_start(ap, message);
#define LEN 256
        char block[LEN];
        int res = vsprintf(block, message, ap);
        assert(res != -1);
#undef LEN
        va_end(ap);
        return bc_NewSimpleException(fr, block);
}

// private
static bc_Class* exception_class() {
        bc_Namespace* lang = bc_GetLangNamespace(NULL);
        bc_Class* excClass =
            bc_FindClassFromNamespace(lang, bc_InternString("Exception"));
        assert(excClass != NULL);
        return excClass;
}