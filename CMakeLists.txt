project(dnw)

cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE files ${dnw_SOURCE_DIR} *.cpp *.hpp )

include_directories(.)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


# moving from deploy directory to build directory
set(deploydir ${PROJECT_SOURCE_DIR}/deploy/)
file(GLOB children RELATIVE ${deploydir} ${deploydir}/*)
foreach(child ${children})
  file(COPY ${deploydir}/${child} DESTINATION ${PROJECT_BINARY_DIR})
endforeach()
  

add_executable(${PROJECT_NAME} ${files})

target_link_libraries(${PROJECT_NAME} wt wthttp boost_regex boost_filesystem boost_system crypto)
