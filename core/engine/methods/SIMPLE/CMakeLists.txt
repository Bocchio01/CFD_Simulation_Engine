project(SIMPLE
    VERSION 1.0
    DESCRIPTION "SIMPLE module for CFD simulation software"
    LANGUAGES C
)

add_subdirectory(equations)

add_library(${PROJECT_NAME}
    SIMPLE.c
    SIMPLE.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC
    EQUATIONS
    libs
)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_link_libraries(${PROJECT_NAME} PUBLIC m)
endif()
