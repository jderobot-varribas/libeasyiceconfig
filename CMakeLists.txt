cmake_minimum_required(VERSION 2.8)
project(easyiceconfig)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

#find_package(Ice)

include_directories(include)

#add_library(${PROJECT_NAME}
#	src/
#)

## demo
add_executable(demo src/demo/demo.cpp)
target_link_libraries(demo Ice IceUtil)
configure_file(src/demo/ice.cfg ice.cfg COPY_ONLY)

## tests
add_executable(test_stdutils src/tests/test_stdutils.cpp)
