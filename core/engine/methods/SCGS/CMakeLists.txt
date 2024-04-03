project(SCGS
    VERSION 1.0
    DESCRIPTION "SCGS module for CFD simulation software"
    LANGUAGES C
)

add_library(${PROJECT_NAME}
    SCGS.c
    SCGS.h
    SCGS_BC.c
    SCGS_BC.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC libs)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_link_libraries(${PROJECT_NAME} PUBLIC m)
endif()
