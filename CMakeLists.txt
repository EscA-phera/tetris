cmake_minimum_required(VERSION 3.15)
project(tetris)

set(CMAKE_CXX_STANDARD 14)

set(SFML_DIR "/usr/include/SFML")

add_executable(tetris main.cpp)
target_link_libraries(tetris sfml-graphics sfml-window sfml-system)