cmake_minimum_required(VERSION 3.14)
project(sepplesDNS)
set(CMAKE_CXX_STANDARD 17)

if (WIN32)
  add_subdirectory(lib/fmt)
endif (WIN32)

if (UNIX)
  find_package(fmt)
endif (UNIX)

include_directories(include)

file (GLOB BINS "src/*.cpp")
add_executable(sepplesDNS ${BINS})
target_link_libraries(sepplesDNS PUBLIC fmt::fmt)