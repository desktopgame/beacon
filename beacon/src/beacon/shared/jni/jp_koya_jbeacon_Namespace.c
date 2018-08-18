#include "jp_koya_jbeacon_Namespace.h"
#include "../../env/namespace.h"

JNIEXPORT jobject JNICALL Java_jp_koya_jbeacon_Namespace_nativeGetNamespace(JNIEnv * env, jobject self, jstring name) {
	const char* name_c = (*env)->GetStringUTFChars(env, name, 0);
	//jp.koya.jbeacon.Namespace
	jclass namespace_cls = (*env)->FindClass(env, "jp/koya/jbeacon/Namespace");
	if(namespace_cls == NULL) {
		(*env)->FatalError(env, "not found class: jp/koya/jbeacon/Namespace");
		return NULL;
	}
	//Namespace#cptr
	jfieldID cptr_field_id = (*env)->GetFieldID(env, namespace_cls, "cptr", "[B");
	if(namespace_cls == NULL) {
		(*env)->FatalError(env, "not found field: cptr");
		return NULL;
	}
	jobject cptr_obj = (*env)->GetObjectField(env, self, cptr_field_id);
	if(cptr_obj == NULL) {
		(*env)->FatalError(env, "not found field: cptr");
		return NULL;
	}
	//C側で子要素を検索する
	void* buffer = NULL;
	(*env)->GetByteArrayRegion(env, cptr_obj, 0, sizeof(buffer), (jbyte*)&buffer);
	namespace_* ns = (namespace_*)buffer;
	namespace_* child = namespace_get_namespace(ns, string_pool_intern(name_c));
	if(child == NULL) {
		return NULL;
	}
	//コンストラクタを検索
	jmethodID namespace_ctor_id = (*env)->GetMethodID(env, namespace_cls, "<init>", "(Ljava/lang/String;[B)V");
	if(namespace_ctor_id == NULL) {
		(*env)->FatalError(env, "not found method: <init>");
		return NULL;
	}
	//コンストラクタを実行
	void* buffer2 = (void*)child;
	jbyteArray pointer = (*env)->NewByteArray(env, sizeof(void*));
    (*env)->SetByteArrayRegion(env, pointer, 0, sizeof(void*), (jbyte*)&buffer2);
	jobject ret = (*env)->NewObject(env, namespace_cls, namespace_ctor_id, name, pointer);
	return ret;
}