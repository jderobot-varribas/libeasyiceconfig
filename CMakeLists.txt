#  Copyright (C) 2015 JDE Developers Team
#  Authors:
#    Victor Arribas <v.arribas.urjc@gmail.com>

cmake_minimum_required(VERSION 2.8)
project(easyiceconfig)
set(PROJECT_DESCRIPTION "A library to tame Ice.Config")
set(PROJET_VERSION 0.9.3-1)

## FindIce
# since Ice is located at standard location (/usr),
# include_directories() and link_directories() can
# be ommited. Only Ice_LIBRARIES must be defined, and
# we can handle it just like pkg-config
#find_package(Ice)
list(APPEND Ice_LIBRARIES Ice IceUtil)


### Project config
include_directories(include)

set(HEADERS
    include/easyiceconfig/EasyIce.h
    include/easyiceconfig/EasyProxy.h
    include/easyiceconfig/hardcoredlocations.h

    include/easyiceconfig/loader.hpp
    include/easyiceconfig/initializer.hpp
    include/easyiceconfig/injector.hpp

    include/easyiceconfig/proxies.hpp
    include/easyiceconfig/debug.hpp

    include/easyiceconfig/stdutils.hpp
)

set(SOURCES
    src/loader.cpp
    src/initializer.cpp
)
set_property(SOURCE src/loader.cpp PROPERTY COMPILE_FLAGS "-std=c++0x")

## Adding shared library for common usage
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${Ice_LIBRARIES})

## Adding static library for single .so configurations
# since target is a shared library, -fPIC must be provided
add_library(${PROJECT_NAME}-embedded STATIC ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME}-embedded ${Ice_LIBRARIES})
set_property(TARGET ${PROJECT_NAME}-embedded PROPERTY POSITION_INDEPENDENT_CODE 1)

## Export library variables (like find_package)
set(${PROJECT_NAME}_FOUND 1 CACHE BOOL "Find(${PROJECT_NAME})")
set(${PROJECT_NAME}_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE PATH "Find(${PROJECT_NAME})")
set(${PROJECT_NAME}_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}" CACHE PATH "Find(${PROJECT_NAME})")
set(${PROJECT_NAME}_LIBRARIES "${PROJECT_NAME}" CACHE STRINGS "Find(${PROJECT_NAME})")


## demo
add_executable(demo src/demo/demo.cpp)
target_link_libraries(demo ${Ice_LIBRARIES})
configure_file(src/demo/ice.cfg ice.cfg COPY_ONLY)

## tests
add_executable(test_stdutils src/tests/test_stdutils.cpp)
set_target_properties(test_stdutils PROPERTIES COMPILE_FLAGS "-std=c++0x")

add_executable(test_loader src/tests/test_loader.cpp)
target_link_libraries(test_loader ${PROJECT_NAME} ${Ice_LIBRARIES})

add_executable(test_proxy src/tests/test_proxy.cpp)
target_link_libraries(test_proxy ${PROJECT_NAME} ${Ice_LIBRARIES} pthread)


include(install_it.cmake)
include(cpack_it.cmake)
