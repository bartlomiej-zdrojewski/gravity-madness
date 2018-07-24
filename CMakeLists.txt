cmake_minimum_required(VERSION 3.5)
project(gravity_madness)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE RELEASE)

if(WIN32)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
    set(SFML_STATIC_LIBRARIES TRUE)

    set(SFML_ROOT "C:/Development/SFML-2.4.2") # Put your own path to SFML directory
    set(CMAKE_MODULE_PATH "${SFML_ROOT}/cmake/Modules" ${CMAKE_MODULE_PATH})

    find_package(SFML 2 COMPONENTS audio graphics window system REQUIRED)
    include_directories(${SFML_INCLUDE_DIR})

    #SET(GUI_TYPE WIN32)

elseif(UNIX)

    set(SFML_LIBRARIES "-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system") # Remember to install libsfml-dev package

endif()

set(PUGIXML_SOURCE_FILES pugixml/pugixml.cpp)
set(MODULE_SOURCE_FILES main.cpp world-module.cpp graphics-module.cpp game-module.cpp debug-module.cpp)
set(CONTROLLER_SOURCE_FILES controllers/spaceship-controller.cpp controllers/player-controller.cpp controllers/ai-controller.cpp controllers/aggressive-ai-controller.cpp controllers/reasonable-ai-controller.cpp controllers/passive-ai-controller.cpp controllers/player-controller-settings.cpp)
set(POWER_UP_SOURCE_FILES power-ups/power-up.cpp power-ups/low-health-power-up.cpp power-ups/high-health-power-up.cpp power-ups/low-energy-power-up.cpp power-ups/high-energy-power-up.cpp power-ups/missile-power-up.cpp power-ups/no-asteroids-power-up.cpp power-ups/more-asteroids-power-up.cpp power-ups/low-gravity-power-up.cpp power-ups/high-gravity-power-up.cpp power-ups/random-gravity-power-up.cpp)
set(OTHER_SOURCE_FILES logger.cpp loger-manager.cpp script.cpp spaceship.cpp planet.cpp body.cpp player-interface.cpp ray.cpp particle-system.cpp asteroid.cpp missile.cpp body-collision.cpp gameplay-settings.cpp message.cpp main-menu.cpp pause-menu.cpp)

set(PUGIXML_HEADER_FILES pugixml/pugiconfig.hpp pugixml/pugixml.hpp)
set(MODULE_HEADER_FILES gravity-madness.hpp world-module.hpp graphics-module.hpp game-module.hpp debug-module.hpp)
set(CONTROLLER_HEADER_FILES controllers/spaceship-controller.hpp controllers/player-controller.hpp controllers/ai-controller.hpp controllers/aggressive-ai-controller.hpp controllers/reasonable-ai-controller.hpp controllers/passive-ai-controller.hpp controllers/player-controller-settings.hpp)
set(POWER_UP_HEADER_FILES power-ups/power-up.hpp power-ups/low-health-power-up.hpp power-ups/high-health-power-up.hpp power-ups/low-energy-power-up.hpp power-ups/high-energy-power-up.hpp power-ups/missile-power-up.hpp power-ups/no-asteroids-power-up.hpp power-ups/more-asteroids-power-up.hpp power-ups/low-gravity-power-up.hpp power-ups/high-gravity-power-up.hpp power-ups/random-gravity-power-up.hpp)
set(OTHER_HEADER_FILES script.hpp logger.hpp logger-manager.hpp body.hpp planet.hpp spaceship.hpp player-interface.hpp constants.hpp ray.hpp particle-system.hpp asteroid.hpp missile.hpp body-collision.hpp gameplay-settings.hpp main-menu.hpp pause-menu.hpp score-board.hpp message.hpp score-board.cpp)

set(SOURCE_FILES ${PUGIXML_SOURCE_FILES} ${MODULE_SOURCE_FILES} ${CONTROLLER_SOURCE_FILES} ${POWER_UP_SOURCE_FILES} ${OTHER_SOURCE_FILES})
set(HEADER_FILES ${PUGIXML_HEADER_FILES} ${MODULE_HEADER_FILES} ${CONTROLLER_HEADER_FILES} ${POWER_UP_HEADER_FILES} ${OTHER_HEADER_FILES})

add_executable(gravity_madness ${GUI_TYPE} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(gravity_madness ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

add_custom_command(TARGET gravity_madness PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:gravity_madness>/assets)

if(WIN32)

    add_custom_command(TARGET gravity_madness PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/openal32.dll $<TARGET_FILE_DIR:gravity_madness>/openal32.dll)

endif()