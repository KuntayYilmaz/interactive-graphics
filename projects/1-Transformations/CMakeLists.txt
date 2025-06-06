cmake_minimum_required(VERSION 3.10)
project(Transformations)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 0. Shader files (for Solution Explorer only)
file(GLOB_RECURSE SHADER_FILES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.vert"
     "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.frag")

# 1. Executable
add_executable(Transformations src/main.cpp)
target_sources(Transformations PRIVATE ${SHADER_FILES})
source_group("Shader Files" FILES ${SHADER_FILES})

# 2. Link / include
target_link_libraries(Transformations PRIVATE Common)
target_include_directories(Transformations PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../common/include)

set_target_properties(Transformations PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:Transformations>")

# 3. Copy assets after every build of the executable
add_custom_command(TARGET Transformations POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
            "$<TARGET_FILE_DIR:Transformations>/shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/models"
            "$<TARGET_FILE_DIR:Transformations>/models"
    COMMENT "Copying shaders/ and models/ to output directory")
