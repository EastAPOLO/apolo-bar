cmake_minimum_required(VERSION 3.0)
project(apolo-bar)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(apolo-bar src/main.cpp)
add_subdirectory(i3ipc++)

include_directories(${I3IPCpp_INCLUDE_DIRS})
link_directories(${I3IPCpp_LIBRARY_DIRS})
target_link_libraries(apolo-bar ${I3IPCpp_LIBRARIES})

