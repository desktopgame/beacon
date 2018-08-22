#include "jp_koya_jbeacon_BCEval.h"
#include "../../ast/ast.h"
#include "../../ast/ast_new_stmt.h"
#include "../../ast/ast_new_literal.h"
#include "../../vm/eval.h"
#include "../../vm/frame.h"
#include "../../vm/symbol_entry.h"
#include "../../env/heap.h"
#include "../../env/script_context.h"
#include "../../env/class_loader.h"
#include "../../env/namespace.h"
#include "../../env/generic_type.h"
#include "../../thread/thread.h"
#include "../../util/io.h"
#include "../../util/mem.h"
#include "../../parse/parser.h"
#include "../../lib/beacon/lang/bc_string.h"
#include "../../error.h"

static jobject bc_eval_string(JNIEnv * env, jclass cls, jstring str, jobject table, const char* filename, const char* source);
static frame* bc_eval_allocate(class_loader* cll);
static void bc_read_symbol(JNIEnv* env, jobject table, ast* a);
static void bc_write_symbol(JNIEnv* env, numeric_map* nmap, frame* fr, jobject target);
static void bc_eval_release(JNIEnv* env, class_loader* cll, frame* fr);
static void printClassInfo(JNIEnv* env, jobject object);

JNIEXPORT jobject JNICALL Java_jp_koya_jbeacon_BCEval_nativeFile(JNIEnv * env, jclass cls, jstring str, jobject table) {
	const char* str_c = (*env)->GetStringUTFChars(env, str, 0);
	const char* source = io_read_text(str_c);
	jobject ret = bc_eval_string(env, cls, str, table, str_c, source);
	MEM_FREE(source);
	return ret;
}

JNIEXPORT jobject JNICALL Java_jp_koya_jbeacon_BCEval_nativeString(JNIEnv * env, jclass cls, jstring str, jobject table) {
	const char* str_c = (*env)->GetStringUTFChars(env, str, 0);
	return bc_eval_string(env, cls, str, table, "string", str_c);
}
//private
static jobject bc_eval_string(JNIEnv * env, jclass cls, jstring str, jobject table, const char* filename, const char* source) {
	//文字列を解析
	parser* p = parse_string(source);
	if (p->result != parse_complete_T) {
		bc_error_throw(bcerror_parse_T, p->error_message);
		parser_destroy(p);
		jclass bc_compile_exc_cls = (*env)->FindClass(env, "jp/koya/jbeacon/BCCompileException");
		(*env)->ThrowNew(env, bc_compile_exc_cls, string_pool_ref2str(bc_error_message()));
		return NULL;
	}
	ast* a = parser_release_ast(p);
	parser_destroy(p);
	bc_read_symbol(env, table, a);
	class_loader* cll = class_loader_new(filename, content_entry_point_T);
	class_loader_load_pass_ast(cll, a);
	if(bc_error_last()) {
		class_loader_delete(cll);
		jclass bc_compile_exc_cls = (*env)->FindClass(env, "jp/koya/jbeacon/BCCompileException");
		(*env)->ThrowNew(env, bc_compile_exc_cls, string_pool_ref2str(bc_error_message()));
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
	bc_write_symbol(env, cll->env->sym_table->map->left, fr, symbol_table_obj);
	bc_write_symbol(env, cll->env->sym_table->map->right, fr, symbol_table_obj);
	bc_eval_release(env, cll, fr);
	//https://stackoverflow.com/questions/23085044/jni-system-out-and-printf-behaviour
	fflush(stdout);
	return symbol_table_obj;
}

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

static void bc_read_symbol(JNIEnv* env, jobject table, ast* a) {
	if(table == NULL) {
		return;
	}
	//jp.koya.jbeacon.SymbolTableを検索する
	jclass symbol_table_cls = (*env)->FindClass(env, "jp/koya/jbeacon/SymbolTable");
	if(symbol_table_cls == NULL) {
		(*env)->FatalError(env, "not found class: jp/koya/jbeacon/SymbolTable");
		return;
	}
	//#keys を検索する
	jmethodID symbol_table_keys_id = (*env)->GetMethodID(env, symbol_table_cls, "getKeys", "()[Ljava/lang/String;");
	if(symbol_table_keys_id == NULL) {
		(*env)->FatalError(env, "not found method: getKeys");
		return;
	}
	//#get を検索する
	jmethodID symbol_table_get_id = (*env)->GetMethodID(env, symbol_table_cls, "get", "(Ljava/lang/String;)Ljava/lang/Object;");
	if(symbol_table_get_id == NULL) {
		(*env)->FatalError(env, "not found method: get");
		return;
	}
	jobjectArray keys_array = (jobjectArray)((*env)->CallObjectMethod(env, table, symbol_table_keys_id));
	if(keys_array == NULL) {
		(*env)->FatalError(env, "null pointer: getKeys");
		return;
	}
	jclass integer_cls = (*env)->FindClass(env, "java/lang/Integer");
	jclass double_cls = (*env)->FindClass(env, "java/lang/Double");
	jclass char_cls = (*env)->FindClass(env, "java/lang/Character");
	jclass string_cls = (*env)->FindClass(env, "java/lang/String");
	if(integer_cls == NULL ||
	   double_cls == NULL ||
	   char_cls == NULL ||
	   string_cls == NULL) {
		(*env)->FatalError(env, "not found class: Integer/Double/Char/String");
		return;
	}
	int len = (*env)->GetArrayLength(env, keys_array);
	for(int i=0; i<len; i++) {
		jstring keyE = (jstring)((*env)->GetObjectArrayElement(env, keys_array, i));
		jobject valueE = (*env)->CallObjectMethod(env, table, symbol_table_get_id, keyE);
		const char *keystr = (*env)->GetStringUTFChars(env, keyE, JNI_FALSE);
		string_view keyv = string_pool_intern(keystr);
		if(valueE == NULL) {
			(*env)->FatalError(env, "null pointer: get");
			return;
		}
		ast* astmt = NULL;
		if((*env)->IsInstanceOf(env, valueE, integer_cls)) {
			astmt = ast_new_inject(keyv, ast_new_int((jint)valueE));
		} else if((*env)->IsInstanceOf(env, valueE, double_cls)) {
			//astmt = ast_new_inject(keyv, ast_new_double((jdouble)valueE));
		} else if((*env)->IsInstanceOf(env, valueE, char_cls)) {
			astmt = ast_new_inject(keyv, ast_new_char((jint)valueE));
		} else if((*env)->IsInstanceOf(env, valueE, string_cls)) {
			jstring valuej = (jstring)valueE;
			const char *valuestr = (*env)->GetStringUTFChars(env, valuej, JNI_FALSE);
			string_view valuev = string_pool_intern(valuestr);
			astmt = ast_new_inject(keyv, ast_new_string(valuev));
			(*env)->ReleaseStringUTFChars(env, valuej, valuestr);
		}
		(*env)->ReleaseStringUTFChars(env, keyE, keystr);
		vector_insert(a->vchildren, 0, astmt);
	}
}

static void bc_write_symbol(JNIEnv* env, numeric_map* nmap, frame* fr, jobject target) {
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
		bc_write_symbol(env, nmap->left, fr, target);
	}
	if(nmap->right != NULL) {
		bc_write_symbol(env, nmap->right, fr, target);
	}
}

static void bc_eval_release(JNIEnv* env, class_loader* cll, frame* fr) {
	if(bc_error_last()) {
		jclass bc_runtime_exc_cls = (*env)->FindClass(env, "jp/koya/jbeacon/BCRuntimeException");
		(*env)->ThrowNew(env, bc_runtime_exc_cls, string_pool_ref2str(bc_error_message()));
	}
	vm_catch(fr);
	heap_gc(heap_get());
	frame_delete(fr);
	sg_thread_release_frame_ref(sg_thread_current(script_context_get_current()));

	bc_error_last();
	class_loader_delete(cll);
}

//https://stackoverflow.com/questions/12719766/can-i-know-the-name-of-the-class-that-calls-a-jni-c-method
static void printClassInfo(JNIEnv* env, jobject obj) {
	jclass cls = (*env)->GetObjectClass(env, obj);
	if (cls == NULL) {
		printf("cls obj is null");
	}
	// First get the class object
	jmethodID mid = (*env)->GetMethodID(env, cls, "getClass", "()Ljava/lang/Class;");
	jobject clsObj = (*env)->CallObjectMethod(env, obj, mid);

	// Now get the class object's class descriptor
	cls = (*env)->GetObjectClass(env, clsObj);

	// Find the getName() method on the class object
	mid = (*env)->GetMethodID(env, cls, "getName", "()Ljava/lang/String;");

	// Call the getName() to get a jstring object back
	jstring strObj = (jstring)(*env)->CallObjectMethod(env, clsObj, mid);

	// Now get the c string from the java jstring object
	const char* str = (*env)->GetStringUTFChars(env, strObj, NULL);

	// Print the class name
	printf("\nCalling class is: %s\n", str);

	// Release the memory pinned char array
	(*env)->ReleaseStringUTFChars(env, strObj, str);
}