project(dnw)

cmake_minimum_required(VERSION 2.8)

include_directories(.)

# variables
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS}")
set(CURDIR ${PROJECT_SOURCE_DIR})


# packages
find_package(Wt REQUIRED)
find_package(Boost COMPONENTS system filesystem regex program_options REQUIRED)


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
set(DEPLOYDIR ${CURDIR}/deploy)
set(DEPLOYDIRS "")
set(DEPLOYFILES "")
file(GLOB CHILDREN RELATIVE ${DEPLOYDIR} ${DEPLOYDIR}/*)
foreach(CHILD ${CHILDREN})
  file(COPY ${DEPLOYDIR}/${CHILD} DESTINATION ${PROJECT_BINARY_DIR})
  if(IS_DIRECTORY ${DEPLOYDIR}/${CHILD})
    list(APPEND DEPLOYDIRS ${DEPLOYDIR}/${CHILD})
  else()
    list(APPEND DEPLOYFILES ${DEPLOYDIR}/${CHILD})
  endif()
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

# install
if(NOT DNW_TARGET_OUTPUT)
  message(WARNING "DNW_TARGET_OUTPUT is not set. Default value ('/srv/http/dnw/') is used!")
  set(DNW_TARGET_OUTPUT "/srv/http/dnw/")
endif()

install(TARGETS ${TARGET_EXE} ${TARGET_LIB} DESTINATION ${DNW_TARGET_OUTPUT})
install(DIRECTORY ${DEPLOYDIRS} DESTINATION ${DNW_TARGET_OUTPUT})
install(FILES ${DEPLOYFILES} DESTINATION ${DNW_TARGET_OUTPUT})

if (NOT WT_RESOURCE_DIR)
  message(WARNING "WT_RESOURCE_DIR is not set. Default value ('/usr/share/Wt/resources') is used!")
  set(WT_RESOURCE_DIR "/usr/share/Wt/resources")
endif()

if (EXISTS "${WT_RESOURCE_DIR}" AND IS_DIRECTORY "${WT_RESOURCE_DIR}")
  set(WT_RESOURCE_LINK "${DNW_TARGET_OUTPUT}/resources")
  install(CODE "execute_process(COMMAND rm -f ${WT_RESOURCE_LINK})")
  install(CODE "execute_process(COMMAND ln -s ${WT_RESOURCE_DIR} ${WT_RESOURCE_LINK})")
else()
  message(WARNING "Resource directory cannot be found!")
endif()


