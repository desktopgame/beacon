add_subdirectory("util")
add_subdirectory("parse")
add_subdirectory("shared")
add_subdirectory("env")
add_subdirectory("vm")
add_subdirectory("lib")
add_subdirectory("ast")
add_subdirectory("il")
add_subdirectory("thread")
add_library("lib__beacon" STATIC
    "cl.c"
    "main.c"
    "error.c"
    "test.c"
)
