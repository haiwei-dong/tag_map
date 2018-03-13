cmake_minimum_required(VERSION 3.9)
project(tag_map)

set(CMAKE_CXX_STANDARD 11)

set(OpenCV_DIR /usr/local/share/OpenCV)
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "version: ${OpenCV_VERSION}")
message(STATUS "libraries:" ${OpenCV_LIBS})
message(STATUS "include path: ${OpenCV_INCLUDE_DIRS}")

if(CMAKE_VERSION VERSION_LESS "2.8.11")
    include_directories(${OPENCV_INCLUDE_DIRS})
endif()

add_executable(tag_map
        #src/create_marker.cpp)
        src/detect_markers.cpp)

target_link_libraries(tag_map
        ${OpenCV_LIBS})