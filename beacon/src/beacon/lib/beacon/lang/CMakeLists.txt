add_subdirectory("unsafe")
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
