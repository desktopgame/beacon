cmake_minimum_required(VERSION 2.8)
project(beacon C)
#あなたのインクルードパスを設定
set(CMAKE_CXX_COMPILER clang)
set(JNI_INCLUDE_DIR "/Library/Java/JavaVirtualMachines/jdk1.8.0_151.jdk/Contents/Home/include" CACHE PATH "Path to jni include")
set(JNI_NATIVE_INCLUDE_DIR "/Library/Java/JavaVirtualMachines/jdk1.8.0_151.jdk/Contents/Home/include/darwin" CACHE PATH "Path to jni native include")
set(GLIB_INCLUDE_DIR "/usr/local/Cellar/glib/2.58.1/include/glib-2.0" CACHE PATH "Path to glib include")
set(GLIB_NATIVE_INCLUDE_DIR "/usr/local/Cellar/glib/2.58.1/lib/glib-2.0/include" CACHE PATH "Path to glib native include")
set(GLIB_LIBRARY_DIR "/usr/local/Cellar/glib/2.58.1/lib" CACHE PATH "Path to glib library")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
enable_testing()
add_test(
    NAME test
    COMMAND ruby auto/test.rb
    #CONFIGURATIONS Debug
    WORKING_DIRECTORY .
)
include_directories(${JNI_INCLUDE_DIR} ${JNI_NATIVE_INCLUDE_DIR} ${GLIB_INCLUDE_DIR} ${GLIB_NATIVE_INCLUDE_DIR})
link_directories (${GLIB_LIBRARY_DIR})
set(BC_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/beacon CACHE PATH "Path to install")
install(
    DIRECTORY ./../bin
    DESTINATION ${BC_INSTALL_DIR}
)
install(
    DIRECTORY ./../doc
    DESTINATION ${BC_INSTALL_DIR}
)
install(
    DIRECTORY ./../../license
    DESTINATION ${BC_INSTALL_DIR}
)
install(
    FILES ./../../README.md ./../../changelog.md
    DESTINATION ${BC_INSTALL_DIR}
)
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
