#include "jp_koya_jbeacon_BCEval.h"
#include "../../ast/ast.h"
#include "../../ast/ast_new_stmt.h"
#include "../../ast/ast_new_factor.h"
#include "../../ast/ast_new_literal.h"
#include "../../vm/eval.h"
#include "../../vm/frame.h"
#include "../../vm/vm.h"
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
static Frame* bc_eval_allocate(class_loader* cll);
static bool bc_read_symbol(JNIEnv* env, jobject table, AST* a);
static void bc_write_symbol(JNIEnv* env, NumericMap* nmap, Frame* fr, jobject target);
static void bc_eval_release(JNIEnv* env, class_loader* cll, Frame* fr);
static void printClassInfo(JNIEnv* env, jobject object);
static jint jobject2jint(JNIEnv* env, jobject obj);
static jchar jobject2jchar(JNIEnv* env, jobject obj);
static jboolean jobject2jboolean(JNIEnv* env, jobject obj);
static jdouble jobject2jdouble(JNIEnv* env, jobject obj);

JNIEXPORT jobject JNICALL Java_jp_koya_jbeacon_BCEval_nativeFile(JNIEnv * env, jclass cls, jstring str, jobject table) {
	const char* str_c = (*env)->GetStringUTFChars(env, str, 0);
	const char* source = ReadText(str_c);
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
	Parser* p = ParseString(source);
	if (p->Result != PARSE_COMPLETE_T) {
		ThrowBCError(BCERROR_PARSE_T, p->ErrorMessage);
		DestroyParser(p);
		jclass bc_compile_exc_cls = (*env)->FindClass(env, "jp/koya/jbeacon/BCCompileException");
		(*env)->ThrowNew(env, bc_compile_exc_cls, Ref2Str(GetBCErrorMessage()));
		return NULL;
	}
	AST* a = ReleaseParserAST(p);
	DestroyParser(p);
	//javaから beacon へインジェクションしようとしたが、
	//参照型をインジェクションしようとした場合
	if(!bc_read_symbol(env, table, a)) {
		DeleteAST(a);
		return NULL;
	}
	class_loader* cll = NewClassLoader(filename, CONTENT_ENTRY_POINT_T);
	LoadPassASTClassLoader(cll, a);
	if(GetLastBCError()) {
		DeleteClassLoader(cll);
		jclass bc_compile_exc_cls = (*env)->FindClass(env, "jp/koya/jbeacon/BCCompileException");
		(*env)->ThrowNew(env, bc_compile_exc_cls, Ref2Str(GetBCErrorMessage()));
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
	Frame* fr =  bc_eval_allocate(cll);
	bc_write_symbol(env, cll->env->Symboles->VariableMap->Left, fr, symbol_table_obj);
	bc_write_symbol(env, cll->env->Symboles->VariableMap->Right, fr, symbol_table_obj);
	bc_eval_release(env, cll, fr);
	//https://stackoverflow.com/questions/23085044/jni-system-out-and-printf-behaviour
	fflush(stdout);
	return symbol_table_obj;
}

static Frame* bc_eval_allocate(class_loader* cll) {
	ScriptContext* ctx = GetCurrentScriptContext();
	Frame* fr = NewFrame();
	SetSGThreadFrameRef(GetCurrentSGThread(GetCurrentScriptContext()), fr);
	Heap* he = GetHeap();
	he->AcceptBlocking = 0;
	if(!GetLastBCError()) {
		ExecuteVM(fr, cll->env);
	}
	if(fr->IsTerminate) {
		ThrowBCError(BCERROR_GENERIC_T, "unexpected terminate");
	}
	return fr;
}

static bool bc_read_symbol(JNIEnv* env, jobject table, AST* a) {
	if(table == NULL) {
		return true;
	}
	//jp.koya.jbeacon.SymbolTableを検索する
	jclass symbol_table_cls = (*env)->FindClass(env, "jp/koya/jbeacon/SymbolTable");
	if(symbol_table_cls == NULL) {
		(*env)->FatalError(env, "not found class: jp/koya/jbeacon/SymbolTable");
		return false;
	}
	//#keys を検索する
	jmethodID symbol_table_keys_id = (*env)->GetMethodID(env, symbol_table_cls, "getKeys", "()[Ljava/lang/String;");
	if(symbol_table_keys_id == NULL) {
		(*env)->FatalError(env, "not found method: getKeys");
		return false;
	}
	//#get を検索する
	jmethodID symbol_table_get_id = (*env)->GetMethodID(env, symbol_table_cls, "get", "(Ljava/lang/String;)Ljava/lang/Object;");
	if(symbol_table_get_id == NULL) {
		(*env)->FatalError(env, "not found method: get");
		return false;
	}
	jobjectArray keys_array = (jobjectArray)((*env)->CallObjectMethod(env, table, symbol_table_keys_id));
	if(keys_array == NULL) {
		(*env)->FatalError(env, "null pointer: getKeys");
		return false;
	}
	//プリミティブ型をロード
	jclass integer_cls = (*env)->FindClass(env, "java/lang/Integer");
	jclass double_cls = (*env)->FindClass(env, "java/lang/Double");
	jclass char_cls = (*env)->FindClass(env, "java/lang/Character");
	jclass string_cls = (*env)->FindClass(env, "java/lang/String");
	jclass bool_cls = (*env)->FindClass(env, "java/lang/Boolean");
	if(integer_cls == NULL ||
	   double_cls == NULL ||
	   char_cls == NULL ||
	   string_cls == NULL ||
	   bool_cls == NULL) {
		(*env)->FatalError(env, "not found class: Integer/Double/Char/String/Boolean");
		return false;
	}
	//Javaのデータを beacon のデータへ変換
	int len = (*env)->GetArrayLength(env, keys_array);
	for(int i=0; i<len; i++) {
		jstring keyE = (jstring)((*env)->GetObjectArrayElement(env, keys_array, i));
		jobject valueE = (*env)->CallObjectMethod(env, table, symbol_table_get_id, keyE);
		const char *keystr = (*env)->GetStringUTFChars(env, keyE, JNI_FALSE);
		StringView keyv = InternString(keystr);
		if(valueE == NULL) {
			(*env)->FatalError(env, "null pointer: get");
			return false;
		}
		AST* astmt = NULL;
		if((*env)->IsInstanceOf(env, valueE, integer_cls) == JNI_TRUE) {
			astmt = NewASTInject(keyv, NewASTInt(jobject2jint(env, valueE)));
		} else if((*env)->IsInstanceOf(env, valueE, double_cls) == JNI_TRUE) {
			astmt = NewASTInject(keyv, NewASTDouble(jobject2jdouble(env, valueE)));
		} else if((*env)->IsInstanceOf(env, valueE, char_cls) == JNI_TRUE) {
			astmt = NewASTInject(keyv, NewASTChar(jobject2jchar(env, valueE)));
		} else if((*env)->IsInstanceOf(env, valueE, bool_cls) == JNI_TRUE) {
			astmt = NewASTInject(keyv, NewASTBool(jobject2jboolean(env, valueE)));
		} else if((*env)->IsInstanceOf(env, valueE, string_cls) == JNI_TRUE) {
			jstring valuej = (jstring)valueE;
			const char *valuestr = (*env)->GetStringUTFChars(env, valuej, JNI_FALSE);
			StringView valuev = InternString(valuestr);
			astmt = NewASTInject(keyv, NewASTString(valuev));
		//それ以外はまだ未対応
		} else {
			jclass bc_not_supported_exc_cls = (*env)->FindClass(env, "jp/koya/jbeacon/BCNotSupportedException");
			(*env)->ThrowNew(env, bc_not_supported_exc_cls, "not supported inject of reference type");
			return false;
		}
		InsertVector(a->Children, 0, astmt);
	}
	return true;
}

static void bc_write_symbol(JNIEnv* env, NumericMap* nmap, Frame* fr, jobject target) {
	if(nmap == NULL) {
		return;
	}
	NumericMapKey key = nmap->Key;
	NumericMapItem val = nmap->Item;
	const char* name = Ref2Str(key);
	SymbolEntry* se = (SymbolEntry*)val;
	object* bcobj = AtVector(fr->VariableTable, se->Index);
	//jp.koya.jbeacon.SymbolTableを検索する
	jclass symbol_table_cls = (*env)->FindClass(env, "jp/koya/jbeacon/SymbolTable");
	if(symbol_table_cls == NULL) {
		(*env)->FatalError(env, "not found class: jp/koya/jbeacon/SymbolTable");
		return;
	}
	//jp.koya.jbeacon.BCObjectを検索する
	jclass bcobject_cls = (*env)->FindClass(env, "jp/koya/jbeacon/BCObject");
	if(bcobject_cls == NULL) {
		(*env)->FatalError(env, "not found class: jp/koya/jbeacon/BCObjec");
		return;
	}
	jmethodID bcobject_ctor_id = (*env)->GetMethodID(env, bcobject_cls, "<init>", "()V");
	if(bcobject_ctor_id == NULL) {
		(*env)->FatalError(env, "not found method: <init>");
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
		(*env)->CallVoidMethod(env, target, symbol_table_put_id, keyj, ((jdouble)OBJ2DOUBLE(bcobj)));
	} else if(GENERIC2TYPE(bcobj->gtype) == TYPE_CHAR) {
		//#putを検索する
		jmethodID symbol_table_put_id = (*env)->GetMethodID(env, symbol_table_cls, "putCharacter", "(Ljava/lang/String;C)V");
		if(symbol_table_put_id == NULL) {
			(*env)->FatalError(env, "not found method: put");
			return;
		}
		(*env)->CallVoidMethod(env, target, symbol_table_put_id, keyj, ((jchar)OBJ2CHAR(bcobj)));
	} else if(GENERIC2TYPE(bcobj->gtype) == TYPE_BOOL) {
		//#putを検索する
		jmethodID symbol_table_put_id = (*env)->GetMethodID(env, symbol_table_cls, "putBoolean", "(Ljava/lang/String;Z)V");
		if(symbol_table_put_id == NULL) {
			(*env)->FatalError(env, "not found method: put");
			return;
		}
		(*env)->CallVoidMethod(env, target, symbol_table_put_id, keyj, ((jboolean)OBJ2BOOL(bcobj)));
	} else if(GENERIC2TYPE(bcobj->gtype) == TYPE_STRING) {
		//#putを検索する
		jmethodID symbol_table_put_id = (*env)->GetMethodID(env, symbol_table_cls, "putString", "(Ljava/lang/String;Ljava/lang/String;)V");
		if(symbol_table_put_id == NULL) {
			(*env)->FatalError(env, "not found method: put");
			return;
		}
		jstring str = (*env)->NewStringUTF(env, GetRawBCString(bcobj)->Text);
		(*env)->CallVoidMethod(env, target, symbol_table_put_id, keyj, str);
	//それ以外の型はとりあえず BCObject へ変換する
	} else {
		//#putを検索する
		jmethodID symbol_table_put_id = (*env)->GetMethodID(env, symbol_table_cls, "put", "(Ljava/lang/String;Ljava/lang/Object;)V");
		if(symbol_table_put_id == NULL) {
			(*env)->FatalError(env, "not found method: put");
			return;
		}
		jobject other = (*env)->NewObject(env, bcobject_cls, bcobject_ctor_id);
		(*env)->CallVoidMethod(env, target, symbol_table_put_id, keyj, other);
	}
	//次の要素へ
	if(nmap->Left != NULL) {
		bc_write_symbol(env, nmap->Left, fr, target);
	}
	if(nmap->Right != NULL) {
		bc_write_symbol(env, nmap->Right, fr, target);
	}
}

static void bc_eval_release(JNIEnv* env, class_loader* cll, Frame* fr) {
	if(GetLastBCError()) {
		Buffer* sbuf = NewBuffer();
		AppendsBuffer(sbuf, "\n");
		AppendsBuffer(sbuf, Ref2Str(GetVMErrorMessage()));
		char* mes = ReleaseBuffer(sbuf);
		jclass bc_runtime_exc_cls = (*env)->FindClass(env, "jp/koya/jbeacon/BCRuntimeException");
		(*env)->ThrowNew(env, bc_runtime_exc_cls, mes);
		MEM_FREE(mes);
	}
	CatchVM(fr);
	CollectHeap(GetHeap());
	DeleteFrame(fr);
	ReleaseSGThreadFrameRef(GetCurrentSGThread(GetCurrentScriptContext()));

	GetLastBCError();
	DeleteClassLoader(cll);
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

//https://stackoverflow.com/questions/29255023/jni-trouble-converting-java-double-to-jdouble
static jint jobject2jint(JNIEnv* env, jobject obj) {
	//Integerクラスを検索
	jclass integer_cl = (*env)->FindClass(env, "java/lang/Integer");
	if(integer_cl == NULL) {
		(*env)->FatalError(env, "not found class: java/lang/Integer");
		return 0;
	}
    jmethodID int_value_id = (*env)->GetMethodID(env,integer_cl, "intValue", "()I" );
	if(int_value_id == NULL) {
		(*env)->FatalError(env, "not found method: intValue");
		return 0;
	}
	return (*env)->CallIntMethod(env, obj, int_value_id);
}

static jchar jobject2jchar(JNIEnv* env, jobject obj) {
	//Characterクラスを検索
	jclass character_cl = (*env)->FindClass(env, "java/lang/Character");
	if(character_cl == NULL) {
		(*env)->FatalError(env, "not found class: java/lang/Character");
		return 0;
	}
    jmethodID char_value_id = (*env)->GetMethodID(env,character_cl, "charValue", "()C" );
	if(char_value_id == NULL) {
		(*env)->FatalError(env, "not found method: charValue");
		return 0;
	}
	return (*env)->CallCharMethod(env, obj, char_value_id);
}

static jboolean jobject2jboolean(JNIEnv* env, jobject obj) {
	//Booleanクラスを検索
	jclass boolean_cl = (*env)->FindClass(env, "java/lang/Boolean");
	if(boolean_cl == NULL) {
		(*env)->FatalError(env, "not found class: java/lang/Boolean");
		return 0;
	}
    jmethodID boolean_value_id = (*env)->GetMethodID(env,boolean_cl, "booleanValue", "()Z" );
	if(boolean_value_id == NULL) {
		(*env)->FatalError(env, "not found method: booleanValue");
		return 0;
	}
	return (*env)->CallBooleanMethod(env, obj, boolean_value_id);
}

static jdouble jobject2jdouble(JNIEnv* env, jobject obj) {
	//Doubleクラスを検索
	jclass double_cl = (*env)->FindClass(env, "java/lang/Double");
	if(double_cl == NULL) {
		(*env)->FatalError(env, "not found class: java/lang/Double");
		return 0;
	}
    jmethodID double_value_id = (*env)->GetMethodID(env,double_cl, "doubleValue", "()D" );
	if(double_value_id == NULL) {
		(*env)->FatalError(env, "not found method: doubleValue");
		return 0;
	}
	return (*env)->CallDoubleMethod(env, obj, double_value_id);
}