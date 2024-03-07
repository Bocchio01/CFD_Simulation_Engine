project(parsers
    VERSION 1.0
    DESCRIPTION "Parsers module for CFD simulation software"
    LANGUAGES C
)

add_library(${PROJECT_NAME}
    cmd.c
    cmd.h
    json.c
    json.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC libs)