#include "jp_koya_jbeacon_BCScriptContext.h"
#include "../../env/script_context.h"
#include "../../env/namespace.h"
#include <assert.h>

JNIEXPORT jobject JNICALL Java_jp_koya_jbeacon_BCScriptContext_nativeOpen(JNIEnv * env, jclass cls) {
	bc_ScriptContext* sctx = bc_OpenScriptContext();
	//エラーメッセージはスタックトレースに含めるので、
	//出力しない
	sctx->IsPrintError = false;
	//Javaに例外として伝えるので、
	//終了しない
	sctx->IsAbortOnError = false;
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
	bc_CloseScriptContext();
}