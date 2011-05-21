CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(maxima_comm CXX)

SET(${PROJECT_NAME}_MAJOR_VERSION 0)
SET(${PROJECT_NAME}_MINOR_VERSION 1)
SET(${PROJECT_NAME}_PATCH_VERSION 1)


SET(${PROJECT_NAME}_VERSION
    ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_VERSION})
SET(${PROJECT_NAME}_SOVERSION
    ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_VERSION})

set(CORELIBS m)

find_package(Boost 1.44.0 COMPONENTS iostreams)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
else()
  message(FATAL_ERROR "Boost not found!") 
endif()

INCLUDE_DIRECTORIES("include")

set(new_link_flags "-Wl,-rpath /home/kirdyk/lib -L/home/kirdyk/lib")

SET(maxima_comm_sources src/maxima_comm/maxima_comm.cpp)
SET(maxima_test_sources src/maxima_test/maxima_test.cpp)

ADD_EXECUTABLE(maxima_test ${maxima_test_sources})
ADD_LIBRARY(maxima_comm SHARED ${maxima_comm_sources})

set_target_properties(maxima_test PROPERTIES LINK_FLAGS ${LINK_FLAGS} ${new_link_flags})

set_target_properties(maxima_comm PROPERTIES LINK_FLAGS ${LINK_FLAGS} ${new_link_flags})
set_target_properties(maxima_comm PROPERTIES VERSION ${${PROJECT_NAME}_VERSION} SOVERSION ${${PROJECT_NAME}_SOVERSION})

set(CMAKE_CXX_FLAGS "-I/home/kirdyk/include")

target_link_libraries(maxima_comm ${CORELIBS} ${Boost_LIBRARIES} maxima_comm)
target_link_libraries(maxima_test maxima_comm)

