cmake_minimum_required(VERSION 2.8)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_definitions(-DASIO_STANDALONE)

add_subdirectory(src)


