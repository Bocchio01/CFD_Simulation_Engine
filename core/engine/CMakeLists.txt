project(engine
    VERSION 1.0
    DESCRIPTION "Engine module for CFD simulation software"
    LANGUAGES C
)

add_subdirectory(mesh)
add_subdirectory(methods)
add_subdirectory(schemes)

add_library(${PROJECT_NAME}
    engine.c
    engine.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC
    mesh
    methods
    schemes
    libs
)