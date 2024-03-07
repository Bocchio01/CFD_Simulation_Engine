project(schemes
    VERSION 1.0
    DESCRIPTION "Schemes module for CFD simulation software"
    LANGUAGES C
)

add_library(${PROJECT_NAME}
    schemes.c
    schemes.h
    convection.c
    convection.h
    diffusion.c
    diffusion.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC
    m
    libs
)
