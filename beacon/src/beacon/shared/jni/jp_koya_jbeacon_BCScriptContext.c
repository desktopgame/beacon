#include "jp_koya_jbeacon_BCScriptContext.h"
#include "../../env/script_context.h"
#include "../../env/namespace.h"
#include <assert.h>

static void bc_load_namespace(JNIEnv * env, jobject obj, numeric_map* parent);


JNIEXPORT jobject JNICALL Java_jp_koya_jbeacon_BCScriptContext_nativeOpen(JNIEnv * env, jclass cls) {
	script_context* sctx = script_context_open();
	//jp.koya.jbeacon.BCScriptContextクラスを取得
	jclass scontext_cls = (*env)->FindClass(env, "jp/koya/jbeacon/BCScriptContext");
	if(scontext_cls == NULL) {
		(*env)->FatalError(env, "not found class: jp/koya/jbeacon/BCScriptContext");
		return NULL;
	}
	//コンストラクタを検索
	jmethodID scontext_ctor_id = (*env)->GetMethodID(env, scontext_cls, "<init>", "([B)V");
	if(scontext_ctor_id == NULL) {
		(*env)->FatalError(env, "not found method: <init>");
		return NULL;
	}
	//コンストラクタを実行
	jbyteArray pointer = (*env)->NewByteArray(env, sizeof(void*));
    (*env)->SetByteArrayRegion(env, pointer, 0, sizeof(void*), (jbyte*)&sctx);
	return (*env)->NewObject(env, scontext_cls, scontext_ctor_id, pointer);
}

JNIEXPORT void JNICALL Java_jp_koya_jbeacon_BCScriptContext_nativeClose(JNIEnv * env, jclass cls) {
	script_context_close();
}

JNIEXPORT jobject JNICALL Java_jp_koya_jbeacon_BCScriptContext_nativeGetRootNamespace(JNIEnv * env, jobject self, jstring name) {
	const char* name_c = (*env)->GetStringUTFChars(env, name, 0);
	namespace_* ns = namespace_get_at_root(string_pool_intern(name_c));
	if(ns == NULL) {
		return NULL;
	}
	//jp.koya.jbeacon.Namespace
	jclass namespace_cls = (*env)->FindClass(env, "jp/koya/jbeacon/BCNamespace");
	if(namespace_cls == NULL) {
		(*env)->FatalError(env, "not found class: jp/koya/jbeacon/BCNamespace");
		return NULL;
	}
	//コンストラクタを検索
	jmethodID namespace_ctor_id = (*env)->GetMethodID(env, namespace_cls, "<init>", "(Ljava/lang/String;[B)V");
	if(namespace_ctor_id == NULL) {
		(*env)->FatalError(env, "not found method: <init>");
		return NULL;
	}
	//コンストラクタを実行
	void* buffer = (void*)ns;
	jbyteArray pointer = (*env)->NewByteArray(env, sizeof(void*));
    (*env)->SetByteArrayRegion(env, pointer, 0, sizeof(void*), (jbyte*)&buffer);
	jobject ret = (*env)->NewObject(env, namespace_cls, namespace_ctor_id, name, pointer);
	bc_load_namespace(env, ret, ns->namespace_map->left);
	bc_load_namespace(env, ret, ns->namespace_map->right);
	return ret;
}
//private
static void bc_load_namespace(JNIEnv * env, jobject obj, numeric_map* parent) {
	if(parent == NULL) {
		return;
	}
	numeric_key key = parent->key;
	numeric_map_item item = parent->item;
	const char* keystr = string_pool_ref2str(key);
	jstring keyjstr = (*env)->NewStringUTF(env, keystr);
	namespace_* ns = (namespace_*)item;
	//jp.koya.jbeacon.Namespace
	jclass namespace_cls = (*env)->FindClass(env, "jp/koya/jbeacon/BCNamespace");
	if(namespace_cls == NULL) {
		(*env)->FatalError(env, "not found class: jp/koya/jbeacon/BCNamespace");
		return;
	}
	//コンストラクタを検索
	jmethodID namespace_ctor_id = (*env)->GetMethodID(env, namespace_cls, "<init>", "(Ljava/lang/String;[B)V");
	if(namespace_ctor_id == NULL) {
		(*env)->FatalError(env, "not found method: <init>");
		return;
	}
	//コンストラクタを実行
	void* buffer = (void*)ns;
	jbyteArray pointer = (*env)->NewByteArray(env, sizeof(void*));
    (*env)->SetByteArrayRegion(env, pointer, 0, sizeof(void*), (jbyte*)&buffer);
	jobject child = (*env)->NewObject(env, namespace_cls, namespace_ctor_id, keyjstr, pointer);
	assert(child != NULL);
	//Namespaceの持つマップへ登録する
	jfieldID namespace_nmap_id = (*env)->GetFieldID(env, namespace_cls, "namespaceMap", "Ljava/util/Map;");
	if(namespace_nmap_id == NULL) {
		(*env)->FatalError(env, "not found field: namespaceMap");
		return;
	}
	//Map#putを取得する
	jclass map_id = (*env)->FindClass(env, "java/util/HashMap");
	if(map_id == NULL) {
		(*env)->FatalError(env, "not found class: HashMap");
		return;
	}
	jmethodID map_put_id = (*env)->GetMethodID(env, map_id, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
	if(map_put_id == NULL) {
		(*env)->FatalError(env, "not found method: put");
		return;
	}
	(*env)->CallObjectMethod(env, obj, map_put_id, keyjstr, child);
	bc_load_namespace(env, obj, parent->left);
	bc_load_namespace(env, obj, parent->right);
}