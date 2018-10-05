#ifndef GRAVITY_MADNESS
#define GRAVITY_MADNESS

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#if ( SFML_VERSION_MINOR < 2 )
    #warning "The oldest tested version of SFML is 2.2, therefore the older ones may not work as expected. For the best result try the 2.5 version."
#elif ( SFML_VERSION_MINOR > 5 )
    #warning "The newest tested version of SFML is 2.5, therefore the newer ones may not work as expected. For the best result try the 2.5 version."
#endif

#include "asteroid.hpp"
#include "body.hpp"
#include "body-collision.hpp"
#include "constants.hpp"
#include "controllers/aggressive-ai-controller.hpp"
#include "controllers/ai-controller.hpp"
#include "controllers/player-controller.hpp"
#include "controllers/player-controller-settings.hpp"
#include "controllers/reasonable-ai-controller.hpp"
#include "controllers/spaceship-controller.hpp"
#include "controllers/visualization-controller.hpp"
#include "game-module.hpp"
#include "gameplay-settings.hpp"
#include "graphics-module.hpp"
#include "interface.hpp"
#include "logger.hpp"
#include "logger-manager.hpp"
#include "message.hpp"
#include "missile.hpp"
#include "particle-system.hpp"
#include "pause-menu.hpp"
#include "planet.hpp"
#include "ray.hpp"
#include "score-board.hpp"
#include "score-counter.hpp"
#include "script.hpp"
#include "shape.hpp"
#include "spaceship.hpp"
#include "tutorial-module.hpp"
#include "world-module.hpp"

#if defined(WIN32)
    #include <windows.h>
#elif defined(unix) || defined(__unix) || defined(__unix__)
    #include <iostream>
#endif

#endif