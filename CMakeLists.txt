#  Copyright (C) 2015-2016 JDE Developers Team
#    Cmake template authors:
#      2016 Jan, Victor Arribas <v.arribas.urjc@gmail.com>
#  Authors:
#    Victor Arribas <v.arribas.urjc@gmail.com>

cmake_minimum_required(VERSION 2.8.4)

## PROJECT_NAME
# define here your project name
project(easyiceconfig)
# Sometimes output binary must have a custom name. Set it here:
set(binname ${PROJECT_NAME})


### Dependencies (@pre-job)
## use_package()
# You can use use_package for:
#   * JdeRobot libraries
#   * standard find_package() libraries
use_package(ZeroCIce)

## custom dependencies
include_directories(
)
link_directories(
)
list(APPEND LIBRARIES
    boost_regex
)


### Project
## Includes
# public headers MUST follow below standard:
#   include/
#     lib_project_name/
#       <your .h files or whatever additional directory>
# Example:
#   include/skel_component/skel_component.h
# Therefore, you can cleanly and safety include headers with
#   #include <skel_component/skel_component.h>
#
# Private headers can be placed under "source" tree and be referenced as:
#   #include "foo.h"
#   #include "../bar/bar.h"
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
include(IDE_show_headers)

## Sources
# sources MUST be placed under "src/" directory
# in a flattened or tree structure
set(SOURCES
    src/loader.cpp
    src/initializer.cpp
    src/injector.cpp
)
set_property(SOURCE src/loader.cpp PROPERTY COMPILE_FLAGS "-std=c++0x")

## Binary declaration
add_library(${binname} SHARED ${SOURCES})
## Link libraries (@post-job)
target_link_libraries(${binname} ${LIBRARIES})

## Adding static library for single .so configurations
# since target is a shared library, -fPIC must be provided
add_library(${binname}-embedded STATIC ${SOURCES})
target_link_libraries(${binname}-embedded ${LIBRARIES})
set_property(TARGET ${binname}-embedded PROPERTY POSITION_INDEPENDENT_CODE 1)


## Adding extras
# Tell compiler to show all possible warnings
set_target_properties(${binname} PROPERTIES COMPILE_FLAGS "-Wall -Wextra")


## demo
add_executable(demo src/demo/demo.cpp)
target_link_libraries(demo ${LIBRARIES})
configure_file(src/demo/ice.cfg ice.cfg)

## tests
list(APPEND LIBRARIES ${binname})
add_executable(test_stdutils src/tests/test_stdutils.cpp)
set_target_properties(test_stdutils PROPERTIES COMPILE_FLAGS "-std=c++0x")

add_executable(test_loader src/tests/test_loader.cpp)
target_link_libraries(test_loader ${LIBRARIES})

add_executable(test_injector src/tests/test_injector.cpp)
target_link_libraries(test_injector ${LIBRARIES})

add_executable(test_proxy src/tests/test_proxy.cpp)
target_link_libraries(test_proxy ${LIBRARIES} pthread)


### Export package
# declare package to be used externally
set(PROJECT_LIBRARIES
    ${binname}
)
declare_package(${PROJECT_NAME} ${PROJECT_LIBRARIES})
declare_variable(${PROJECT_NAME}_STATIC_LIBRARIES ${binname}-embedded STRINGS)


### Install
install(TARGETS ${binname} ${binname}-embedded
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/jderobot
    COMPONENT lib
)
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    COMPONENT dev
)

