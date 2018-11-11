add_subdirectory("stmt")
add_subdirectory("factor")
add_subdirectory("type")
set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
add_library("lib__beacon_il" STATIC
    "il_field.c"
    "il_parameter.c"
    "il_argument.c"
    "call_frame.c"
    "il_operator_overload.c"
    "il_method.c"
    "il_namespace.c"
    "il_type_parameter.c"
    "il_constructor_chain.c"
    "control_structure.c"
    "il_type_argument.c"
    "il_stmt_interface.c"
    "il_import.c"
    "il_type_interface.c"
    "il_property.c"
    "il_constructor.c"
    "il_factor_interface.c"
    "call_context.c"
    "il_property_body.c"
    "il_function.c"
    "il_top_level.c"
    "il_print_layout.c"
)
