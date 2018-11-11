set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
add_library("lib__beacon_vm" STATIC
    "eval.c"
    "defer_context.c"
    "generate.c"
    "opcode.c"
    "vm.c"
    "line_range.c"
    "symbol_table.c"
    "label.c"
    "opcode_buf.c"
    "symbol_entry.c"
    "frame.c"
    "yield_context.c"
    "enviroment.c"
    "vm_trace.c"
)
