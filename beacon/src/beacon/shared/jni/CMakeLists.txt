set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
add_library("lib__beacon_shared_jni" STATIC
    "jp_koya_jbeacon_Beacon.c"
    "jp_koya_jbeacon_BCEval.c"
    "jp_koya_jbeacon_Beacon_State.c"
    "jp_koya_jbeacon_BCScriptContext.c"
)
