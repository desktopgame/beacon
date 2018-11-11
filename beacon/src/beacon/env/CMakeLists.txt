add_subdirectory("type")
add_subdirectory("cll")
set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
add_library("lib__beacon_env" STATIC
    "type_interface.c"
    "object.c"
    "heap.c"
    "script_method.c"
    "generic_cache.c"
    "type_cache.c"
    "fqcn_cache.c"
    "exception.c"
    "vtable.c"
    "property.c"
    "operator_overload.c"
    "class_loader.c"
    "type_parameter.c"
    "script_context.c"
    "parameter.c"
    "import_info.c"
    "native_method_ref.c"
    "method.c"
    "field.c"
    "generic_type.c"
    "native_method.c"
    "constructor.c"
    "operator_vt.c"
    "namespace.c"
    "property_body.c"
    "import_manager.c"
)
