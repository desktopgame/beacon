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
static void CLBC_import_internal(class_loader* self, Vector* ilimports, int i);


static void CLBC_new_load_internal(class_loader * self, char * full_path);

static void CLBC_import_already(class_loader* self, class_loader* cll);
//static class_loader* CLBC_import_new(class_loader* self, char* fullPath);

void CLBC_import(class_loader* self, Vector* ilimports) {
	CL_ERROR(self);
	for (int i = self->import_manager->info_vec->Length; i < ilimports->Length; i++) {
		CLBC_import_internal(self, ilimports, i);
		CL_ERROR(self);
	}
	//Javaがjava.langをインポートせずに使用できるのと同じように、
	//全てのクラスローダーはデフォルトで beacon/lang をロードする
	script_context* ctx = GetCurrentScriptContext();
	for(int i=0; i<ctx->include_vec->Length; i++) {
		FileEntry* entry = AtVector(ctx->include_vec, i);
		if(entry->IsFile && IsMatchExtension(entry->FileName, "bc")) {
			char* p = GetAbsolutePath(entry->FileName);
			CLBC_new_load(self, p);
			MEM_FREE(p);
		}
	}
}

void CLBC_new_load(class_loader * self, char * fullPath) {
	CL_ERROR(self);
	script_context* ctx = GetCurrentScriptContext();
	ctx->heap->accept_blocking++;
	CLBC_new_load_internal(self, fullPath);
	ctx->heap->accept_blocking--;
}

class_loader* CLBC_import_new(class_loader* self, char* full_path) {
	CL_ERROR_RET(self, self);
	script_context* ctx = GetCurrentScriptContext();
	class_loader* cll = NewClassLoader(full_path, CONTENT_LIB_T);
	cll->parent = self;
	import_info* info = ImportImportManager(self->import_manager, cll);
	info->consume = false;
	PutTreeMap(ctx->class_loader_map, full_path, cll);
	return cll;
}

//private
static void CLBC_import_internal(class_loader* self, Vector* ilimports, int i) {
	CL_ERROR(self);
	if (i >= ilimports->Length ||
	    IsLoadedImportManager(self->import_manager, i)) {
		return;
	}
	VectorItem e = AtVector(ilimports, i);
	il_import* import = (il_import*)e;
	char* withExt = ConcatString(Ref2Str(import->pathv), ".bc");
	char* fullPath = ResolveScriptPath(withExt);
	CLBC_new_load(self, fullPath);
	MEM_FREE(withExt);
	MEM_FREE(fullPath);
}

static void CLBC_new_load_internal(class_loader * self, char * full_path) {
	CL_ERROR(self);
	script_context* ctx = GetCurrentScriptContext();
	//そのファイルパスに対応した
	//クラスローダが既に存在するなら無視
	class_loader* cll = GetTreeMapValue(ctx->class_loader_map, full_path);
	if (cll != NULL) {
		CLBC_import_already(self, cll);
		return;
		//新たに読みこんだなら親に設定
	} else {
		cll = CLBC_import_new(self, full_path);
	}
	//そのローダーが破損しているなら
	if (GetLastBCError()) {
		ThrowBCError(BCERROR_CHAIN_T, cll->filename);
	}
	//パースをキャンセル
	if (GetLastBCError()) {
		return;
	}
	LoadClassLoader(cll);
}

static void CLBC_import_already(class_loader* self, class_loader* cll) {
	CL_ERROR(self);
	//self -> cll への参照を与える
	import_info* info = ImportImportManager(self->import_manager, cll);
	info->consume = false;
	assert(cll->source_code != NULL);
	assert(cll->il_code != NULL);
	//そのローダーが破損しているなら
	if (GetLastBCError()) {
		ThrowBCError(BCERROR_CHAIN_T, cll->filename);
		return;
	}
}