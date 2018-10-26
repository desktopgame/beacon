#include "class_loader_bcload_import_module_impl.h"
#include "../../il/il_import.h"
#include "../../env/script_context.h"
#include "../../env/heap.h"
#include "../../env/import_info.h"
#include "../../parse/parser.h"
#include "../../util/text.h"
#include "../../util/io.h"
#include "../../util/mem.h"
#include "../../util/file_entry.h"
#include "class_loader_ilload_impl.h"
#include <assert.h>

//proto
static void CLBC_import_internal(ClassLoader* self, Vector* ilimports, int i);


static void CLBC_new_load_internal(ClassLoader * self, char * full_path);

static void CLBC_import_already(ClassLoader* self, ClassLoader* cll);
//static ClassLoader* CLBC_import_new(ClassLoader* self, char* fullPath);

void CLBC_import(ClassLoader* self, Vector* ilimports) {
	CL_ERROR(self);
	for (int i = self->ImportManager->Items->Length; i < ilimports->Length; i++) {
		CLBC_import_internal(self, ilimports, i);
		CL_ERROR(self);
	}
	//Javaがjava.langをインポートせずに使用できるのと同じように、
	//全てのクラスローダーはデフォルトで beacon/lang をロードする
	ScriptContext* ctx = GetCurrentScriptContext();
	for(int i=0; i<ctx->IncludeList->Length; i++) {
		FileEntry* entry = AtVector(ctx->IncludeList, i);
		if(entry->IsFile && IsMatchExtension(entry->FileName, "bc")) {
			char* p = GetAbsolutePath(entry->FileName);
			CLBC_new_load(self, p);
			MEM_FREE(p);
		}
	}
}

void CLBC_new_load(ClassLoader * self, char * fullPath) {
	CL_ERROR(self);
	ScriptContext* ctx = GetCurrentScriptContext();
	ctx->Heap->AcceptBlocking++;
	CLBC_new_load_internal(self, fullPath);
	ctx->Heap->AcceptBlocking--;
}

ClassLoader* CLBC_import_new(ClassLoader* self, char* full_path) {
	CL_ERROR_RET(self, self);
	ScriptContext* ctx = GetCurrentScriptContext();
	ClassLoader* cll = NewClassLoader(full_path, CONTENT_LIB_T);
	cll->Parent = self;
	ImportInfo* info = ImportImportManager(self->ImportManager, cll);
	info->IsConsume = false;
	PutTreeMap(ctx->ClassLoaderMap, full_path, cll);
	return cll;
}

//private
static void CLBC_import_internal(ClassLoader* self, Vector* ilimports, int i) {
	CL_ERROR(self);
	if (i >= ilimports->Length ||
	    IsLoadedImportManager(self->ImportManager, i)) {
		return;
	}
	VectorItem e = AtVector(ilimports, i);
	ILImport* import = (ILImport*)e;
	char* withExt = ConcatString(Ref2Str(import->Path), ".bc");
	char* fullPath = ResolveScriptPath(withExt);
	CLBC_new_load(self, fullPath);
	MEM_FREE(withExt);
	MEM_FREE(fullPath);
}

static void CLBC_new_load_internal(ClassLoader * self, char * full_path) {
	CL_ERROR(self);
	ScriptContext* ctx = GetCurrentScriptContext();
	//そのファイルパスに対応した
	//クラスローダが既に存在するなら無視
	ClassLoader* cll = GetTreeMapValue(ctx->ClassLoaderMap, full_path);
	if (cll != NULL) {
		CLBC_import_already(self, cll);
		return;
		//新たに読みこんだなら親に設定
	} else {
		cll = CLBC_import_new(self, full_path);
	}
	//そのローダーが破損しているなら
	if (GetLastBCError()) {
		ThrowBCError(BCERROR_CHAIN_T, cll->FileName);
	}
	//パースをキャンセル
	if (GetLastBCError()) {
		return;
	}
	LoadClassLoader(cll);
}

static void CLBC_import_already(ClassLoader* self, ClassLoader* cll) {
	CL_ERROR(self);
	//self -> cll への参照を与える
	ImportInfo* info = ImportImportManager(self->ImportManager, cll);
	info->IsConsume = false;
	assert(cll->SourceCode != NULL);
	assert(cll->ILCode != NULL);
	//そのローダーが破損しているなら
	if (GetLastBCError()) {
		ThrowBCError(BCERROR_CHAIN_T, cll->FileName);
		return;
	}
}