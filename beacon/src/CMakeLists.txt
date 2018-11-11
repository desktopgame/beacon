cmake_minimum_required(VERSION 2.8)
project(beacon C)
#あなたのインクルードパスを設定
set(CMAKE_CXX_COMPILER clang)
set(JNI_INCLUDE_DIR "" CACHE FILEPATH "Path to jni")
set(JNI_NATIVE_INCLUDE_DIR "" CACHE FILEPATH "Path to jni native")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
include_directories(${JNI_INCLUDE_DIR} ${JNI_NATIVE_INCLUDE_DIR})
add_subdirectory("beacon")
add_executable(a.out "beacon/main.c")
target_link_libraries(a.out
    "lib__beacon_util"
    "lib__beacon_parse"
    "lib__beacon_shared_jni"
    "lib__beacon_env_type"
    "lib__beacon_env_cll"
    "lib__beacon_env"
    "lib__beacon_vm"
    "lib__beacon_lib_beacon_lang_unsafe"
    "lib__beacon_lib_beacon_lang"
    "lib__beacon_ast"
    "lib__beacon_il_stmt"
    "lib__beacon_il_factor_unary"
    "lib__beacon_il_factor_variable"
    "lib__beacon_il_factor_invoke"
    "lib__beacon_il_factor_binary"
    "lib__beacon_il_factor"
    "lib__beacon_il_type"
    "lib__beacon_il"
    "lib__beacon_thread"
    "lib__beacon"
)
