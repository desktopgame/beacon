#ifndef BEACON_JNI_BRIDGE_H
#define BEACON_JNI_BRIDGE_H
#include <jni.h>

typedef enum bc_JavaBridgeMode {
        JAVA_BRIDGE_FROM_NONE,
        JAVA_BRIDGE_FROM_SELF,
        JAVA_BRIDGE_FROM_JAVA,
} bc_JavaBridgeMode;

typedef struct bc_JavaBridge {
        JNIEnv* Env;
        JavaVM* Jvm;
        bc_JavaBridgeMode Mode;
} bc_JavaBridge;

bc_JavaBridge* bc_BridgeFromJava(JNIEnv* env);

bc_JavaBridge* bc_GetJavaBridge();
#endif