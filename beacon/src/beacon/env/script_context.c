#include "script_context.h"
#include <assert.h>
#include <stdlib.h>
#include "../lib/bc_library_interface.h"
#include "../util/io.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../vm/script_thread.h"
#include "class_loader.h"
#include "field.h"
#include "generic_type.h"
#include "heap.h"
#include "namespace.h"
#include "type/class_impl.h"
#include "type_interface.h"
// proto
static bc_ScriptContext* malloc_script_context(void);
static void free_script_context(bc_ScriptContext* self);
static void delete_class_loader(const char* name, bc_TreeItem item);

static void unlink_namespace(bc_NumericMapKey key, bc_NumericMapItem item);
static void delete_namespace(bc_NumericMapKey key, bc_NumericMapItem item);
static void clear_impl(bc_Field* item);
static void delete_cache(bc_VectorItem item);
static void delete_mcache(bc_NumericMapKey key, bc_NumericMapItem item);

static bc_Vector* gScriptContextVec = NULL;
static bc_ScriptContext* gScriptContext = NULL;

bc_ScriptContext* bc_OpenScriptContext() {
        if (gScriptContextVec == NULL) {
                gScriptContextVec = bc_NewVector();
        }
        bc_ScriptContext* sctx = malloc_script_context();
        bc_PushVector(gScriptContextVec, sctx);
        bc_BootstrapScriptContext(sctx);
        return sctx;
}

bc_ScriptContext* bc_GetCurrentScriptContext() {
        return bc_SelectedScriptContext(bc_GetCurrentScriptThread());
}

void bc_CloseScriptContext() {
        bc_ScriptContext* sctx =
            (bc_ScriptContext*)bc_PopVector(gScriptContextVec);
        free_script_context(sctx);
        if (gScriptContextVec->Length == 0) {
                bc_DeleteVector(gScriptContextVec, bc_VectorDeleterOfNull);
                gScriptContextVec = NULL;
        }
}

void bc_BootstrapScriptContext(bc_ScriptContext* self) {
        self->Heap->AcceptBlocking++;
        self->IsLoadForBoot = true;
        //プリロード
        bc_Namespace* beacon =
            bc_CreateNamespaceAtRoot(bc_InternString("beacon"));
        bc_Namespace* lang =
            bc_AddNamespaceNamespace(beacon, bc_InternString("lang"));
        bc_Namespace* unsafe =
            bc_AddNamespaceNamespace(beacon, bc_InternString("unsafe"));
        bc_Namespace* placeholder =
            bc_CreateNamespaceAtRoot(bc_InternString("$placeholder"));
        bc_InitObject();
        bc_InitArray();
        bc_InitException();
        bc_InitInt();
        bc_InitDouble();
        bc_InitChar();
        bc_InitLong();
        bc_InitString();
        bc_InitBool();
        bc_InitVoid();
        bc_InitConsole();
        bc_InitNull();
        bc_InitFile();
        bc_InitSystem();
        bc_InitLocaleType();
        bc_InitTime();
        //ブートストラップクラスローダー
        self->BootstrapClassLoader =
            bc_NewClassLoader("bootstrap", CONTENT_LIB_T);
        bc_SpecialLoadClassLoader(self->BootstrapClassLoader,
                                  "beacon/lang/Object.bc");

        bc_SpecialLoadClassLoader(self->BootstrapClassLoader,
                                  "beacon/lang/Int.bc");
        bc_SpecialLoadClassLoader(self->BootstrapClassLoader,
                                  "beacon/lang/Double.bc");
        bc_SpecialLoadClassLoader(self->BootstrapClassLoader,
                                  "beacon/lang/Char.bc");
        bc_SpecialLoadClassLoader(self->BootstrapClassLoader,
                                  "beacon/lang/Bool.bc");
        bc_SpecialLoadClassLoader(self->BootstrapClassLoader,
                                  "beacon/lang/Null.bc");
        bc_SpecialLoadClassLoader(self->BootstrapClassLoader,
                                  "beacon/lang/Void.bc");

        bc_SpecialLoadClassLoader(self->BootstrapClassLoader,
                                  "beacon/lang/Iterable.bc");
        bc_SpecialLoadClassLoader(self->BootstrapClassLoader,
                                  "beacon/lang/Iterator.bc");
        bc_SpecialLoadClassLoader(self->BootstrapClassLoader,
                                  "beacon/lang/Array.bc");
        bc_SpecialLoadClassLoader(self->BootstrapClassLoader,
                                  "beacon/lang/String.bc");
        bc_SpecialLoadClassLoader(self->BootstrapClassLoader,
                                  "beacon/lang/Console.bc");
        bc_SpecialLoadClassLoader(self->BootstrapClassLoader,
                                  "beacon/lang/Exception.bc");
        bc_SpecialLoadClassLoader(self->BootstrapClassLoader,
                                  "beacon/lang/StackTraceElement.bc");

        bc_SpecialLoadClassLoader(self->BootstrapClassLoader,
                                  "beacon/lang/World.bc");
        //退避していたコンテキストを復帰
        self->Heap->AcceptBlocking--;
        self->IsLoadForBoot = false;
}

void bc_EachStaticScriptContext(bc_ScriptContext* self, bc_StaticEach act) {
        bc_ScriptContext* ctx = self;
        for (int i = 0; i < ctx->TypeList->Length; i++) {
                bc_Type* e = (bc_Type*)bc_AtVector(ctx->TypeList, i);
                if (e->Tag != TYPE_CLASS_T) {
                        continue;
                }
                bc_Class* cls = e->Kind.Class;
                for (int j = 0; j < cls->StaticFields->Length; j++) {
                        bc_Field* f =
                            (bc_Field*)bc_AtVector(cls->StaticFields, j);
                        if (bc_IsStaticModifier(BC_MEMBER_MODIFIER(f))) {
                                act(f);
                        }
                }
        }
}

void bc_ClearScriptContext(bc_ScriptContext* self) {
        bc_EachStaticScriptContext(self, clear_impl);
}

bc_Object* bc_IInternScriptContext(bc_ScriptContext* self, int i) {
        bc_Heap* he = self->Heap;
        bc_NumericMap* cell = bc_GetNumericMapCell(self->IntegerCacheMap, i);
        he->AcceptBlocking++;
        if (cell == NULL) {
                bc_Object* obj = (bc_Object*)bc_NewInteger(i);
                obj->Paint = PAINT_ONEXIT_T;
                cell = bc_PutNumericMap(self->IntegerCacheMap, i, obj);
        }
        he->AcceptBlocking--;
        return (bc_Object*)cell->Item;
}

void bc_CacheScriptContext() {
        bc_ScriptContext* self = bc_GetCurrentScriptContext();
        if (self == NULL) return;
        bc_Heap* h = bc_GetHeap();
        if (h != NULL) h->AcceptBlocking++;
        //すでにキャッシュされている
        if (self->PositiveIntegerCacheList->Length > 0 ||
            self->NegativeIntegerCacheList->Length > 0) {
                if (h != NULL) h->AcceptBlocking--;
                return;
        }
        //正の数のキャッシュ
        for (int i = 0; i < 100; i++) {
                bc_Object* a = (bc_Object*)bc_NewInteger(i);
                bc_PushVector(self->PositiveIntegerCacheList, a);
                a->Paint = PAINT_ONEXIT_T;
        }
        //負の数のキャッシュ
        for (int i = 1; i < 10; i++) {
                bc_Object* a = (bc_Object*)bc_NewInteger(-i);
                bc_PushVector(self->NegativeIntegerCacheList, a);
                a->Paint = PAINT_ONEXIT_T;
        }
        if (h != NULL) h->AcceptBlocking--;
}

// private
static bc_ScriptContext* malloc_script_context(void) {
        bc_ScriptContext* ret =
            (bc_ScriptContext*)MEM_MALLOC(sizeof(bc_ScriptContext));
        ret->NamespaceMap = bc_NewNumericMap();
        ret->ClassLoaderMap = bc_NewTreeMap();
        ret->Heap = bc_NewHeap();
        ret->TypeList = bc_NewVector();
        ret->BootstrapClassLoader = NULL;
        ret->AllGenericList = bc_NewVector();
        ret->True = NULL;
        ret->False = NULL;
        ret->Null = NULL;
        ret->IsLoadForBoot = false;
#if defined(_MSC_VER)
        char* path = bc_GetAbsolutePath("script-lib/beacon/lang");
        ret->IncludeList = bc_GetFiles(path);
        MEM_FREE(path);
#else
        ret->IncludeList = bc_GetFiles("script-lib/beacon/lang");
#endif
        ret->PositiveIntegerCacheList = bc_NewVector();
        ret->NegativeIntegerCacheList = bc_NewVector();
        ret->IntegerCacheMap = bc_NewNumericMap();
        ret->IsPrintError = true;
        ret->IsAbortOnError = true;
        ret->ThreadRef = NULL;
        bc_AttachScriptContext(ret);
        return ret;
}

static void free_script_context(bc_ScriptContext* self) {
        int aa = bc_CountActiveObject();
        assert(self->Heap->CollectBlocking == 0);
        //全ての例外フラグをクリア
        bc_Frame* thv = bc_GetScriptThreadFrameRef(bc_GetCurrentScriptThread());
        bc_CatchVM(thv);
        bc_DeleteClassLoader(self->BootstrapClassLoader);
        if (self->Null != NULL) {
                bc_IgnoreHeap(self->Heap, self->Null);
                self->Null->Paint = PAINT_ONEXIT_T;
                bc_DestroyObject(self->Null);
        }
        bc_DeleteHeap(self->Heap);
        bc_DeleteVector(self->NegativeIntegerCacheList, delete_cache);
        bc_DeleteVector(self->PositiveIntegerCacheList, delete_cache);
        bc_DeleteNumericMap(self->IntegerCacheMap, delete_mcache);
        // DeleteObject(self->Null);
        bc_CollectGenericType();
        bc_DeleteVector(self->AllGenericList, bc_VectorDeleterOfNull);
        int x = bc_CountActiveObject();

        bc_DeleteVector(self->TypeList, bc_VectorDeleterOfNull);
        bc_DeleteTreeMap(self->ClassLoaderMap, delete_class_loader);
        //ブートストラップクラスローダを意図的に起動していないなら、
        //ここはまだNULL
        if (self->NamespaceMap != NULL) {
                bc_EachNumericMap(self->NamespaceMap, unlink_namespace);
        }

        int a = bc_CountActiveObject();
        bc_DeleteNumericMap(self->NamespaceMap, delete_namespace);
        bc_DeleteFiles(self->IncludeList);
        bc_DetachScriptContext(self);
        MEM_FREE(self);
}

static void delete_class_loader(const char* name, bc_TreeItem item) {
        bc_ClassLoader* e = (bc_ClassLoader*)item;
        bc_DeleteClassLoader(e);
}

static void unlink_namespace(bc_NumericMapKey key, bc_NumericMapItem item) {
        bc_Namespace* e = (bc_Namespace*)item;
        bc_UnlinkNamespace(e);
}

static void delete_namespace(bc_NumericMapKey key, bc_NumericMapItem item) {
        bc_Namespace* e = (bc_Namespace*)item;
        bc_DeleteNamespace(e);
}

static void clear_impl(bc_Field* item) {
        item->StaticValue = bc_GetNullObject();
}

static void delete_cache(bc_VectorItem item) {
        bc_DestroyObject((bc_Object*)item);
}

static void delete_mcache(bc_NumericMapKey key, bc_NumericMapItem item) {
        bc_DestroyObject((bc_Object*)item);
}