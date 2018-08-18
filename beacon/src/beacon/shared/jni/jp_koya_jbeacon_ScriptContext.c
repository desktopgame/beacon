#include "jp_koya_jbeacon_ScriptContext.h"
#include "../../env/script_context.h"

JNIEXPORT jobject JNICALL Java_jp_koya_jbeacon_ScriptContext_nativeOpen(JNIEnv * env, jclass cls) {
	script_context* sctx = script_context_open();
	//jp.koya.jbeacon.ScriptContextクラスを取得
	jclass scontext_cls = (*env)->FindClass(env, "jp/koya/jbeacon/ScriptContext");
	if(scontext_cls == NULL) {
		(*env)->FatalError(env, "not found class: jp/koya/jbeacon/ScriptContext");
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

JNIEXPORT void JNICALL Java_jp_koya_jbeacon_ScriptContext_nativeClose(JNIEnv * env, jclass cls) {
	script_context_close();
}