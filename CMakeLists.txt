CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(libmaxima_test CXX)

set(CORELIBS boost_iostreams m)

INCLUDE_DIRECTORIES("include")

set(new_link_flags "-Wl,-rpath /home/kirdyk/lib -L/home/kirdyk/lib")

SET(maxima_comm_sources src/maxima_comm/maxima_comm.cpp)
SET(maxima_test_sources src/maxima_test/maxima_test.cpp)

ADD_EXECUTABLE(maxima_test ${maxima_test_sources})
ADD_LIBRARY(maxima_comm SHARED ${maxima_comm_sources})

set_target_properties(maxima_test PROPERTIES LINK_FLAGS ${LINK_FLAGS} ${new_link_flags})
set_target_properties(maxima_comm PROPERTIES LINK_FLAGS ${LINK_FLAGS} ${new_link_flags})

set(CMAKE_CXX_FLAGS "-I/home/kirdyk/include")

target_link_libraries(maxima_comm ${CORELIBS} maxima_comm)
target_link_libraries(maxima_test maxima_comm)

