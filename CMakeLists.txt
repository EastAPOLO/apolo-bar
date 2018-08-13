cmake_minimum_required(VERSION 3.0)
project(apolo-bar)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(apolo-bar src/main.cpp)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(i3ipc++)
include_directories(${I3IPCpp_INCLUDE_DIRS})
link_directories(${I3IPCpp_LIBRARY_DIRS})
target_link_libraries(apolo-bar ${I3IPCpp_LIBRARIES})
