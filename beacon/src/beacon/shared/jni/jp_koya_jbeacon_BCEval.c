#include "jp_koya_jbeacon_BCEval.h"
#include "../../vm/eval.h"

JNIEXPORT void JNICALL Java_jp_koya_jbeacon_BCEval_nativeFile(JNIEnv * env, jclass cls, jstring str) {
	const char* str_c = (*env)->GetStringUTFChars(env, str, 0);
	eval_file(str_c);
	//https://stackoverflow.com/questions/23085044/jni-system-out-and-printf-behaviour
	fflush(stdout);
}

JNIEXPORT void JNICALL Java_jp_koya_jbeacon_BCEval_nativeString(JNIEnv * env, jclass cls, jstring str) {
	const char* str_c = (*env)->GetStringUTFChars(env, str, 0);
	eval_string(str_c);
	//https://stackoverflow.com/questions/23085044/jni-system-out-and-printf-behaviour
	fflush(stdout);
}