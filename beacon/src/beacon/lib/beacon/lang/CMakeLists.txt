add_subdirectory("unsafe")
set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
add_library("lib__beacon_lib_beacon_lang" STATIC
    "char.c"
    "object.c"
    "double.c"
    "array.c"
    "exception.c"
    "string.c"
    "console.c"
    "void.c"
    "null.c"
    "bool.c"
    "int.c"
    "long.c"
)
