cmake_minimum_required(VERSION 3.26)
project(mass_image_processing)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(mass_image_processing main.cpp
        Image.cpp
        Image.h)

target_link_libraries(mass_image_processing ${OpenCV_LIBS})
