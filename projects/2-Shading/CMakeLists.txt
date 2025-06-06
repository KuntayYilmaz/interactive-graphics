cmake_minimum_required(VERSION 3.10)
project(Shading)

set(SHADING_SOURCES
    src/main.cpp
)

add_executable(Shading ${SHADING_SOURCES})

target_link_libraries(Shading
    Common
)
# Include the Common library's headers.
target_include_directories(Shading
    PRIVATE # Or PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../common/include
)
