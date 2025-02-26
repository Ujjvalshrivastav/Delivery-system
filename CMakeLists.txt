cmake_minimum_required(VERSION 3.10)
project(dlib_test)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(OpenCV_DIR "D:\\opencv\\x64\\mingw\\lib")
# Find Dlib
find_package(dlib REQUIRED)
include_directories(D:\\SDK\\dlib_install\\include)


find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(dlib REQUIRED)
include_directories(${dlib_INCLUDE_DIRS})

add_executable(dlib_test test.cpp)

target_link_libraries(dlib_test dlib::dlib ${OpenCV_LIBS})

