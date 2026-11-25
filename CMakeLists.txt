cmake_minimum_required(VERSION 3.0.0)
project(tp1 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

# add_executable(ascii_cat src/ascii_cat.cpp)

# add_executable(ascii_wc src/ascii_wc.cpp)

# add_executable(ascii_diff src/ascii_diff.cpp)

add_executable(frequencies src/frequencies.cpp)