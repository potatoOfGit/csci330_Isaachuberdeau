cmake_minimum_required(VERSION 3.10)
project(Chapter03_References)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Tests (optional)
# add_executable(tests tests/test_main.cpp)