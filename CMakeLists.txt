cmake_minimum_required(VERSION 3.4)

project(Puzzler)
list(APPEND CMAKE_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
set(CMAKE_CXX_STANDARD 11)
find_package(Imagine REQUIRED COMPONENTS Graphics)

add_executable(Puzzler main.cpp
    Puzzle.h
    Puzzle.cpp)
target_link_libraries(Puzzler Imagine::Graphics)
