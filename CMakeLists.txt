CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(libmaxima_test CXX)

set(CORELIBS boost_iostreams m)

set(new_link_flags "-Wl,-rpath /home/kirdyk/lib -L/home/kirdyk/lib")

ADD_EXECUTABLE(maxima_test maxima_test.cpp)
ADD_LIBRARY(maxima_comm SHARED maxima_comm.cpp)

set_target_properties(maxima_test PROPERTIES LINK_FLAGS ${LINK_FLAGS} ${new_link_flags})
set_target_properties(maxima_comm PROPERTIES LINK_FLAGS ${LINK_FLAGS} ${new_link_flags})
set(CMAKE_CXX_FLAGS "-I/home/kirdyk/include")

target_link_libraries(maxima_comm ${CORELIBS} maxima_comm)
target_link_libraries(maxima_test maxima_comm)

