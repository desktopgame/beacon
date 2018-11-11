add_subdirectory("unary")
add_subdirectory("variable")
add_subdirectory("invoke")
add_subdirectory("binary")
set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
add_library("lib__beacon_il_factor" STATIC
    "il_factor_property_impl.c"
    "il_factor_member_op_impl.c"
    "il_factor_new_instance_impl.c"
    "il_factor_string_impl.c"
    "il_factor_subscript_impl.c"
    "il_factor_int_impl.c"
    "il_factor_bool_impl.c"
    "il_factor_instanceof_impl.c"
    "il_factor_unary_op_impl.c"
    "il_factor_assign_op_impl.c"
    "il_factor_explicit_unary_op_impl.c"
    "il_factor_super_impl.c"
    "il_factor_as_impl.c"
    "il_factor_double_impl.c"
    "il_factor_binary_op_impl.c"
    "il_factor_call_op_impl.c"
    "il_factor_variable_impl.c"
    "il_factor_char_impl.c"
    "il_factor_null_impl.c"
    "il_factor_explicit_binary_op_impl.c"
    "il_factor_this_impl.c"
)
