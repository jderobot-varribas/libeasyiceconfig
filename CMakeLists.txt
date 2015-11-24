cmake_minimum_required(VERSION 2.8)
project(easyiceconfig)

#find_package(Ice)

include_directories(include)

#add_library(${PROJECT_NAME}
#	src/
#)

## demo
add_executable(demo src/demo/demo.cpp)
target_link_libraries(demo Ice IceUtil)
configure_file(src/demo/ice.cfg ice.cfg COPY_ONLY)

