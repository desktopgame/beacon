set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
add_library("lib__beacon_lib_beacon_lang_unsafe" STATIC
    "bc_time.c"
    "bc_system.c"
    "bc_file.c"
    "bc_locale.c"
)
