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

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#find_package(ZeroCIceCore)
#if(ZeroCIceCore_FOUND)
#    include_directories(${ZeroCIceCore_INCLUDE_DIRS})
#else()
#    message(FATAL_ERROR "IceCore not found!")
#endif()

#find_package(ZeroCIceUtil)
#if(ZeroCIceUtil_FOUND)
#    include_directories(${ZeroCIceUtil_INCLUDE_DIRS})
#else()
#    message(FATAL_ERROR "IceCore not found!")
#endif()

find_package(Boost 1.44.0 COMPONENTS iostreams)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
else()
  message(FATAL_ERROR "Boost not found!") 
endif()

INCLUDE_DIRECTORIES("include")
INCLUDE_DIRECTORIES("slice")

#set(new_link_flags "-Wl,-rpath /home/kirdyk/lib -L/home/kirdyk/lib")

SET(maxima_comm_sources src/maxima_comm/maxima_comm.cpp)
SET(maxima_test_sources src/maxima_test/maxima_test.cpp)

SET(maximaWorker_sources slice/Maxima.cpp src/maximaWorker/main.cpp)
SET(maximaWorkerClnt_sources slice/Maxima.cpp src/maximaWorker/client.cpp)
SET(maximaDispatcher_sources slice/Maxima.cpp src/maximaDispatcher/main.cpp)

SET(matrix_exp_sources src/matrix_exp/main.cpp)

ADD_EXECUTABLE(matrix_exp ${matrix_exp_sources})

#ADD_EXECUTABLE(maxima_test ${maxima_test_sources})
#ADD_LIBRARY(maxima_comm SHARED ${maxima_comm_sources})

#ADD_EXECUTABLE(maximaWorker ${maximaWorker_sources})
#ADD_EXECUTABLE(maximaWorkerClnt ${maximaWorkerClnt_sources})
#ADD_EXECUTABLE(maximaDispatcher ${maximaDispatcher_sources})

#set_target_properties(maxima_comm PROPERTIES VERSION ${${PROJECT_NAME}_VERSION} SOVERSION ${${PROJECT_NAME}_SOVERSION})

#target_link_libraries(maxima_comm ${CORELIBS} ${Boost_LIBRARIES} maxima_comm)
#target_link_libraries(maxima_test maxima_comm)

#target_link_libraries(maximaWorker ${CORELIBS} ${ZeroCIceCore_LIBRARY} ${ZeroCIceUtil_LIBRARY} maxima_comm)
#target_link_libraries(maximaWorkerClnt ${CORELIBS} ${ZeroCIceCore_LIBRARY} ${ZeroCIceUtil_LIBRARY})
#target_link_libraries(maximaDispatcher ${CORELIBS} ${ZeroCIceCore_LIBRARY} ${ZeroCIceUtil_LIBRARY})

