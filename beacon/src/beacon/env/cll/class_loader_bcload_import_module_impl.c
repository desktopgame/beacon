#include "class_loader_bcload_import_module_impl.h"
#include <assert.h>
#include "../../env/heap.h"
#include "../../env/import_info.h"
#include "../../env/script_context.h"
#include "../../il/il_import.h"
#include "../../parse/parser.h"
#include "../../util/file_entry.h"
#include "../../util/io.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "class_loader_ilload_impl.h"

// proto
static void CLBC_import_internal(bc_ClassLoader* self, bc_Vector* ilimports,
                                 int i);

static void CLBC_new_load_internal(bc_ClassLoader* self, char* full_path);

static void CLBC_import_already(bc_ClassLoader* self, bc_ClassLoader* cll);
// static ClassLoader* CLBC_import_new(ClassLoader* self, char* fullPath);

void CLBC_import(bc_ClassLoader* self, bc_Vector* ilimports) {
        bc_CL_ERROR(self);
        for (int i = self->ImportManager->Items->Length; i < ilimports->Length;
             i++) {
                CLBC_import_internal(self, ilimports, i);
                bc_CL_ERROR(self);
        }
        // Javaがjava.langをインポートせずに使用できるのと同じように、
        //全てのクラスローダーはデフォルトで beacon/lang をロードする
        bc_ScriptContext* ctx = bc_GetScriptContext();
        for (int i = 0; i < ctx->IncludeList->Length; i++) {
                bc_FileEntry* entry = bc_AtVector(ctx->IncludeList, i);
                if (entry->IsFile &&
                    bc_IsMatchExtension(entry->FileName, "bc")) {
                        char* p = bc_GetAbsolutePath(entry->FileName);
                        CLBC_new_load(self, p);
                        MEM_FREE(p);
                }
        }
}

void CLBC_new_load(bc_ClassLoader* self, char* fullPath) {
        bc_CL_ERROR(self);
        bc_Heap* he = bc_GetHeap();
        bc_BeginNewConstant();
        CLBC_new_load_internal(self, fullPath);
        bc_EndNewConstant();
}

bc_ClassLoader* CLBC_import_new(bc_ClassLoader* self, char* full_path) {
        bc_CL_ERROR_RET(self, self);
        bc_ScriptContext* ctx = bc_GetScriptContext();
        bc_ClassLoader* cll = bc_NewClassLoader(full_path, CONTENT_LIB_T);
        cll->Parent = self;
        bc_ImportInfo* info = bc_ImportImportManager(self->ImportManager, cll);
        info->IsConsume = false;
        bc_PutTreeMap(ctx->ClassLoaderMap, full_path, cll);
        return cll;
}

// private
static void CLBC_import_internal(bc_ClassLoader* self, bc_Vector* ilimports,
                                 int i) {
        bc_CL_ERROR(self);
        if (i >= ilimports->Length ||
            bc_IsLoadedImportManager(self->ImportManager, i)) {
                return;
        }
        bc_VectorItem e = bc_AtVector(ilimports, i);
        bc_ILImport* import = (bc_ILImport*)e;
        char* withExt = bc_ConcatString(bc_Ref2Str(import->Path), ".bc");
        char* fullPath = bc_ResolveScriptPath(withExt);
        CLBC_new_load(self, fullPath);
        MEM_FREE(withExt);
        MEM_FREE(fullPath);
}

static void CLBC_new_load_internal(bc_ClassLoader* self, char* full_path) {
        bc_CL_ERROR(self);
        bc_ScriptContext* ctx = bc_GetScriptContext();
        //そのファイルパスに対応した
        //クラスローダが既に存在するなら無視
        bc_ClassLoader* cll =
            bc_GetTreeMapValue(ctx->ClassLoaderMap, full_path);
        if (cll != NULL) {
                CLBC_import_already(self, cll);
                return;
                //新たに読みこんだなら親に設定
        } else {
                cll = CLBC_import_new(self, full_path);
        }
        //そのローダーが破損しているなら
        if (bc_GetLastPanic()) {
                bc_Panic(BCERROR_CHAIN_T, cll->FileName);
        }
        //パースをキャンセル
        if (bc_GetLastPanic()) {
                return;
        }
        bc_LoadClassLoader(cll);
}

static void CLBC_import_already(bc_ClassLoader* self, bc_ClassLoader* cll) {
        bc_CL_ERROR(self);
        // self -> cll への参照を与える
        bc_ImportInfo* info = bc_ImportImportManager(self->ImportManager, cll);
        info->IsConsume = false;
        assert(cll->SourceCode != NULL);
        assert(cll->ILCode != NULL);
        //そのローダーが破損しているなら
        if (bc_GetLastPanic()) {
                bc_Panic(BCERROR_CHAIN_T, cll->FileName);
                return;
        }
}