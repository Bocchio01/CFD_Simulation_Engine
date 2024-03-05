project(in
    VERSION 1.0
    DESCRIPTION "Input module for CFD simulation software"
    LANGUAGES C
)

add_subdirectory(parsers)

add_library(${PROJECT_NAME}
    in.c
    in.h
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
    parsers
)