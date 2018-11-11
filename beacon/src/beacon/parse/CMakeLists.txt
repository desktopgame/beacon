set(CMAKE_C_FLAGS_DEBUG "-g -coverage -O0 -DDEBUG -MMD -Wall")
set(CMAKE_C_FLAGS_RELEASE "-g -O2 -MMD -w -DNDEBUG")
add_library("lib__beacon_parse" STATIC
    "beacon.tab.c"
    "lex.yy.c"
    "parser.c"
)
