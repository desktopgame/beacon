add_subdirectory("unsafe")
set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
add_library("lib__beacon_lib_beacon_lang" STATIC
    "bc_string.c"
    "bc_void.c"
    "bc_object.c"
    "bc_double.c"
    "bc_int.c"
    "bc_null.c"
    "bc_bool.c"
    "bc_array.c"
    "bc_long.c"
    "bc_console.c"
    "bc_char.c"
    "bc_exception.c"
)
