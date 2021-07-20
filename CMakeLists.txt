cmake_minimum_required(VERSION 3.14)
project(sepplesDNS)
set(CMAKE_CXX_STANDARD 17)
include_directories(include)

add_subdirectory(lib/fmt)

file (GLOB BINS "src/*.cpp")
add_executable(sepplesDNS ${BINS})
target_link_libraries(sepplesDNS PUBLIC fmt::fmt-header-only)