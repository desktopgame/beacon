add_subdirectory("util")
add_subdirectory("parse")
add_subdirectory("shared")
add_subdirectory("env")
add_subdirectory("vm")
add_subdirectory("lib")
add_subdirectory("ast")
add_subdirectory("il")
add_subdirectory("thread")
set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
add_library("lib__beacon" STATIC
    "cl.c"
    "main.c"
    "error.c"
    "test.c"
)
