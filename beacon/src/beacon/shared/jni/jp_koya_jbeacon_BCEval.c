#include "jp_koya_jbeacon_BCEval.h"
#include "../../vm/eval.h"
#include "../../vm/frame.h"
#include "../../vm/symbol_entry.h"
#include "../../env/heap.h"
#include "../../env/script_context.h"
#include "../../env/class_loader.h"
#include "../../env/namespace.h"
#include "../../env/generic_type.h"
#include "../../thread/thread.h"
#include "../../parse/parser.h"
#include "../../lib/beacon/lang/bc_string.h"
#include "../../error.h"

static void bc_eval_write(JNIEnv* env, numeric_map* nmap, frame* fr, jobject target);

static frame* bc_eval_allocate(class_loader* cll);
static void bc_eval_release(class_loader* cll, frame* fr);

JNIEXPORT jobject JNICALL Java_jp_koya_jbeacon_BCEval_nativeFile(JNIEnv * env, jclass cls, jstring str) {
	const char* str_c = (*env)->GetStringUTFChars(env, str, 0);
	class_loader* cll = class_loader_new(str_c, content_entry_point_T);
	class_loader_load(cll);
	if(bc_error_last()) {
		class_loader_delete(cll);
		jclass bc_compile_exc_cls = (*env)->FindClass(env, "jp/koya/jbeacon/BCCompileException");
		(*env)->ThrowNew(env, bc_compile_exc_cls, "compile error");
		return NULL;
	}
	//jp.koya.jbeacon.SymbolTableを検索する
	jclass symbol_table_cls = (*env)->FindClass(env, "jp/koya/jbeacon/SymbolTable");
	if(symbol_table_cls == NULL) {
		(*env)->FatalError(env, "not found class: jp/koya/jbeacon/SymbolTable");
		return NULL;
	}
	//コンストラクタを検索する
	jmethodID symbol_table_ctor_id = (*env)->GetMethodID(env, symbol_table_cls, "<init>", "()V");
	if(symbol_table_ctor_id == NULL) {
		(*env)->FatalError(env, "not found ctor: <init>");
		return NULL;
	}
	//インスタンスを生成
	jobject symbol_table_obj = (*env)->NewObject(env, symbol_table_cls, symbol_table_ctor_id);
	//スクリプトを実行
	frame* fr =  bc_eval_allocate(cll);
	bc_eval_write(env, cll->env->sym_table->map->left, fr, symbol_table_obj);
	bc_eval_write(env, cll->env->sym_table->map->right, fr, symbol_table_obj);
	bc_eval_release(cll, fr);
	//https://stackoverflow.com/questions/23085044/jni-system-out-and-printf-behaviour
	fflush(stdout);
	return symbol_table_obj;
}

JNIEXPORT jobject JNICALL Java_jp_koya_jbeacon_BCEval_nativeString(JNIEnv * env, jclass cls, jstring str) {
	const char* str_c = (*env)->GetStringUTFChars(env, str, 0);
	//文字列を解析
	parser* p = parse_string(str_c);
	if (p->result != parse_complete_T) {
		bc_error_throw(bcerror_parse_T, p->error_message);
		parser_destroy(p);
		jclass bc_compile_exc_cls = (*env)->FindClass(env, "jp/koya/jbeacon/BCCompileException");
		(*env)->ThrowNew(env, bc_compile_exc_cls, "compile error");
		return NULL;
	}
	ast* a = parser_release_ast(p);
	parser_destroy(p);
	class_loader* cll = class_loader_new(str_c, content_entry_point_T);
	class_loader_load_pass_ast(cll, a);
	if(bc_error_last()) {
		class_loader_delete(cll);
		return NULL;
	}
	//jp.koya.jbeacon.SymbolTableを検索する
	jclass symbol_table_cls = (*env)->FindClass(env, "jp/koya/jbeacon/SymbolTable");
	if(symbol_table_cls == NULL) {
		(*env)->FatalError(env, "not found class: jp/koya/jbeacon/SymbolTable");
		return NULL;
	}
	//コンストラクタを検索する
	jmethodID symbol_table_ctor_id = (*env)->GetMethodID(env, symbol_table_cls, "<init>", "()V");
	if(symbol_table_ctor_id == NULL) {
		(*env)->FatalError(env, "not found ctor: <init>");
		return NULL;
	}
	//インスタンスを生成
	jobject symbol_table_obj = (*env)->NewObject(env, symbol_table_cls, symbol_table_ctor_id);
	//スクリプトを実行
	frame* fr =  bc_eval_allocate(cll);
	bc_eval_write(env, cll->env->sym_table->map->left, fr, symbol_table_obj);
	bc_eval_write(env, cll->env->sym_table->map->right, fr, symbol_table_obj);
	bc_eval_release(cll, fr);
	//https://stackoverflow.com/questions/23085044/jni-system-out-and-printf-behaviour
	fflush(stdout);
	return symbol_table_obj;
}
//private
static frame* bc_eval_allocate(class_loader* cll) {
	script_context* ctx = script_context_get_current();
	frame* fr = frame_new();
	sg_thread_set_frame_ref(sg_thread_current(script_context_get_current()), fr);
	heap* he = heap_get();
	he->accept_blocking = 0;
	if(!bc_error_last()) {
		vm_execute(fr, cll->env);
	}
	if(fr->terminate) {
		bc_error_throw(bcerror_generic_T, "unexpected terminate");
	}
	return fr;
}

static void bc_eval_write(JNIEnv* env, numeric_map* nmap, frame* fr, jobject target) {
	if(nmap == NULL) {
		return;
	}
	numeric_key key = nmap->key;
	numeric_map_item val = nmap->item;
	const char* name = string_pool_ref2str(key);
	symbol_entry* se = (symbol_entry*)val;
	object* bcobj = vector_at(fr->ref_stack, se->index);
	//jp.koya.jbeacon.SymbolTableを検索する
	jclass symbol_table_cls = (*env)->FindClass(env, "jp/koya/jbeacon/SymbolTable");
	if(symbol_table_cls == NULL) {
		(*env)->FatalError(env, "not found class: jp/koya/jbeacon/SymbolTable");
		return;
	}
	//beaconのオブジェクトをjavaのオブジェクトへ
	jstring keyj= (*env)->NewStringUTF(env, name);
	if(GENERIC2TYPE(bcobj->gtype) == TYPE_INT) {
		//#putを検索する
		jmethodID symbol_table_put_id = (*env)->GetMethodID(env, symbol_table_cls, "putInteger", "(Ljava/lang/String;I)V");
		if(symbol_table_put_id == NULL) {
			(*env)->FatalError(env, "not found method: put");
			return;
		}
		(*env)->CallVoidMethod(env, target, symbol_table_put_id, keyj, ((jint)OBJ2INT(bcobj)));
	} else if(GENERIC2TYPE(bcobj->gtype) == TYPE_DOUBLE) {
		//#putを検索する
		jmethodID symbol_table_put_id = (*env)->GetMethodID(env, symbol_table_cls, "putDouble", "(Ljava/lang/String;D)V");
		if(symbol_table_put_id == NULL) {
			(*env)->FatalError(env, "not found method: put");
			return;
		}
		//(*env)->CallVoidMethod(env, target, symbol_table_put_id, keyj, ((jobject)OBJ2DOUBLE(bcobj)));
	} else if(GENERIC2TYPE(bcobj->gtype) == TYPE_CHAR) {
		//#putを検索する
		jmethodID symbol_table_put_id = (*env)->GetMethodID(env, symbol_table_cls, "putChar", "(Ljava/lang/String;C)V");
		if(symbol_table_put_id == NULL) {
			(*env)->FatalError(env, "not found method: put");
			return;
		}
		(*env)->CallVoidMethod(env, target, symbol_table_put_id, keyj, ((jchar)OBJ2CHAR(bcobj)));
	} else if(GENERIC2TYPE(bcobj->gtype) == TYPE_STRING) {
		//#putを検索する
		jmethodID symbol_table_put_id = (*env)->GetMethodID(env, symbol_table_cls, "putString", "(Ljava/lang/String;Ljava/lang/String;)V");
		if(symbol_table_put_id == NULL) {
			(*env)->FatalError(env, "not found method: put");
			return;
		}
		jstring str = (*env)->NewStringUTF(env, bc_string_raw(bcobj)->text);
		(*env)->CallVoidMethod(env, target, symbol_table_put_id, keyj, str);
	}
	//次の要素へ
	if(nmap->left != NULL) {
		bc_eval_write(env, nmap->left, fr, target);
	}
	if(nmap->right != NULL) {
		bc_eval_write(env, nmap->right, fr, target);
	}
}

static void bc_eval_release(class_loader* cll, frame* fr) {
	vm_catch(fr);
	heap_gc(heap_get());
	frame_delete(fr);
	sg_thread_release_frame_ref(sg_thread_current(script_context_get_current()));

	bc_error_last();
	class_loader_delete(cll);
}