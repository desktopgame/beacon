#include "jp_koya_jbeacon_Beacon.h"
#include "../../util/string_pool.h"
#include "../../vm/eval.h"

JNIEXPORT void JNICALL Java_jp_koya_jbeacon_Beacon_nativeInit(JNIEnv * env, jclass cls) {
	string_pool_init();
}

JNIEXPORT void JNICALL Java_jp_koya_jbeacon_Beacon_nativeExecute(JNIEnv * env, jclass cls, jstring name) {
	const char* name_c = (*env)->GetStringUTFChars(env, name, 0);
	eval_file(name_c);
}

JNIEXPORT void JNICALL Java_jp_koya_jbeacon_Beacon_nativeDestroy(JNIEnv * env, jclass cls) {
	string_pool_destroy();
}