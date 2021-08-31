cmake_minimum_required(VERSION 3.14)
project(sepplesDNS)
set(CMAKE_CXX_STANDARD 20)

if (WIN32)
  add_subdirectory(lib/fmt)
endif (WIN32)

if (UNIX)
  find_package(fmt)
endif (UNIX)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS} include)
link_directories(${Boost_LIBRARY_DIRS})

file (GLOB BINS "src/*.cpp")
add_executable(sepplesDNS ${BINS})

target_link_libraries(sepplesDNS PUBLIC fmt::fmt ${Boost_LIBRARIES})