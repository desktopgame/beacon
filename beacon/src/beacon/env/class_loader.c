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
static void Loadclass_loader_impl(ClassLoader* self);
static void Linkclass_loader_recursive(ClassLoader* self, LinkType type);
static void class_loader_cache_delete(VectorItem item);
static ClassLoader* Loadclass_loader_specialImpl(ClassLoader* self, ClassLoader* cll, char* full_path);
static void Loadclass_loader_toplevel(ClassLoader* self);
static void Loadclass_loader_linkall(ClassLoader* self);
static void Loadclass_loader_toplevel_function(ClassLoader* self);
static bool check_parser_error(Parser* p);

ClassLoader* NewClassLoader(const char* filename, ContentType type) {
	ClassLoader* ret = (ClassLoader*)MEM_MALLOC(sizeof(ClassLoader));
	ret->SourceCode = NULL;
	ret->ILCode = NULL;
	ret->Parent = NULL;
	ret->Type = type;
	ret->Link = LINK_NONE_T;
	ret->ImportManager = NewImportManager();
	ret->Env = NewEnviroment();
	ret->Level = 0;
	ret->TypeCaches = NewVector();
	ret->FileName = Strdup(filename);
	ret->Env->ContextRef = ret;
	return ret;
}

void LoadClassLoader(ClassLoader * self) {
	//ASTを読み込む
	Parser* p = ParseFile(self->FileName);
	//解析に失敗した場合
	if (check_parser_error(p)) {
		return;
	}
	AST* a = ReleaseParserAST(p);
	DestroyParser(p);
	LoadPassASTClassLoader(self, a);
}

void LoadPassASTClassLoader(ClassLoader* self, AST* a) {
	ClearBCError();
	Heap* hee = GetHeap();
	hee->AcceptBlocking++;
	self->SourceCode = a;
	Loadclass_loader_impl(self);
	hee->AcceptBlocking--;
}

void SpecialLoadClassLoader(ClassLoader* self, char* relativePath) {
	char* fullP = ResolveScriptPath(relativePath);
	ScriptContext* ctx = GetCurrentScriptContext();
	Heap* he = GetHeap();
	ClassLoader* cll = GetTreeMapValue(ctx->ClassLoaderMap, fullP);
	he->AcceptBlocking++;
	if(cll == NULL) {
		cll = Loadclass_loader_specialImpl(self, cll, fullP);
	}
	he->AcceptBlocking--;
	MEM_FREE(fullP);
}

void DeleteClassLoader(ClassLoader * self) {
	if(self == NULL) {
		return;
	}
	DeleteAST(self->SourceCode);
	DeleteILToplevel(self->ILCode);
	DeleteVector(self->TypeCaches, class_loader_cache_delete);
	DeleteImportManager(self->ImportManager);
	DeleteEnviroment(self->Env);
	MEM_FREE(self->FileName);
	MEM_FREE(self);
}


//private
static void Loadclass_loader_impl(ClassLoader* self) {
	assert(self != NULL);
	//AST -> IL へ
	ILLoadClassLoader(self, self->SourceCode);
	if (GetLastBCError()) { return; }
	//IL -> SG へ
	BCLoadClassLoader(self);
	if (GetLastBCError()) { return; }
	//他のクラスローダーとリンク
	Loadclass_loader_linkall(self);
	Loadclass_loader_toplevel_function(self);
	Loadclass_loader_toplevel(self);
}

static void Linkclass_loader_recursive(ClassLoader* self, LinkType type) {
	if (self->Link == type) {
		return;
	}
	if(GetLastBCError()) {
		return;
	}
	self->Link = type;
	ImportManager* importMgr = self->ImportManager;
	for (int i = 0; i < importMgr->Items->Length; i++) {
		ImportInfo* info = (ImportInfo*)AtVector(importMgr->Items, i);
		if (info->IsConsume) {
			continue;
		}
		Linkclass_loader_recursive(info->Context, type);
	}
	LinkClassLoader(self, type);
}

static void class_loader_cache_delete(VectorItem item) {
	TypeCache* e = (TypeCache*)item;
	DeleteTypeCache(e);
}

static ClassLoader* Loadclass_loader_specialImpl(ClassLoader* self, ClassLoader* cll, char* full_path) {
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
	if (GetLastBCError()) { return cll; }
	//IL -> SG へ
	SpecialBCLoadClassLoader(cll);
	if (GetLastBCError()) { return cll; }
	assert(cll->Type == CONTENT_LIB_T);
	return cll;
}

static void Loadclass_loader_linkall(ClassLoader* self) {
	if(self->Type != CONTENT_ENTRY_POINT_T) {
		return;
	}
	Linkclass_loader_recursive(self, LINK_DECL_T);
	Linkclass_loader_recursive(self, LINK_IMPL_T);
}

static void Loadclass_loader_toplevel(ClassLoader* self) {
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
	body->lineno = 0;
	createWorldStmt->Value->lineno = 0;
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

static void Loadclass_loader_toplevel_function(ClassLoader* self) {
	if(self->Level != 0 || self->Type != CONTENT_ENTRY_POINT_T) {
		return;
	}
	Vector* funcs = self->ILCode->FunctionList;
	Type* worldT = FindTypeFromNamespace(GetLangNamespace(), InternString("World"));
	//前回の実行で作成されたメソッドを解放
	Vector* methods = TYPE2CLASS(worldT)->method_list;
	if(methods->Length > 0) {
		DeleteVector(methods, DeleteMethod);
		TYPE2CLASS(worldT)->method_list = NewVector();
	}
	//メソッドの宣言のみロード
	for(int i=0; i<funcs->Length; i++) {
		ILFunction* ilfunc = AtVector(funcs, i);
		Method* m = method_new(ilfunc->Name);
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
	//	Println();
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
		PushVector(worldT->Kind.Class->method_list, m);
		//CLBC_corutine(self, m, env, ilfunc->parameter_list, ilfunc->statement_list, cctx, GetLangNamespace());
		DeleteCallContext(cctx);
	}
	//実装のロード
	for(int i=0; i<funcs->Length; i++) {
		ILFunction* ilfunc = AtVector(funcs, i);
		Method* m = AtVector(TYPE2CLASS(worldT)->method_list, i);
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
		ThrowBCError(BCERROR_PARSE_T, p->ErrorMessage);
		DestroyParser(p);
		return true;
	} else if(p->Result == PARSE_OPEN_ERROR_T) {
		ThrowBCError(BCERROR_REQUIRE_NOT_FOUND_T, p->SourceName);
		DestroyParser(p);
		return true;
	}
	return false;
}