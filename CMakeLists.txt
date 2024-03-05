cmake_minimum_required(VERSION 3.28)

project(CFD_Simulation_Engine
    VERSION 0.1
    DESCRIPTION "A compact but flexible CFD engine."
    LANGUAGES C
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Werror -O2)
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4 /WX)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

# Used by the log library
add_definitions(-DLOG_USE_COLOR)

include_directories(
    ${CMAKE_SOURCE_DIR}
)

add_subdirectory(libs)
add_subdirectory(src)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE
    libs
    src
)

add_executable(${PROJECT_NAME}_bench bench.c)
target_link_libraries(${PROJECT_NAME}_bench PRIVATE
    libs
    src
)