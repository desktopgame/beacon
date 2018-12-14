cmake_minimum_required(VERSION 2.8)
project(beacon C)
#各種変数の設定
set(CMAKE_CXX_COMPILER clang)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
set(BC_EXECUTABLE "beacon" CACHE STRING "executable file name")
set(BC_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/beacon CACHE PATH "Path to install")
set(BC_IGNORE_COMPILE "CMakeCCompilerId.c" "feature_tests.c")
set(BC_LINK_JAVA false CACHE bool "if call java from beacon, set a true.")

#Windowsの場合
if (WIN32)
    set(GLIB_LIBRARY_DIRS "" CACHE PATH "glib library dirs")
    set(GLIB_INCLUDE_DIRS "" CACHE PATH "glib include dirs")
    set(GLIB_LIBRARIES "" CACHE FILEPATH "glib libraries")
    set(JNI_LIBRARY_DIRS "" CACHE PATH "jni library dirs")
    set(JNI_INCLUDE_DIRS "" CACHE PATH "jni include dirs")
    set(JNI_LIBRARIES "" CACHE FILEPATH "jni libraries")
#それ以外
else()
    find_package(PkgConfig REQUIRED)
    find_package(JNI)
    pkg_check_modules(GLIB REQUIRED glib-2.0)
    set(JNI_LIBRARY_DIR_DEFAULT /Library/Java/JavaVirtualMachines/jdk1.8.0_151.jdk/Contents/Home/jre/lib/server)
    #空なら追加
    if(NOT JNI_LIBRARY_DIRS)
        list(APPEND JNI_LIBRARY_DIRS ${JNI_LIBRARY_DIR_DEFAULT})
    endif()
endif (WIN32)
message(STATUS "GLIB_LIBRARY_DIRS=${GLIB_LIBRARY_DIRS}")
message(STATUS "GLIB_INCLUDE_DIRS=${GLIB_INCLUDE_DIRS}")
message(STATUS "GLIB_LIBRARIES=${GLIB_LIBRARIES}")
message(STATUS "JNI_LIBRARY_DIRS=${JNI_LIBRARY_DIRS}")
message(STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
message(STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")
message(STATUS "BC_INSTALL_DIR=${BC_INSTALL_DIR}")


enable_testing()
add_test(
    NAME test
    COMMAND ruby auto/test.rb
    #CONFIGURATIONS Debug
    WORKING_DIRECTORY .
)
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
#ここで全ての .c ファイルを収集する
#また、テスト用に自動生成されるファイルは取り除く
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "**/*.c")
if(NOT BC_LINK_JAVA)
    list(APPEND BC_IGNORE_COMPILE "bridge.c")
    set(JNI_LIBRARIES "")
    set(JNI_CFLAGS_OTHER "")
endif()
foreach(e IN LISTS SOURCES)
    foreach(pat IN LISTS BC_IGNORE_COMPILE)
        if(${e} MATCHES ${pat})
            message("remove compile target: ${e}")
            list(REMOVE_ITEM SOURCES ${e})
            break()
        endif()
    endforeach()
endforeach()
#インクルードパス、リンカなど各種設定
link_directories (
    ${GLIB_LIBRARY_DIRS}
    ${JNI_LIBRARY_DIRS}
)
add_executable(${BC_EXECUTABLE} ${SOURCES})
add_definitions (${JNI_CFLAGS_OTHER} ${GLIB_CFLAGS_OTHER})
target_include_directories(
    ${BC_EXECUTABLE}
    PRIVATE
    ${GLIB_INCLUDE_DIRS}
    ${JNI_INCLUDE_DIRS}
)
target_link_libraries(
    ${BC_EXECUTABLE}
    PRIVATE
    ${GLIB_LIBRARIES}
    ${JNI_LIBRARIES}
)