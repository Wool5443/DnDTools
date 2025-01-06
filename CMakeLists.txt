cmake_minimum_required(VERSION 3.20)
set(projectName "DndTools")

project(${projectName} C)

# add_compile_definitions("DISABLE_LOGGING")

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED true)

set(CMAKE_C_FLAGS_DEBUG "\
-g -D _DEBUG -ggdb3 -std=gnu17 -O0 -Wall -Wextra \
-fsanitize=address,undefined,leak,shift,float-divide-by-zero,signed-integer-overflow\
")
set(CMAKE_C_FLAGS_RELEASE "-O3 -g -DNDEBUG -march=native")

add_subdirectory(cmlib)

set(SOURCES
    "src/main.c"
    "src/Roll.c"
    "src/CLArgs.c"
    "src/ModeFunctions.c"
    "src/Options.c"
    "src/ThrowStats.c"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE cmlibLogger cmlibVector)
target_include_directories(${PROJECT_NAME} PRIVATE include)
