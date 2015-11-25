cmake_minimum_required(VERSION 2.8)
project(easyice)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

#find_package(Ice)
set(Ice_LIBRARIES "-lIce -lIceUtil")

include_directories(include)

add_library(${PROJECT_NAME} SHARED
    src/easyice.cpp
    src/loader.cpp

    include/easyice/easyice.hpp
    include/easyice/loader.hpp
    include/easyice/injector.hpp
    include/easyice/debug.hpp

    include/easyice/stdutils.hpp

    include/easyice/hardcoredlocations.h
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

