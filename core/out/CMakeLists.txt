project(out
    VERSION 1.0
    DESCRIPTION "Output module for CFD simulation software"
    LANGUAGES C
)

add_library(${PROJECT_NAME}
    out.c
    out.h
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})