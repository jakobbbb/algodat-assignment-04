add_executable(example
    example.cpp
    closest.cpp
    )

add_executable(tests
    tests.cpp
    closest.cpp
    )

# generate compile_commands.json
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
