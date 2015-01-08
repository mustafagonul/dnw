project(dnw)

cmake_minimum_required(VERSION 2.8)

include_directories(.)

# variables
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS}")
set(CURDIR ${PROJECT_SOURCE_DIR})


# packages
find_package(Wt REQUIRED)
find_package(Boost COMPONENTS system filesystem iostreams regex program_options REQUIRED)


# getting library files
set(LIBFILES "")
file(GLOB CHILDREN RELATIVE ${CURDIR} ${CURDIR}/*)
foreach(CHILD ${CHILDREN})
  if(IS_DIRECTORY ${CURDIR}/${CHILD})
    set(CHILDDIR ${CURDIR}/${CHILD})
    file(GLOB_RECURSE CHILDFILES ${CHILDDIR} ${CHILDDIR}/*.cpp ${CHILDDIR}/*.hpp)
    list(APPEND LIBFILES ${CHILDFILES})    
  endif()
endforeach()

  
# getting executable files
file(GLOB EXEFILES ${CURDIR} ${CURDIR}/*.cpp ${CURDIR}/*.hpp)
    

# moving from deploy directory to build directory
set(DEPLOYDIR ${CURDIR}/deploy/)
set(DEPLOYS "")
file(GLOB CHILDREN RELATIVE ${DEPLOYDIR} ${DEPLOYDIR}/*)
foreach(CHILD ${CHILDREN})
  file(COPY ${DEPLOYDIR}/${CHILD} DESTINATION ${PROJECT_BINARY_DIR})
  list(APPEND DEPLOYS ${DEPLOYDIR}/${CHILD})
endforeach()


# setting targets
set(TARGET_EXE "${PROJECT_NAME}_exe")
set(TARGET_LIB "${PROJECT_NAME}")
  

# targets
add_executable(${TARGET_EXE} ${EXEFILES})
add_library(${TARGET_LIB} SHARED ${LIBFILES})


# libraries
target_link_libraries(${TARGET_EXE} wt wthttp boost_filesystem boost_system boost_iostreams dl)
target_link_libraries(${TARGET_LIB} wt boost_regex boost_filesystem boost_system crypto)

# install
set(TARGET_OUTPUT "/srv/http/dnw/")
install(TARGETS ${TARGET_EXE} ${TARGET_LIB} DESTINATION ${TARGET_OUTPUT})
install(DIRECTORY ${DEPLOYS} DESTINATION ${TARGET_OUTPUT})


