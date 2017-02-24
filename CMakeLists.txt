cmake_minimum_required(VERSION 3.6)
project(minesweeper)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/mineswepper.cpp src/functions.cpp header/mineswepper.h header/functions.h)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
add_executable(minesweeper ${SOURCE_FILES})