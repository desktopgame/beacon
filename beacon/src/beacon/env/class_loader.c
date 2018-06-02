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
#include "compile_context.h"
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
#include "cll/class_loader_link_impl.h"
#include "import_info.h"
#include "type_cache.h"
#include "heap.h"

//proto
static void class_loader_load_impl(class_loader* self);
static void class_loader_link_recursive(class_loader* self, link_type type);
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
	ret->env->context_ref = ret;
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
		class_loader_report(ret, "parser failed --- %s\n", p->source_name);
		return ret;
	}
	ret->source_code = p->root;
	p->root = NULL;
	return ret;
}

void class_loader_load(class_loader * self) {
	heap* hee = heap_get();
	hee->accept_blocking++;
	class_loader_load_impl(self);
	hee->accept_blocking--;
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
	ast_delete(self->source_code);
	il_top_level_delete(self->il_code);
	vector_delete(self->type_cache_vec, class_loader_cache_delete);
	import_manager_delete(self->import_manager);
	enviroment_delete(self->env);
	MEM_FREE(self->filename);
	MEM_FREE(self);
}

int class_loader_report(class_loader* self, const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	int ret = class_loader_vreport(self, fmt, ap);
	va_end(ap);
	return ret;
}

int class_loader_vreport(class_loader* self, const char* fmt, va_list ap) {
	self->error = true;
	return text_vprintf(fmt, ap);
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
		class_loader_link_recursive(self, link_decl);
		class_loader_link_recursive(self, link_impl);
		il_error_exit();
	}
	//トップレベルのステートメントを読み込む
	ccset_class_loader(self);
	cc_enable(ccstate_toplevel);
	CLBC_body(self, self->il_code->statement_list, self->env, NULL);
	cc_disable(ccstate_toplevel);
	ccset_class_loader(NULL);
}

static void class_loader_link_recursive(class_loader* self, link_type type) {
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
		class_loader_link_recursive(info->context, type);
	}
	class_loader_link(self, type);
}

static void class_loader_cache_delete(vector_item item) {
	type_cache* e = (type_cache*)item;
	type_cache_delete(e);
}