#include "bridge.h"
#include <stdbool.h>
#include "../../util/mem.h"
#include "config.h"

static bc_JavaBridge* gJava = NULL;
static bc_JavaBridge* new_bridge();
static void save_bridge(bc_JavaBridge* bridge);
static bc_JavaBridge* load_bridge();

bc_JavaBridge* bc_BridgeFromJava(JNIEnv* env) {
        bc_JavaBridge* temp = load_bridge();
        return NULL;
}

bc_JavaBridge* bc_GetJavaBridge() {
        //すでに存在するならそれを返す
        bc_JavaBridge* temp = load_bridge();
        if (temp != NULL) {
                return temp;
        }
        //有効なJNIのバージョンを列挙
        const int jni_version_len = 4;
        const int jni_versions[jni_version_len] = {
            JNI_VERSION_1_6,
            JNI_VERSION_1_4,
            JNI_VERSION_1_2,
            JNI_VERSION_1_1,
        };
        // JVMの引数を設定する
        JavaVM* jvm;
        JNIEnv* env;
        JavaVMInitArgs initArgs;
        bool supportedJNI = false;
        for (int i = 0; i < jni_version_len; i++) {
                initArgs.version = jni_versions[i];
                jint result = JNI_GetDefaultJavaVMInitArgs(&initArgs);
                //サポートされてる
                if (result >= 0) {
                        supportedJNI = true;
                        break;
                }
        }
        if (!supportedJNI) {
                fprintf(stderr, "failed for config of jvm\n");
                abort();
        }
        // JVMを起動する
        jint result = JNI_CreateJavaVM(&jvm, &env, &initArgs);
        if (result < 0) {
                fprintf(stderr, "failed for launch of jvm\n");
                abort();
        }
        //保存しておく
        bc_JavaBridge* bridge = new_bridge();
        bridge->Jvm = jvm;
        bridge->Env = env;
        bridge->Mode = JAVA_BRIDGE_FROM_SELF;
        save_bridge(bridge);
        return bridge;
}

// private
static bc_JavaBridge* new_bridge() {
        bc_JavaBridge* ret = MEM_MALLOC(sizeof(bc_JavaBridge));
        ret->Jvm = NULL;
        ret->Env = NULL;
        ret->Mode = JAVA_BRIDGE_FROM_NONE;
        return ret;
}

static void save_bridge(bc_JavaBridge* bridge) { gJava = bridge; }

static bc_JavaBridge* load_bridge() { return gJava; }