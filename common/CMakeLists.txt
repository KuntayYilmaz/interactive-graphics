cmake_minimum_required(VERSION 3.10)
project(Common LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1) Collect your .cpp sources
set(COMMON_SOURCES
  src/Shader.cpp
  src/glad.c
)

# 2) Collect your headers
set(COMMON_HEADERS
  include/common/Common.h
  include/common/Shader.h
  include/common/cyCore.h
  include/common/cyTriMesh.h
  include/common/cyVector.h
)

# 3) Create the library with both sources and headers
add_library(Common STATIC
  ${COMMON_SOURCES}
  ${COMMON_HEADERS}       # ← now CMake “knows” about your headers
)

# 4) (Optional) Group headers under “Header Files” in VS
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${COMMON_HEADERS}
)

# 5) Include paths
target_include_directories(Common PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# 6) Link GLFW lib
target_link_libraries(Common PUBLIC
  opengl32
  "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib"
)
