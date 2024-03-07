project(methods
    VERSION 1.0
    DESCRIPTION "Methods module for CFD simulation software"
    LANGUAGES C
)

add_library(${PROJECT_NAME}
    methods.c
    methods.h
    SCGS.c
    SCGS.h
    SCGS_BC.c
    SCGS_BC.h
    SIMPLE.c
    SIMPLE.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC
    m
    libs
)
