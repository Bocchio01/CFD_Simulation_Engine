project(cALGEBRA
    VERSION 1.0
    DESCRIPTION "C library for linear algebra operations"
    LANGUAGES C
)

add_library(${PROJECT_NAME} STATIC
    cMAT3D.c
    cMAT3D.h
    cMAT2D.c
    cMAT2D.h
    cVEC.c
    cVEC.h
)

target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
