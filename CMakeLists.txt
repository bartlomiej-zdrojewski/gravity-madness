cmake_minimum_required(VERSION 3.5)
project(gravity-madness)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE RELEASE)

if(WIN32) # TODO fix version 2.2

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
    set(SFML_STATIC_LIBRARIES TRUE)

    #set(GUI_TYPE WIN32) # Comment to launch with the console
    set(SFML_PATH "C:/Development/SFML-2.5.0-64") # Put your own path to SFML 2.x directory

    if(EXISTS ${SFML_PATH})

        if(EXISTS "${SFML_PATH}/lib/cmake/SFML") # SFML 2.5 or higher

            set(SFML_MODERN_LINKING TRUE)
            set(SFML_DIR "${SFML_PATH}/lib/cmake/SFML")

        elseif(EXISTS "${SFML_PATH}/cmake/Modules/FindSFML.cmake") # SFML 2.4 or lower

            set(SFML_MODERN_LINKING FALSE)
            set(SFML_ROOT "${SFML_PATH}")
            set(CMAKE_MODULE_PATH "${SFML_ROOT}/cmake/Modules" ${CMAKE_MODULE_PATH})

        else()

            message( FATAL_ERROR "Path to SFML 2.x directory is valid, but it does not contain '/lib/cmake/SFML/SFMLConfig.cmake' nor "
                    "'/cmake/Modules/FindSFML.cmake' file! Try to reinstall the library, preferably the 2.5 version." )

        endif()

        find_package(SFML 2 COMPONENTS audio graphics window system REQUIRED)
        include_directories(${SFML_INCLUDE_DIR})

    else()

        message( FATAL_ERROR "Path to SFML 2.x directory is invalid! Did you forget to change it in the 14th line of 'CMakeLists.txt' file? "
                "If not, install SFML 2.5 from:\nhttps://www.sfml-dev.org/download/sfml/2.5.0/\nand then modify 'CMakeLists.txt' file." )

    endif()

elseif(UNIX)

    set(SFML_MODERN_LINKING FALSE)
    set(SFML_LIBRARIES "-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system") # Remember to install libsfml-dev package

endif()

set(PUGIXML_SOURCE_FILES pugixml/pugixml.cpp)
set(MODULE_SOURCE_FILES main.cpp world-module.cpp graphics-module.cpp game-module.cpp debug-module.cpp tutorial-module.cpp)
set(CONTROLLER_SOURCE_FILES controllers/spaceship-controller.cpp controllers/player-controller.cpp controllers/ai-controller.cpp controllers/aggressive-ai-controller.cpp controllers/reasonable-ai-controller.cpp controllers/passive-ai-controller.cpp controllers/player-controller-settings.cpp)
set(POWER_UP_SOURCE_FILES power-ups/power-up.cpp power-ups/low-health-power-up.cpp power-ups/high-health-power-up.cpp power-ups/low-energy-power-up.cpp power-ups/high-energy-power-up.cpp power-ups/missile-power-up.cpp power-ups/no-asteroids-power-up.cpp power-ups/more-asteroids-power-up.cpp power-ups/low-gravity-power-up.cpp power-ups/high-gravity-power-up.cpp power-ups/random-gravity-power-up.cpp)
set(OTHER_SOURCE_FILES logger.cpp logger-manager.cpp script.cpp spaceship.cpp planet.cpp body.cpp interface.cpp ray.cpp particle-system.cpp asteroid.cpp missile.cpp body-collision.cpp gameplay-settings.cpp message.cpp main-menu.cpp pause-menu.cpp score-counter.cpp shape.cpp)

set(PUGIXML_HEADER_FILES pugixml/pugiconfig.hpp pugixml/pugixml.hpp)
set(MODULE_HEADER_FILES gravity-madness.hpp world-module.hpp graphics-module.hpp game-module.hpp debug-module.hpp tutorial-module.hpp)
set(CONTROLLER_HEADER_FILES controllers/spaceship-controller.hpp controllers/player-controller.hpp controllers/ai-controller.hpp controllers/aggressive-ai-controller.hpp controllers/reasonable-ai-controller.hpp controllers/passive-ai-controller.hpp controllers/player-controller-settings.hpp controllers/visualization-controller.hpp controllers/visualization-controller.cpp)
set(POWER_UP_HEADER_FILES power-ups/power-up.hpp power-ups/low-health-power-up.hpp power-ups/high-health-power-up.hpp power-ups/low-energy-power-up.hpp power-ups/high-energy-power-up.hpp power-ups/missile-power-up.hpp power-ups/no-asteroids-power-up.hpp power-ups/more-asteroids-power-up.hpp power-ups/low-gravity-power-up.hpp power-ups/high-gravity-power-up.hpp power-ups/random-gravity-power-up.hpp)
set(OTHER_HEADER_FILES script.hpp logger.hpp logger-manager.hpp body.hpp planet.hpp spaceship.hpp interface.hpp constants.hpp ray.hpp particle-system.hpp asteroid.hpp missile.hpp body-collision.hpp gameplay-settings.hpp main-menu.hpp pause-menu.hpp score-board.hpp message.hpp score-board.cpp score-counter.hpp shape.hpp)

set(SOURCE_FILES ${PUGIXML_SOURCE_FILES} ${MODULE_SOURCE_FILES} ${CONTROLLER_SOURCE_FILES} ${POWER_UP_SOURCE_FILES} ${OTHER_SOURCE_FILES})
set(HEADER_FILES ${PUGIXML_HEADER_FILES} ${MODULE_HEADER_FILES} ${CONTROLLER_HEADER_FILES} ${POWER_UP_HEADER_FILES} ${OTHER_HEADER_FILES})

add_executable(gravity-madness ${GUI_TYPE} ${SOURCE_FILES} ${HEADER_FILES})

if (SFML_MODERN_LINKING)

    target_link_libraries(gravity-madness sfml-audio sfml-graphics sfml-window sfml-system)

else()

    target_link_libraries(gravity-madness ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

endif()

add_custom_command(TARGET gravity-madness POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:gravity-madness>/assets)

if(WIN32)

    add_custom_command(TARGET gravity-madness POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/openal32.dll $<TARGET_FILE_DIR:gravity-madness>/openal32.dll)

endif()