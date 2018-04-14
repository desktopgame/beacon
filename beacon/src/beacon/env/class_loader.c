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
#include "../util/xassert.h"
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
#include "../il/il_error.h"
#include <string.h>

#include "cll/class_loader_ilload_impl.h"
#include "cll/class_loader_bcload_impl.h"
#include "cll/class_loader_bcload_import_module_impl.h"
#include "cll/class_loader_bcload_member_module_impl.h"
#include "import_info.h"
#include "type_cache.h"
#include "heap.h"

//proto
static void class_loader_load_impl(class_loader* self);
static void class_loader_link(class_loader* self, link_type type);
static void class_loader_cache_delete(vector_item item);

class_loader* class_loader_new(content_type type) {
	class_loader* ret = (class_loader*)MEM_MALLOC(sizeof(class_loader));
	ret->source_code = NULL;
	ret->il_code = NULL;
	ret->parent = NULL;
	ret->type = type;
	ret->link = link_none;
	ret->import_manager = import_manager_new();
	ret->env = enviroment_new();
	ret->error = false;
	ret->level = 0;
	ret->type_cache_vec = vector_new();
	//ret->linked_allimports = false;
	ret->error_message = NULL;
	ret->env->context_ref = ret;
	//text_printfln("new classloader");
	//ret->link = classlink_unlinked;
	return ret;
}

class_loader * class_loader_new_entry_point_from_file(const char * filename) {
	char* text = io_read_text(filename);
	class_loader* ret = class_loader_new_entry_point_from_source(text, filename);
	//ret->filename = text_strdup(filename);
	MEM_FREE(text);
	return ret;
}

class_loader * class_loader_new_entry_point_from_source(const char * source, const char* contextDescription) {
	parser* p = parser_parse_from_source_swap(source, contextDescription);
	class_loader* ret = class_loader_new_entry_point_from_parser(p);
	parser_pop();
	ret->filename = text_strdup(contextDescription);
	return ret;
}

class_loader * class_loader_new_entry_point_from_parser(parser * p) {
	class_loader* ret = class_loader_new(content_entry_point);
	//解析に失敗した場合
	if (p->fail) {
		class_loader_errorf(ret, "parse failed --- %s", p->source_name);
		//MEM_FREE(text);
		//parser_pop();
		return ret;
	}
	ret->source_code = p->root;
	p->root = NULL;
	//MEM_FREE(text);
	return ret;
}

void class_loader_load(class_loader * self) {
	heap* hee = heap_get();
	hee->blocking++;
	class_loader_load_impl(self);
	hee->blocking--;
}

void class_loader_sub(class_loader * self, char * fullPath) {
	CLBC_new_load(self, fullPath);
}

void class_loader_rsub(class_loader * self, char * relativePath) {
	char* a = io_absolute_path(relativePath);
	class_loader_sub(self, a);
	MEM_FREE(a);
}

void class_loader_delete(class_loader * self) {
	if(self == NULL) {
		return;
	}
	//text_printf("deleted loader %s\n", self->filename);
	//free(self->source_code);
	ast_delete(self->source_code);
	il_top_level_delete(self->il_code);
	vector_delete(self->type_cache_vec, class_loader_cache_delete);
	import_manager_delete(self->import_manager);
	enviroment_delete(self->env);
	MEM_FREE(self->filename);
	MEM_FREE(self->error_message);
	MEM_FREE(self);
}

//utilitiy
void class_loader_error(class_loader* self, const char* message) {
	self->error_message = text_strdup(message);
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
static void class_loader_load_impl(class_loader* self) {
	assert(self != NULL);
	assert(self->source_code != NULL);
	//AST -> IL へ
	class_loader_ilload_impl(self, self->source_code);
	if (self->error) { return; }
	//IL -> SG へ
	class_loader_bcload_impl(self);
	if (self->error) { return; }
	//他のクラスローダーとリンク
	if(self->type == content_entry_point) {
		il_error_enter();
		class_loader_link(self, link_decl);
		class_loader_link(self, link_impl);
		il_error_exit();
	}
	//トップレベルのステートメントを読み込む
	il_context* ilctx = il_context_new();
	ilctx->toplevel = true;
	CLBC_body(self, self->il_code->statement_list, self->env, NULL, ilctx);
	il_context_delete(ilctx);
	logger_log(log_info, __FILE__, __LINE__, "loaded file %s", self->filename);
}

static void class_loader_link(class_loader* self, link_type type) {
	if (self->link == type) {
		return;
	}
	self->link = type;
	import_manager* importMgr = self->import_manager;
	for (int i = 0; i < importMgr->info_vec->length; i++) {
		import_info* info = (import_info*)vector_at(importMgr->info_vec, i);
		if (info->consume) {
			continue;
		}
		//info->consume = true;
		class_loader_link(info->context, type);
	}
//	XBREAK((
//		!text_contains(self->filename, "Array") &&
//		text_contains(self->filename, "Iterator"))
//	);
	class_loader_bcload_link(self, type);
}

static void class_loader_cache_delete(vector_item item) {
	type_cache* e = (type_cache*)item;
	type_cache_delete(e);
}