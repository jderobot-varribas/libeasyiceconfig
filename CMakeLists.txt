cmake_minimum_required(VERSION 2.8)
project(easyiceconfig)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

#find_package(Ice)
set(Ice_LIBRARIES "-lIce -lIceUtil")

include_directories(include)

add_library(${PROJECT_NAME} SHARED
    src/loader.cpp
    src/initializer.cpp

    include/easyiceconfig/EasyIce.hpp
    include/easyiceconfig/hardcoredlocations.h

    include/easyiceconfig/loader.hpp
    include/easyiceconfig/initializer.hpp
    include/easyiceconfig/injector.hpp
    include/easyiceconfig/debug.hpp

    include/easyiceconfig/stdutils.hpp
)
target_link_libraries(${PROJECT_NAME} ${Ice_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-std=c++0x")


## demo
add_executable(demo src/demo/demo.cpp)
target_link_libraries(demo ${Ice_LIBRARIES})
configure_file(src/demo/ice.cfg ice.cfg COPY_ONLY)

## tests
add_executable(test_stdutils src/tests/test_stdutils.cpp)
set_target_properties(test_stdutils PROPERTIES COMPILE_FLAGS "-std=c++0x")

add_executable(test_loader src/tests/test_loader.cpp)
target_link_libraries(test_loader ${PROJECT_NAME} ${Ice_LIBRARIES})

