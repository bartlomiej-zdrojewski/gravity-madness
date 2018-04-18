cmake_minimum_required(VERSION 3.8)
project(gravity_madness)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

set(CMAKE_BUILD_TYPE RELEASE)
set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_ROOT "C:/Development/SFML-2.4.2")
set(CMAKE_MODULE_PATH "${SFML_ROOT}/cmake/Modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 COMPONENTS audio graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

#if(WIN32)
#    SET(GUI_TYPE WIN32)
#endif()

set(SOURCE_FILES pugixml/pugixml.cpp main.cpp world-module.cpp graphics-module.cpp logger.cpp loger-manager.cpp script.cpp)
set(HEADER_FILES pugixml/pugiconfig.hpp pugixml/pugixml.hpp gravity-madness.hpp world-module.hpp graphics-module.hpp script.hpp logger.hpp logger-manager.hpp)

add_executable(gravity_madness ${GUI_TYPE} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(gravity_madness ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

add_custom_command(TARGET gravity_madness PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/config $<TARGET_FILE_DIR:gravity_madness>/config)
add_custom_command(TARGET gravity_madness PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:gravity_madness>/assets)

if(WIN32)
    add_custom_command(TARGET gravity_madness PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/openal32.dll $<TARGET_FILE_DIR:gravity_madness>/openal32.dll)
endif()