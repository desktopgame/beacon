#include "class_loader.h"
#include <stdlib.h>
#include <assert.h>
#include "fqcn_cache.h"
#include "../util/mem.h"
#include "../il/il_type_interface.h"
#include "../il/il_function.h"
#include "../vm/vm.h"
#include "../vm/opcode.h"
#include "../vm/opcode_buf.h"
#include "../env/native_method_ref.h"
#include "../env/type_parameter.h"
#include "../il/il_argument.h"
#include "../util/vector.h"
#include "script_context.h"
#include "../util/text.h"
#include "../util/io.h"
#include "../parse/parser.h"
#include "namespace.h"
#include "TYPE_IMPL.h"
#include "field.h"
#include "method.h"
#include "parameter.h"
#include "constructor.h"
#include "../il/il_constructor.h"
#include "../il/il_constructor_chain.h"
#include "../il/il_TYPE_IMPL.h"
#include "../il/il_field.h"
#include "../il/il_method.h"
#include "../il/il_stmt_impl.h"
#include "../il/il_factor_impl.h"
#include "../il/il_parameter.h"
#include "../il/il_import.h"
#include "../il/il_namespace.h"
#include "../error.h"
#include <string.h>

#include "cll/class_loader_ilload_impl.h"
#include "cll/class_loader_ilload_type_module_impl.h"
#include "cll/class_loader_bcload_impl.h"
#include "cll/class_loader_bcload_import_module_impl.h"
#include "cll/class_loader_bcload_member_module_impl.h"
#include "cll/class_loader_link_impl.h"
#include "import_info.h"
#include "type_cache.h"
#include "heap.h"

//proto
static void load_class(bc_ClassLoader* self);
static void link_recursive(bc_ClassLoader* self, bc_LinkType type);
static void delete_cache(VectorItem item);
static bc_ClassLoader* load_special_class(bc_ClassLoader* self, bc_ClassLoader* cll, char* full_path);
static void load_toplevel(bc_ClassLoader* self);
static void link_all(bc_ClassLoader* self);
static void load_toplevel_function(bc_ClassLoader* self);
static bool check_parser_error(Parser* p);

bc_ClassLoader* bc_NewClassLoader(const char* filename, bc_ContentType type) {
	bc_ClassLoader* ret = (bc_ClassLoader*)MEM_MALLOC(sizeof(bc_ClassLoader));
	ret->SourceCode = NULL;
	ret->ILCode = NULL;
	ret->Parent = NULL;
	ret->Type = type;
	ret->Link = LINK_NONE_T;
	ret->ImportManager = bc_NewImportManager();
	ret->Env = bc_NewEnviroment();
	ret->Level = 0;
	ret->TypeCaches = NewVector();
	ret->FileName = bc_Strdup(filename);
	ret->Env->ContextRef = ret;
	return ret;
}

void bc_LoadClassLoader(bc_ClassLoader * self) {
	//ASTを読み込む
	Parser* p = ParseFile(self->FileName);
	//解析に失敗した場合
	if (check_parser_error(p)) {
		return;
	}
	bc_AST* a = ReleaseParserAST(p);
	DestroyParser(p);
	bc_LoadPassASTClassLoader(self, a);
}

void bc_LoadPassASTClassLoader(bc_ClassLoader* self, bc_AST* a) {
	bc_Recover();
	bc_Heap* hee = bc_GetHeap();
	hee->AcceptBlocking++;
	self->SourceCode = a;
	load_class(self);
	hee->AcceptBlocking--;
}

void bc_SpecialLoadClassLoader(bc_ClassLoader* self, char* relativePath) {
	char* fullP = bc_ResolveScriptPath(relativePath);
	bc_ScriptContext* ctx = bc_GetCurrentScriptContext();
	bc_Heap* he = bc_GetHeap();
	bc_ClassLoader* cll = GetTreeMapValue(ctx->ClassLoaderMap, fullP);
	he->AcceptBlocking++;
	if(cll == NULL) {
		cll = load_special_class(self, cll, fullP);
	}
	he->AcceptBlocking--;
	MEM_FREE(fullP);
}

void bc_DeleteClassLoader(bc_ClassLoader * self) {
	if(self == NULL) {
		return;
	}
	bc_DeleteAST(self->SourceCode);
	DeleteILToplevel(self->ILCode);
	DeleteVector(self->TypeCaches, delete_cache);
	bc_DeleteImportManager(self->ImportManager);
	bc_DeleteEnviroment(self->Env);
	MEM_FREE(self->FileName);
	MEM_FREE(self);
}


//private
static void load_class(bc_ClassLoader* self) {
	assert(self != NULL);
	//AST -> IL へ
	ILLoadClassLoader(self, self->SourceCode);
	if (bc_GetLastPanic()) { return; }
	//IL -> SG へ
	BCLoadClassLoader(self);
	if (bc_GetLastPanic()) { return; }
	//他のクラスローダーとリンク
	link_all(self);
	load_toplevel_function(self);
	load_toplevel(self);
}

static void link_recursive(bc_ClassLoader* self, bc_LinkType type) {
	if (self->Link == type) {
		return;
	}
	if(bc_GetLastPanic()) {
		return;
	}
	self->Link = type;
	bc_ImportManager* importMgr = self->ImportManager;
	for (int i = 0; i < importMgr->Items->Length; i++) {
		bc_ImportInfo* info = (bc_ImportInfo*)AtVector(importMgr->Items, i);
		if (info->IsConsume) {
			continue;
		}
		link_recursive(info->Context, type);
	}
	LinkClassLoader(self, type);
}

static void delete_cache(VectorItem item) {
	bc_TypeCache* e = (bc_TypeCache*)item;
	bc_DeleteTypeCache(e);
}

static bc_ClassLoader* load_special_class(bc_ClassLoader* self, bc_ClassLoader* cll, char* full_path) {
	cll = CLBC_import_new(self, full_path);
	//parser
	Parser* p = ParseFile(full_path);
	if(check_parser_error(p)) {
		return cll;
	}
	//ASTをclassloaderへ
	cll->SourceCode = ReleaseParserAST(p);
	DestroyParser(p);
	//AST -> IL へ
	ILLoadClassLoader(cll, cll->SourceCode);
	if (bc_GetLastPanic()) { return cll; }
	//IL -> SG へ
	SpecialBCLoadClassLoader(cll);
	if (bc_GetLastPanic()) { return cll; }
	assert(cll->Type == CONTENT_LIB_T);
	return cll;
}

static void link_all(bc_ClassLoader* self) {
	if(self->Type != CONTENT_ENTRY_POINT_T) {
		return;
	}
	link_recursive(self, LINK_DECL_T);
	link_recursive(self, LINK_IMPL_T);
}

static void load_toplevel(bc_ClassLoader* self) {
	//トップレベルのステートメントを読み込む
	if(self->Type != CONTENT_ENTRY_POINT_T) {
		return;
	}
	//var $world = new beacon::lang::World();
	ILInferencedTypeInit* createWorldStmt = NewILInferencedTypeInit(InternString("$world"));
	ILNewInstance* newWorldInstance = NewILNewInstance();
	newWorldInstance->FQCNCache->Name = InternString("World");
	createWorldStmt->Value = WrapILNewInstance(newWorldInstance);
	ILStatement* body = WrapILInferencedTypeInit(createWorldStmt);
	//これをやらないと -1 のまま
	body->Lineno = 0;
	createWorldStmt->Value->Lineno = 0;
	//worldをselfにする
	CallContext* cctx = NewCallContext(CALL_TOP_T);
	cctx->Ty = bc_FindTypeFromNamespace(bc_GetLangNamespace(), InternString("World"));
	LoadILStmt(body, self->Env, cctx);
	GenerateILStmt(body, self->Env, cctx);
	//$worldをthisにする
	bc_AddOpcodeBuf(self->Env->Bytecode, OP_LOAD);
	bc_AddOpcodeBuf(self->Env->Bytecode, 1);
	bc_AddOpcodeBuf(self->Env->Bytecode, OP_STORE);
	bc_AddOpcodeBuf(self->Env->Bytecode, 0);
	//以下読み込み
	CLBC_body(self, self->ILCode->StatementList, self->Env, cctx, NULL);
	DeleteILStmt(body);
	DeleteCallContext(cctx);
	bc_CacheScriptContext();
}

static void load_toplevel_function(bc_ClassLoader* self) {
	if(self->Level != 0 || self->Type != CONTENT_ENTRY_POINT_T) {
		return;
	}
	Vector* funcs = self->ILCode->FunctionList;
	bc_Type* worldT = bc_FindTypeFromNamespace(bc_GetLangNamespace(), InternString("World"));
	//前回の実行で作成されたメソッドを解放
	Vector* methods = BC_TYPE2CLASS(worldT)->Methods;
	if(methods->Length > 0) {
		DeleteVector(methods, bc_DeleteMethod);
		BC_TYPE2CLASS(worldT)->Methods = NewVector();
	}
	//メソッドの宣言のみロード
	for(int i=0; i<funcs->Length; i++) {
		ILFunction* ilfunc = AtVector(funcs, i);
		bc_Method* m = bc_NewMethod(ilfunc->Name);
		bc_DupTypeParameterList(ilfunc->TypeParameters, m->TypeParameters);
		bc_ScriptMethod* sm = bc_NewScriptMethod();
		bc_Enviroment* env = bc_NewEnviroment();
		//CallContextの設定
		CallContext* cctx = NewCallContext(CALL_METHOD_T);
		cctx->Scope = bc_GetLangNamespace();
		cctx->Ty = worldT;
		cctx->Kind.Method = m;
		bc_Namespace* loc = GetNamespaceCContext(cctx);
		env->ContextRef = self;
		sm->Env = env;
		m->Access = ACCESS_PRIVATE_T;
		m->Kind.Script = sm;
		m->Parent = worldT;
		//戻り値を指定
		m->ReturnGType = bc_ResolveImportManager(loc, ilfunc->ReturnGCache, cctx);
	//	PrintGenericType(m->return_gtype);
	//	bc_Println();
		//引数を指定
		for(int j=0; j<ilfunc->Parameters->Length; j++) {
			ILParameter* ilparam = AtVector(ilfunc->Parameters, j);
			bc_Parameter* param = bc_NewParameter(ilparam->Name);
			PushVector(m->Parameters, param);
			param->GType = bc_ResolveImportManager(loc, ilparam->GCache, cctx);
			bc_EntrySymbolTable(
				env->Symboles,
				bc_ResolveImportManager(loc, ilparam->GCache, cctx),
				ilparam->Name
			);
			//実引数を保存
			//0番目は this のために開けておく
			bc_AddOpcodeBuf(env->Bytecode, OP_STORE);
			bc_AddOpcodeBuf(env->Bytecode, (j + 1));
		}
		bc_AddOpcodeBuf(env->Bytecode, (VectorItem)OP_STORE);
		bc_AddOpcodeBuf(env->Bytecode, (VectorItem)0);
		PushVector(worldT->Kind.Class->Methods, m);
		//CLBC_corutine(self, m, env, ilfunc->parameter_list, ilfunc->statement_list, cctx, GetLangNamespace());
		DeleteCallContext(cctx);
	}
	//実装のロード
	for(int i=0; i<funcs->Length; i++) {
		ILFunction* ilfunc = AtVector(funcs, i);
		bc_Method* m = AtVector(BC_TYPE2CLASS(worldT)->Methods, i);
		bc_ScriptMethod* sm = m->Kind.Script;
		CallContext* cctx = NewCallContext(CALL_METHOD_T);
		cctx->Scope = bc_GetLangNamespace();
		cctx->Ty = worldT;
		cctx->Kind.Method = m;
		CLBC_corutine(self, m, sm->Env, ilfunc->Parameters, ilfunc->Statements, cctx, bc_GetLangNamespace());
		DeleteCallContext(cctx);
	}
}

static bool check_parser_error(Parser* p) {
	if(p->Result == PARSE_SYNTAX_ERROR_T) {
		bc_Panic(BCERROR_PARSE_T, p->ErrorMessage);
		DestroyParser(p);
		return true;
	} else if(p->Result == PARSE_OPEN_ERROR_T) {
		bc_Panic(BCERROR_REQUIRE_NOT_FOUND_T, p->SourceName);
		DestroyParser(p);
		return true;
	}
	return false;
}