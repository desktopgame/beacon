set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
add_library("lib__beacon_env_cll" STATIC
    "class_loader_ilload_factor_module_impl.c"
    "class_loader_link_impl.c"
    "class_loader_ilload_stmt_module_impl.c"
    "class_loader_ilload_impl.c"
    "class_loader_bcload_import_module_impl.c"
    "class_loader_ilload_type_module_impl.c"
    "class_loader_bcload_member_module_impl.c"
    "class_loader_bcload_impl.c"
    "class_loader_ilload_member_module_impl.c"
)
