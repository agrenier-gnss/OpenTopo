# FIXME: Add what you need to handle Qt's link and compilation

cmake_minimum_required(VERSION 2.8)
project(OPENSOFT C CXX)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic -std=c++11 -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0")

# Facilitate Qt use
set(CMAKE_AUTOMOC ON)

#find_package(Threads REQUIRED)
find_package(Boost COMPONENTS program_options system REQUIRED)

include_directories(src/)


add_subdirectory(src/back-end)
# TODO: Add new src/ subdirectories here


# main binary
set(ALL
  src/opensoft.cc)
add_executable(opensoft ${ALL})
target_link_libraries(
  opensoft
#  back-end_obj
  ${Boost_LIBRARIES}
# TODO: Add the libraries you need to compile the main here
)
