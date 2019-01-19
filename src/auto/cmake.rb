require "open3"
require "fileutils"
require "date"
require 'fileutils'
=begin
ユーザ側の設定例
.bash_profile
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

makefile作成の例
../bin/a.out --test
cmake -D JNI_INCLUDE_DIR=/Library/Java/JavaVirtualMachines/jdk1.8.0_151.jdk/Contents/Home/include -D JNI_NATIVE_INCLUDE_DIR=/Library/Java/JavaVirtualMachines/jdk1.8.0_151.jdk/Contents/Home/include/darwin .
cmake -D CMAKE_BUILD_TYPE=Release -D JNI_INCLUDE_DIR=/Library/Java/JavaVirtualMachines/jdk1.8.0_151.jdk/Contents/Home/include -D JNI_NATIVE_INCLUDE_DIR=/Library/Java/JavaVirtualMachines/jdk1.8.0_151.jdk/Contents/Home/include/darwin .
cmake -D CMAKE_BUILD_TYPE=Debug -D JNI_INCLUDE_DIR=/Library/Java/JavaVirtualMachines/jdk1.8.0_151.jdk/Contents/Home/include -D JNI_NATIVE_INCLUDE_DIR=/Library/Java/JavaVirtualMachines/jdk1.8.0_151.jdk/Contents/Home/include/darwin .
make test ARGS='-V'
=end

@exe_template = <<'EOS'
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
EOS

@lib_template = <<'EOS'
set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
EOS
@all = ["${GLIB_LDFLAGS}"]

def path_to_bar(path)
    path = path.gsub(Dir.pwd, "lib_")
    path.gsub("/", "_")
end

def create_cmake(cmake_path, dir, files, depth)
    File.open(cmake_path, "w") do |fp|
        fp.puts(@exe_template) if depth == 0
        files.each do |e|
            if FileTest.directory?(e) then
                fp.puts(sprintf("add_subdirectory(\"%s\")", File.basename(e)))
            end
        end
        #ライブラリをビルド
        if depth > 0 then
            fp.puts(@lib_template)
            lib = sprintf("add_library(\"%s\" STATIC\n", (path_to_bar(dir)))
            c_files = files.select {|e| e.end_with?(".c") }
            c_files.each {|e| lib << sprintf("    \"%s\"\n", e.gsub(dir + "/", ""))}
            lib << ")\n"
            #ライブラリ一覧に追加
            if c_files.length > 0 then
                fp.puts(lib)
                @all << path_to_bar(dir)
            end
        end
        #実行ファイルをビルド
        if depth == 0 then
            exe = sprintf("add_executable(${BC_EXECUTABLE} \"beacon/main.c\")")
            fp.puts(exe)
            #ライブラリのリンク
            link = sprintf("target_link_libraries(${BC_EXECUTABLE}\n")
            @all.each {|e| link << sprintf("    \"%s\"\n", e)}
            link << ")\n"
            fp.puts(link)
            @all = []
        end
    end
end

def each_recursive(path, depth)
    file_list = []
    #パスを展開する
    opath = path
    path = File.expand_path(path)
    cmake_path = path + "/CMakeLists.txt"
    cache_path = path + "/CMakeCache.txt"
    cmake_dir = path + "/CMakeFiles"
    insta_path = path + "/cmake_install.cmake"
    makef_path = path + "/Makefile"
    test_path = path + "/CMakeTestTestfile.cmake"
    puts ("open: " + path)
    puts ("make: " + cmake_path)
    #CMakeLists.txtが存在するなら削除する
    if File.exist?(cmake_path) then
        FileUtils.rm(cmake_path)
    end
    #CMakeFilesが存在するなら削除する
    if File.exist?(cmake_dir) then
        FileUtils.rm_r(cmake_dir)
    end
    #CMakeCacheが存在するなら削除する
    if File.exist?(cache_path) then
        FileUtils.rm(cache_path)
    end
    #installが存在するなら削除する
    if File.exist?(insta_path) then
        FileUtils.rm(insta_path)
    end
    #test_pathが存在するなら削除する
    if File.exist?(test_path) then
        FileUtils.rm(test_path)
    end
    #全てのファイルを開く
    Dir.open(path).each do |file|
        next if(file == "." || file == "..")
        next if(file == "lcov" || file == "auto" || file == "script" || file == "Testing" || file == "nbproject")
        file = path + "/" + file
        puts ("  " + file)
        if(FileTest.directory?(file)) then
            each_recursive(file, depth + 1)
            file_list << file
        #ファイルを登録する
        else
            file_list << file
        end
    end
    create_cmake(cmake_path, path, file_list, depth)
    file_list
end

each_recursive(".", 0)