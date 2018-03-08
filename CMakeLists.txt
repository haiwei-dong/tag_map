cmake_minimum_required(VERSION 3.9)
project(tag_map)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

add_executable(tag_map
        main.cpp
        include/detect_marker.h include/create_marker.h)

target_link_libraries(tag_map
        ${OpenCV_LIBS}
        )