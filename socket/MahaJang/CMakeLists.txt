cmake_minimum_required(VERSION 2.8.4)
project(MJServer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/bin")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")




set(SOURCE_FILES_SERVER server.cpp)

find_package(Boost 1.57.0 COMPONENTS system)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(MJServer ${SOURCE_FILES_SERVER})
    target_link_libraries(MJServer ${Boost_LIBRARIES})
endif()



set(SOURCE_FILES_CLIENT client.cpp)
project(MJClient)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(MJClient ${SOURCE_FILES_CLIENT})
    target_link_libraries(MJClient ${Boost_LIBRARIES})
endif()
