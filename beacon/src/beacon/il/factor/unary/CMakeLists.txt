set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
add_library("lib__beacon_il_factor_unary" STATIC
    "il_factor_not_op_impl.c"
    "il_factor_negative_op_impl.c"
    "il_factor_childa_op_impl.c"
)
