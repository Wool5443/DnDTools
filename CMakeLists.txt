cmake_minimum_required(VERSION 3.20)

project(DnDTools CXX)

set(PROJECTNAME ${PROJECT_NAME})

find_package(Boost REQUIRED COMPONENTS program_options)
find_package(fmt REQUIRED)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_C_FLAGS_DEBUG "\
-g -D _DEBUG -ggdb3 -O0 -Wall -Wextra \
-fsanitize=address,undefined,leak,shift,float-divide-by-zero,signed-integer-overflow\
")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")

set(SOURCES
    "src/main.cpp"
    "src/ParseCLI.cpp"
    "src/Roll.cpp"
    "src/Modes.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES} fmt::fmt)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
