set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
add_library("lib__beacon_il_type" STATIC
    "il_enum_impl.c"
    "il_class_impl.c"
    "il_interface_impl.c"
)
