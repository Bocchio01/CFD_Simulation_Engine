add_library(libs
    libs.c
    libs.h
)

add_subdirectory(cGETOPT)
add_subdirectory(cLOG)
add_subdirectory(cFILE)
add_subdirectory(cJSON)
add_subdirectory(cALGEBRA)

target_include_directories(libs PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/cGETOPT
    ${CMAKE_CURRENT_SOURCE_DIR}/cLOG
    ${CMAKE_CURRENT_SOURCE_DIR}/cFILE
    ${CMAKE_CURRENT_SOURCE_DIR}/cJSON
    ${CMAKE_CURRENT_SOURCE_DIR}/cALGEBRA
)

target_link_libraries(libs PUBLIC
    cGETOPT
    cLOG
    cFILE
    cJSON
    cALGEBRA
)