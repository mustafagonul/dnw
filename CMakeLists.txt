project(dnw)

cmake_minimum_required(VERSION 2.8)

include_directories(.)

# variables
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


# packages
#find_package(Wt REQUIRED)
find_package(Boost COMPONENTS system filesystem regex program_options REQUIRED)

  
# getting executable files
file(GLOB_RECURSE FILES ${PROJECT_SOURCE_DIR} *.cpp *.hpp )
    

# moving from deploy directory to build directory
set(DEPLOYDIR ${PROJECT_SOURCE_DIR}/deploy)
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
  

# targets
add_executable(${PROJECT_NAME} ${FILES})


# libraries
# target_link_libraries(${PROJECT_NAME} boost_regex boost_filesystem boost_system crypto wt wthttp)
# or
# target_link_libraries(${PROJECT_NAME} boost_regex boost_filesystem boost_system crypto wt wtfcgi)
target_link_libraries(${PROJECT_NAME} debug wt debug wthttp)
target_link_libraries(${PROJECT_NAME} optimized wt optimized wtfcgi)
target_link_libraries(${PROJECT_NAME} general boost_regex boost_filesystem boost_system crypto)


# install
if(NOT DNW_TARGET_OUTPUT)
  message(WARNING "DNW_TARGET_OUTPUT is not set. Default value ('/srv/http/dnw/') is used!")
  set(DNW_TARGET_OUTPUT "/srv/http/dnw")
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION ${DNW_TARGET_OUTPUT})
install(DIRECTORY ${DEPLOYDIRS} DESTINATION ${DNW_TARGET_OUTPUT})
install(FILES ${DEPLOYFILES} DESTINATION ${DNW_TARGET_OUTPUT})




