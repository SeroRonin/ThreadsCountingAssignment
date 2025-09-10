cmake_minimum_required(VERSION 3.10)
project(ThreadsCountingAssignment)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(ThreadsCountingAssignment ${SOURCES})
