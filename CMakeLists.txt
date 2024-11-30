cmake_minimum_required(VERSION 3.31)

project(Voxel)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

add_executable(${PROJECT_NAME} "src/Voxel.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC glfw/include)
target_link_libraries(${PROJECT_NAME} PRIVATE -lstdc++ PUBLIC glfw)