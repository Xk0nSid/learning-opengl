cmake_minimum_required(VERSION 3.27)

project(learning_opengl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lgl src/main.cc)

add_subdirectory(deps/glew/build/cmake)
add_subdirectory(deps/glfw)

target_link_libraries(lgl ${GLEW_LIBRARIES} glfw)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)