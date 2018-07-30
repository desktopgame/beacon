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
static void CLBC_import_internal(class_loader* self, vector* ilimports, int i);


static void CLBC_new_load_internal(class_loader * self, char * fullPath);

static void CLBC_import_already(class_loader* self, class_loader* cll);
//static class_loader* CLBC_import_new(class_loader* self, char* fullPath);

void CLBC_import(class_loader* self, vector* ilimports) {
	CL_ERROR(self);
	for (int i = self->import_manager->info_vec->length; i < ilimports->length; i++) {
		CLBC_import_internal(self, ilimports, i);
		CL_ERROR(self);
	}
	//Javaがjava.langをインポートせずに使用できるのと同じように、
	//全てのクラスローダーはデフォルトで beacon/lang をロードする
	script_context* ctx = script_context_get_current();
	for(int i=0; i<ctx->include_vec->length; i++) {
		file_entry* fe = vector_at(ctx->include_vec, i);
		if(fe->is_file && io_extension(fe->filename, "bc")) {
			char* p = io_absolute_path(fe->filename);
			CLBC_new_load(self, p);
			MEM_FREE(p);
		}
	}
}

void CLBC_new_load(class_loader * self, char * fullPath) {
	CL_ERROR(self);
	script_context* ctx = script_context_get_current();
	ctx->heap->accept_blocking++;
	CLBC_new_load_internal(self, fullPath);
	ctx->heap->accept_blocking--;
}

class_loader* CLBC_import_new(class_loader* self, char* fullPath) {
	CL_ERROR_RET(self, self);
	script_context* ctx = script_context_get_current();
	class_loader* cll = class_loader_new(content_lib);
	cll->type = content_lib;
	cll->filename = fullPath;
	cll->parent = self;
	import_info* info = import_manager_import(self->import_manager, cll);
	info->consume = false;
	tree_map_put(ctx->class_loader_map, fullPath, cll);
	return cll;
}

//private
static void CLBC_import_internal(class_loader* self, vector* ilimports, int i) {
	CL_ERROR(self);
	if (i >= ilimports->length ||
	    import_manager_loaded(self->import_manager, i)) {
		return;
	}
	vector_item e = vector_at(ilimports, i);
	il_import* import = (il_import*)e;
	char* withExt = text_concat(string_pool_ref2str(import->pathv), ".bc");
	char* fullPath = io_absolute_path(withExt);
	CLBC_new_load(self, fullPath);
	MEM_FREE(withExt);
	MEM_FREE(fullPath);
}

static void CLBC_new_load_internal(class_loader * self, char * fullPath) {
	CL_ERROR(self);
	script_context* ctx = script_context_get_current();
	//そのファイルパスに対応した
	//クラスローダが既に存在するなら無視
	class_loader* cll = tree_map_get(ctx->class_loader_map, fullPath);
	if (cll != NULL) {
		CLBC_import_already(self, cll);
		return;
		//新たに読みこんだなら親に設定
	} else {
		cll = CLBC_import_new(self, fullPath);
	}
	//そのローダーが破損しているなら
	if (bc_error_last()) {
		bc_error_throw(bcerror_chain, cll->filename);
	}
	//パースをキャンセル
	if (bc_error_last()) {
		return;
	}
	cll->filename = text_strdup(fullPath);
	cll->level = (self->level + 1);
	char* text = io_read_text(fullPath);
	parser* p = parser_parse_from_source_swap(text, fullPath);
	assert(p->root != NULL);
	assert(!p->fail);
	//パースに失敗
	if (p->fail) {
		MEM_FREE(text);
		parser_pop();
		return;
		//成功
	} else {
		cll->source_code = p->root;
		p->root = NULL;
		MEM_FREE(text);
		parser_pop();
	}
	//ロード
	class_loader_load(cll);
	assert(cll->source_code != NULL);
	assert(cll->il_code != NULL);
}

static void CLBC_import_already(class_loader* self, class_loader* cll) {
	CL_ERROR(self);
	//self -> cll への参照を与える
	import_info* info = import_manager_import(self->import_manager, cll);
	info->consume = false;
	assert(cll->source_code != NULL);
	assert(cll->il_code != NULL);
	//そのローダーが破損しているなら
	if (bc_error_last()) {
		bc_error_throw(bcerror_chain, cll->filename);
		return;
	}
}