cmake_minimum_required(VERSION 2.8)
project(easyiceconfig)

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
    src/injector.cpp
)
set_property(SOURCE src/loader.cpp PROPERTY COMPILE_FLAGS "-std=c++0x")

set(LIBRARIES
    ${Ice_LIBRARIES}
    boost_regex
)

## Adding shared library for common usage
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

## Adding static library for single .so configurations
# since target is a shared library, -fPIC must be provided
add_library(${PROJECT_NAME}-embedded STATIC ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME}-embedded ${LIBRARIES})
set_property(TARGET ${PROJECT_NAME}-embedded PROPERTY POSITION_INDEPENDENT_CODE 1)

## Export library variables (like find_package)
declare_package(${PROJECT_NAME})
declare_variable(${PROJECT_NAME}_STATIC_LIBRARIES ${PROJECT_NAME}-embedded STRINGS)

## demo
add_executable(demo src/demo/demo.cpp)
target_link_libraries(demo ${LIBRARIES})
configure_file(src/demo/ice.cfg ice.cfg)

## tests
add_executable(test_stdutils src/tests/test_stdutils.cpp)
set_target_properties(test_stdutils PROPERTIES COMPILE_FLAGS "-std=c++0x")

add_executable(test_loader src/tests/test_loader.cpp)
target_link_libraries(test_loader ${PROJECT_NAME} ${LIBRARIES})

add_executable(test_injector src/tests/test_injector.cpp)
target_link_libraries(test_injector ${PROJECT_NAME} ${LIBRARIES})

add_executable(test_proxy src/tests/test_proxy.cpp)
target_link_libraries(test_proxy ${PROJECT_NAME} ${LIBRARIES} pthread)


### Install
install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/jderobot
    COMPONENT lib
)
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    COMPONENT dev
)
