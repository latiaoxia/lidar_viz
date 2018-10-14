cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_compile_definitions(ASIO_STANDALONE)

add_subdirectory(src)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

