cmake_minimum_required(VERSION 2.8)
project(beacon C)
set(CMAKE_CXX_COMPILER clang)

find_package(PkgConfig REQUIRED)
find_package(JNI)
pkg_check_modules(GLIB REQUIRED glib-2.0)
set(JNI_LIBRARY_DIR_DEFAULT /Library/Java/JavaVirtualMachines/jdk1.8.0_151.jdk/Contents/Home/jre/lib/server)
#空なら追加
if(NOT JNI_LIBRARY_DIRS)
    list(APPEND JNI_LIBRARY_DIRS ${JNI_LIBRARY_DIR_DEFAULT})
endif()
message(STATUS "GLIB_LIBRARY_DIRS=${GLIB_LIBRARY_DIRS}")
message(STATUS "GLIB_INCLUDE_DIRS=${GLIB_INCLUDE_DIRS}")
message(STATUS "GLIB_LIBRARIES=${GLIB_LIBRARIES}")
message(STATUS "JNI_LIBRARY_DIRS=${JNI_LIBRARY_DIRS}")
message(STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
message(STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")

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
#ここで全ての .c ファイルを収集する
#また、テスト用に自動生成されるファイルは取り除く
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "**/*.c")
foreach(e IN LISTS SOURCES)
    if(${e} MATCHES "CMakeCCompilerId.c" OR
       ${e} MATCHES "feature_tests.c")
        message("remove test script: ${e}")
        list(REMOVE_ITEM SOURCES ${e})
    endif()
endforeach()
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
    -ljvm
    -lglib-2.0
)