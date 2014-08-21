project(dnw)

cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE files ${dnw_SOURCE_DIR} *.cpp *.hpp )

include_directories(.)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(${PROJECT_NAME} ${files})

target_link_libraries(${PROJECT_NAME} wt wthttp boost_regex boost_filesystem boost_system crypto)
