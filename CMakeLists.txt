project(dnw)

cmake_minimum_required(VERSION 2.8)

include_directories(.)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CURDIR ${PROJECT_SOURCE_DIR})
set(EXEDIRS "boost")



# getting library files
set(LIBFILES "")
file(GLOB CHILDREN RELATIVE ${CURDIR} ${CURDIR}/*)
foreach(CHILD ${CHILDREN})
  list(FIND EXEDIRS ${CHILD} DIRINDEX)
  if(IS_DIRECTORY ${CURDIR}/${CHILD} AND ${DIRINDEX} GREATER -1)
    file(GLOB_RECURSE FILES ${CURDIR}/${CHILD} *.cpp *.hpp)
    list(APPEND LIBFILES ${FILES})
  endif()
endforeach()
  
  
# getting executable files
file(GLOB EXEFILES ${CURDIR} *.cpp *.hpp)
foreach(EXEDIR ${EXEDIRS})
  file(GLOB_RECURSE FILES ${CURDIR}/${EXEDIR} ${CURDIR}/${EXEDIR}/*)
  list(APPEND EXEFILES ${FILES})
endforeach()
    

# moving from deploy directory to build directory
set(DEPLOYDIR ${CURDIR}/deploy/)
file(GLOB CHILDREN RELATIVE ${DEPLOYDIR} ${DEPLOYDIR}/*)
foreach(CHILD ${CHILDREN})
  file(COPY ${DEPLOYDIR}/${CHILD} DESTINATION ${PROJECT_BINARY_DIR})
endforeach()


# setting targets
set(TARGET_EXE "${PROJECT_NAME}_exe")
set(TARGET_LIB "${PROJECT_NAME}")
  

# targets
add_executable(${TARGET_EXE} ${EXEFILES})
add_library(${TARGET_LIB} SHARED ${LIBFILES})


# libraries
target_link_libraries(${TARGET_EXE} wt wthttp boost_filesystem boost_system dl)
target_link_libraries(${TARGET_LIB} wt boost_regex boost_filesystem boost_system crypto)
