cmake_minimum_required(VERSION 3.26)
project(mass_image_processing)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(OpenCV REQUIRED)
find_package(TBB REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(mass_image_processing src/main.cpp
        src/Image.cpp
        includes/Image.h
        src/ParallelProcess.cpp
        includes/ParallelProcess.h
        src/SequentialProcess.cpp
        includes/SequentialProcess.h
        src/BufferedIO.cpp
        includes/BufferedIO.h
        includes/ImageOperation.h
        includes/ColorChangeOperation.h
        includes/GaussianBlurOperation.h)

target_link_libraries(mass_image_processing ${OpenCV_LIBS} TBB::tbb)
