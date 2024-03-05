add_executable(${CMAKE_PROJECT_NAME} main.c)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    libs
    core
)

add_executable(${CMAKE_PROJECT_NAME}_Bench bench.c)
target_link_libraries(${CMAKE_PROJECT_NAME}_Bench PRIVATE
    libs
    core
)