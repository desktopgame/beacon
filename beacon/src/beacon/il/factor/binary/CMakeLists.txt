set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
add_library("lib__beacon_il_factor_binary" STATIC
    "il_factor_logic_op_impl.c"
    "il_factor_compare_op_impl.c"
    "il_factor_excor_op_impl.c"
    "il_factor_arithmetic_op_impl.c"
    "il_factor_shift_op_impl.c"
)
