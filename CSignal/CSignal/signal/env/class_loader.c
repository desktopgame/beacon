#include "class_loader.h"
#include <stdlib.h>
#include <assert.h>
//#include <uni>
//#include <uni>
#include "fqcn_cache.h"
#include "../util/mem.h"
#include "../il/il_type_interface.h"
#include "../vm/vm.h"
#include "../vm/opcode.h"
#include "../vm/opcode_buf.h"
#include "../env/native_method_ref.h"
#include "../il/il_argument.h"
#include "../util/vector.h"
#include "../util/logger.h"
#include "script_context.h"
#include "../util/text.h"
#include "../util/io.h"
#include "../parse/parser.h"
#include "namespace.h"
#include "type_impl.h"
#include "field.h"
#include "method.h"
#include "parameter.h"
#include "constructor.h"
#include "../il/il_constructor.h"
#include "../il/il_constructor_chain.h"
#include "../il/il_type_impl.h"
#include "../il/il_field.h"
#include "../il/il_method.h"
#include "../il/il_stmt_impl.h"
#include "../il/il_factor_impl.h"
#include "../il/il_parameter.h"
#include "../il/il_import.h"
#include "../il/il_namespace.h"
#include <string.h>

#include "class_loader_ilload_impl.h"
#include "class_loader_sgload_impl.h"
#include "import_info.h"

//proto
static void class_loader_link(class_loader* self);

class_loader* class_loader_new() {
	class_loader* ret = (class_loader*)MEM_MALLOC(sizeof(class_loader));
	ret->source_code = NULL;
	ret->il_code = NULL;
	ret->parentVec = vector_new();
	ret->ref_count = 0;
	ret->type = content_entry_point;
	ret->import_manager = import_manager_new();
	ret->env = enviroment_new();
	ret->error = false;
	ret->type_cacheVec = vector_new();
	ret->level = 0;
	ret->loadedNamespace = false;
	ret->linkedAllImports = false;
	ret->errorMessage = NULL;
	ret->env->context_cll = ret;
	ret->env->toplevel = true;
	//ret->link = classlink_unlinked;
	return ret;
}

class_loader * class_loader_new_entry_point(const char * filename) {
	class_loader* cll = class_loader_new();
	cll->filename = text_strdup(filename);
	char* text = io_read_text(filename);
	parser* p = parser_parse_from_source_swap(text, filename);
	//解析に失敗した場合
	if (p->fail) {
		class_loader_errorf(cll, "parse failed --- %s", p->source_name);
		MEM_FREE(text);
		parser_pop();
		return cll;
	}
	cll->source_code = p->root;
	p->root = NULL;
	MEM_FREE(text);
	parser_pop();
	return cll;
}

void class_loader_load(class_loader * self) {
	assert(self != NULL);
	assert(self->source_code != NULL);
	//system("cls");
	//ast_print_tree(self->source_code);
	class_loader_ilload_impl(self, self->source_code);
	if (self->error) { return; }

	class_loader_sgload_impl(self);
	if (self->error) { return; }

	class_loader_link(self);
	class_loader_sgload_body(self, self->il_code->statement_list, self->env, NULL);
	//このクラスローダーがライブラリをロードしているなら
	//必要最低限の情報を残して後は開放
	if (self->type == content_lib) {
	//	ast_delete(self->source_code);
	//	il_top_level_delete(self->il_code);
	//	self->source_code = NULL;
	//	self->il_code = NULL;
	}
}

void class_loader_delete(class_loader * self) {
	assert(self != NULL);
	//assert(self->ref_count == 0);
	for (int i = 0; i < self->parentVec->length; i++) {
		class_loader* e = (class_loader*)vector_at(self->parentVec, i);
		e->ref_count--;
	}
	//free(self->source_code);
	ast_delete(self->source_code);
	self->source_code = NULL;

	il_top_level_delete(self->il_code);
	self->il_code = NULL;

	import_manager_delete(self->import_manager);
	enviroment_delete(self->env);
	MEM_FREE(self->filename);
	MEM_FREE(self->errorMessage);
	MEM_FREE(self);
}

//utilitiy
void class_loader_error(class_loader* self, const char* message) {
	self->errorMessage = text_strdup(message);
	self->error = true;
	text_printf("%s", message);
	text_putline();
}

void class_loader_errorf(class_loader* self, const char* message, ...) {
	va_list ap;
	va_start(ap, message);
	char buff[100];
	int res = text_sprintf(buff, 100, message, ap);
	if (res == -1) {
		//on error
		text_printf("internal error: %s %d", __FILE__, __LINE__);
	} else {
		class_loader_error(self, buff);
	}
	va_end(ap);
}

//private
static void class_loader_link(class_loader* self) {
	if (self->linkedAllImports) {
		return;
	}
	self->linkedAllImports = true;
	import_manager* importMgr = self->import_manager;
	for (int i = 0; i < importMgr->infoVec->length; i++) {
		import_info* info = (import_info*)vector_at(importMgr->infoVec, i);
		class_loader_link(info->context);
	}

	class_loader_sgload_link(self);
}