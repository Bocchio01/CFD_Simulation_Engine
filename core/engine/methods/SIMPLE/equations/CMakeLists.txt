project(EQUATIONS
    VERSION 1.0
    DESCRIPTION "EQUATIONS module for CFD simulation software"
    LANGUAGES C
)

add_library(${PROJECT_NAME}
    P_equation.c
    P_equation.h
    U_equation.c
    U_equation.h
    V_equation.c
    V_equation.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC libs)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_link_libraries(${PROJECT_NAME} PUBLIC m)
endif()
