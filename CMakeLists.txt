cmake_minimum_required(VERSION 3.10)  # Or higher
project(InteractiveGraphicsProject)

# Add the common subdirectory.  This is crucial for building the common library.
add_subdirectory(common)

# Add the projects subdirectory, so CMake knows where to find project-specific CMakeLists.txt.
add_subdirectory(projects/1-Transformations)
add_subdirectory(projects/2-Shading)