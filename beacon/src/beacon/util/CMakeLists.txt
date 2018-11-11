set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
add_library("lib__beacon_util" STATIC
    "string_buffer.c"
    "tree_map.c"
    "string_pool.c"
    "stack.c"
    "io.c"
    "storage.c"
    "vector.c"
    "mem.c"
    "numeric_map.c"
    "text.c"
    "file_entry.c"
    "getopt.c"
)
