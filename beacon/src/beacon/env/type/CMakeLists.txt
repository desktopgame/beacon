set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
add_library("lib__beacon_env_type" STATIC
    "interface_impl.c"
    "class_impl.c"
    "meta_impl.c"
    "interface_validate.c"
    "class_find.c"
    "class_validate.c"
)
