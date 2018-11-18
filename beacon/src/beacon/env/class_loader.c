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
static void link_recursive(bc_ClassLoader* self, LinkType type);
static void delete_cache(VectorItem item);
static bc_ClassLoader* load_special_class(bc_ClassLoader* self, bc_ClassLoader* cll, char* full_path);
static void load_toplevel(bc_ClassLoader* self);
static void link_all(bc_ClassLoader* self);
static void load_toplevel_function(bc_ClassLoader* self);
static bool check_parser_error(Parser* p);

bc_ClassLoader* bc_NewClassLoader(const char* filename, ContentType type) {
	bc_ClassLoader* ret = (bc_ClassLoader*)MEM_MALLOC(sizeof(bc_ClassLoader));
	ret->SourceCode = NULL;
	ret->ILCode = NULL;
	ret->Parent = NULL;
	ret->Type = type;
	ret->Link = LINK_NONE_T;
	ret->ImportManager = NewImportManager();
	ret->Env = NewEnviroment();
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
	Heap* hee = GetHeap();
	hee->AcceptBlocking++;
	self->SourceCode = a;
	load_class(self);
	hee->AcceptBlocking--;
}

void bc_SpecialLoadClassLoader(bc_ClassLoader* self, char* relativePath) {
	char* fullP = bc_ResolveScriptPath(relativePath);
	ScriptContext* ctx = GetCurrentScriptContext();
	Heap* he = GetHeap();
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
	DeleteImportManager(self->ImportManager);
	DeleteEnviroment(self->Env);
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

static void link_recursive(bc_ClassLoader* self, LinkType type) {
	if (self->Link == type) {
		return;
	}
	if(bc_GetLastPanic()) {
		return;
	}
	self->Link = type;
	ImportManager* importMgr = self->ImportManager;
	for (int i = 0; i < importMgr->Items->Length; i++) {
		ImportInfo* info = (ImportInfo*)AtVector(importMgr->Items, i);
		if (info->IsConsume) {
			continue;
		}
		link_recursive(info->Context, type);
	}
	LinkClassLoader(self, type);
}

static void delete_cache(VectorItem item) {
	TypeCache* e = (TypeCache*)item;
	DeleteTypeCache(e);
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
	cctx->Ty = FindTypeFromNamespace(GetLangNamespace(), InternString("World"));
	LoadILStmt(body, self->Env, cctx);
	GenerateILStmt(body, self->Env, cctx);
	//$worldをthisにする
	AddOpcodeBuf(self->Env->Bytecode, OP_LOAD);
	AddOpcodeBuf(self->Env->Bytecode, 1);
	AddOpcodeBuf(self->Env->Bytecode, OP_STORE);
	AddOpcodeBuf(self->Env->Bytecode, 0);
	//以下読み込み
	CLBC_body(self, self->ILCode->StatementList, self->Env, cctx, NULL);
	DeleteILStmt(body);
	DeleteCallContext(cctx);
	CacheScriptContext();
}

static void load_toplevel_function(bc_ClassLoader* self) {
	if(self->Level != 0 || self->Type != CONTENT_ENTRY_POINT_T) {
		return;
	}
	Vector* funcs = self->ILCode->FunctionList;
	Type* worldT = FindTypeFromNamespace(GetLangNamespace(), InternString("World"));
	//前回の実行で作成されたメソッドを解放
	Vector* methods = TYPE2CLASS(worldT)->Methods;
	if(methods->Length > 0) {
		DeleteVector(methods, DeleteMethod);
		TYPE2CLASS(worldT)->Methods = NewVector();
	}
	//メソッドの宣言のみロード
	for(int i=0; i<funcs->Length; i++) {
		ILFunction* ilfunc = AtVector(funcs, i);
		Method* m = NewMethod(ilfunc->Name);
		DupTypeParameterList(ilfunc->TypeParameters, m->TypeParameters);
		ScriptMethod* sm = NewScriptMethod();
		Enviroment* env = NewEnviroment();
		//CallContextの設定
		CallContext* cctx = NewCallContext(CALL_METHOD_T);
		cctx->Scope = GetLangNamespace();
		cctx->Ty = worldT;
		cctx->Kind.Method = m;
		Namespace* loc = GetNamespaceCContext(cctx);
		env->ContextRef = self;
		sm->Env = env;
		m->Access = ACCESS_PRIVATE_T;
		m->Kind.Script = sm;
		m->Parent = worldT;
		//戻り値を指定
		m->ReturnGType = ResolveImportManager(loc, ilfunc->ReturnGCache, cctx);
	//	PrintGenericType(m->return_gtype);
	//	bc_Println();
		//引数を指定
		for(int j=0; j<ilfunc->Parameters->Length; j++) {
			ILParameter* ilparam = AtVector(ilfunc->Parameters, j);
			Parameter* param = NewParameter(ilparam->Name);
			PushVector(m->Parameters, param);
			param->GType = ResolveImportManager(loc, ilparam->GCache, cctx);
			EntrySymbolTable(
				env->Symboles,
				ResolveImportManager(loc, ilparam->GCache, cctx),
				ilparam->Name
			);
			//実引数を保存
			//0番目は this のために開けておく
			AddOpcodeBuf(env->Bytecode, OP_STORE);
			AddOpcodeBuf(env->Bytecode, (j + 1));
		}
		AddOpcodeBuf(env->Bytecode, (VectorItem)OP_STORE);
		AddOpcodeBuf(env->Bytecode, (VectorItem)0);
		PushVector(worldT->Kind.Class->Methods, m);
		//CLBC_corutine(self, m, env, ilfunc->parameter_list, ilfunc->statement_list, cctx, GetLangNamespace());
		DeleteCallContext(cctx);
	}
	//実装のロード
	for(int i=0; i<funcs->Length; i++) {
		ILFunction* ilfunc = AtVector(funcs, i);
		Method* m = AtVector(TYPE2CLASS(worldT)->Methods, i);
		ScriptMethod* sm = m->Kind.Script;
		CallContext* cctx = NewCallContext(CALL_METHOD_T);
		cctx->Scope = GetLangNamespace();
		cctx->Ty = worldT;
		cctx->Kind.Method = m;
		CLBC_corutine(self, m, sm->Env, ilfunc->Parameters, ilfunc->Statements, cctx, GetLangNamespace());
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