#include "class_loader_bcload_import_module_impl.h"
#include "../../il/il_import.h"
#include "../../env/script_context.h"
#include "../../env/heap.h"
#include "../../env/import_info.h"
#include "../../parse/parser.h"
#include "../../util/text.h"
#include "../../util/io.h"
#include "../../util/mem.h"
#include "class_loader_bcload_link_module_impl.h"
#include "class_loader_ilload_impl.h"
#include <assert.h>

//proto
static void CLBC_import_internal(class_loader* self, vector* ilimports, int i);


static void CLBC_new_load_internal(class_loader * self, char * fullPath);

static void CLBC_import_already(class_loader* self, class_loader* cll);
static class_loader* CLBC_import_new(class_loader* self, char* fullPath);

void CLBC_import(class_loader* self, vector* ilimports) {
	CL_ERROR(self);
	for (int i = self->import_manager->info_vec->length; i < ilimports->length; i++) {
		CLBC_import_internal(self, ilimports, i);
		CL_ERROR(self);
	}
}

void CLBC_new_load(class_loader * self, char * fullPath) {
	CL_ERROR(self);
	script_context* ctx = script_context_get_current();
	ctx->heap->accept_blocking++;
	CLBC_new_load_internal(self, fullPath);
	ctx->heap->accept_blocking--;
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
	char* withExt = text_concat(import->path, ".bc");
	char* fullPath = io_absolute_path(withExt);
	CLBC_new_load(self, fullPath);
	MEM_FREE(withExt);
	MEM_FREE(fullPath);
}

static void CLBC_new_load_internal(class_loader * self, char * fullPath) {
	CL_ERROR(self);
	script_context* ctx = script_context_get_current();
	//text_printf("%s\n", fullPath);
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
	if (cll->error) {
		class_loader_report(self, "error %s\n", cll->filename);
	}
	//パースをキャンセル
	if (self->error) {
		cll->error = true;
		return;
	}
	cll->filename = text_strdup(fullPath);
	cll->level = (self->level + 1);
	//cll->link = classlink_unlinked;
	char* text = io_read_text(fullPath);
	parser* p = parser_parse_from_source_swap(text, fullPath);
	assert(p->root != NULL);
	assert(!p->fail);
	//パースに失敗
	if (p->fail) {
		//class_loader_errors(cll, "parse failed --- %s", p->source_name);
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
	//text_printf("aimport %s\n", cll->filename);
	//そのローダーが破損しているなら
	if (cll->error) {
		class_loader_report(self, "error %s\n", cll->filename);
		return;
	}
	//CLBC_import(cll, cll->il_code->import_list);
}

static class_loader* CLBC_import_new(class_loader* self, char* fullPath) {
	CL_ERROR_RET(self, self);
	script_context* ctx = script_context_get_current();
	class_loader* cll = class_loader_new(content_lib);
	cll->type = content_lib;
	cll->filename = fullPath;
	cll->parent = self;
	//text_printf("nimport %s\n", cll->filename);
	import_info* info = import_manager_import(self->import_manager, cll);
	info->consume = false;
	tree_map_put(ctx->class_loader_map, fullPath, cll);
	return cll;
}
