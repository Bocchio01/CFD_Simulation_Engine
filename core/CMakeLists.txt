project(core
    VERSION 1.0
    DESCRIPTION "Core of the CFD library"
    LANGUAGES C
)

add_subdirectory(in)
add_subdirectory(engine)
add_subdirectory(out)

add_library(${PROJECT_NAME}
    CFD.h
    CFD.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
    in
    engine
    out
)