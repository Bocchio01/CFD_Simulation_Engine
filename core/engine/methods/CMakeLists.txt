project(methods
    VERSION 1.0
    DESCRIPTION "Methods module for CFD simulation software"
    LANGUAGES C
)

add_subdirectory(SCGS)
add_subdirectory(SIMPLE)

add_library(${PROJECT_NAME}
    methods.c
    methods.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC
    SCGS
    SIMPLE
    libs
)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_link_libraries(${PROJECT_NAME} PUBLIC m)
endif()
