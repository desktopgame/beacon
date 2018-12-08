cmake_minimum_required(VERSION 2.8)
project(beacon C)
#JNIのパスを検索
find_package(JNI)
message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
message (STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")
#GLIBのパスを検索
find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)
message (STATUS "GLIB_INCLUDE_DIRS=${GLIB_INCLUDE_DIRS}")
message (STATUS "GLIB_LIBRARIES=${GLIB_LIBRARIES}")

set(CMAKE_CXX_COMPILER clang)
set(GLIB_INCLUDE_DIR "/usr/local/Cellar/glib/2.58.1/include/glib-2.0" CACHE PATH "Path to glib include")
set(GLIB_NATIVE_INCLUDE_DIR "/usr/local/Cellar/glib/2.58.1/lib/glib-2.0/include" CACHE PATH "Path to glib native include")
set(GLIB_LIBRARY_DIR "/usr/local/Cellar/glib/2.58.1/lib" CACHE PATH "Path to glib library")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
set(BC_EXECUTABLE "beacon" CACHE STRING "executable file name")
enable_testing()
add_test(
    NAME test
    COMMAND ruby auto/test.rb
    #CONFIGURATIONS Debug
    WORKING_DIRECTORY .
)
include_directories(${JNI_INCLUDE_DIRS} ${GLIB_INCLUDE_DIRS})
link_directories (${GLIB_LIBRARIES})
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
add_executable(${BC_EXECUTABLE} "beacon/main.c")
target_link_libraries(${BC_EXECUTABLE}
    "${GLIB_LDFLAGS}"
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
