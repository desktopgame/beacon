set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
add_library("lib__beacon_il_factor_invoke" STATIC
    "subscript_descriptor.c"
    "il_factor_invoke_static_impl.c"
    "il_factor_invoke_bound_impl.c"
    "il_factor_invoke_impl.c"
)
