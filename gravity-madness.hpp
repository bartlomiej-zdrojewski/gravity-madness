#ifndef GRAVITY_MADNESS
#define GRAVITY_MADNESS

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "body.hpp"
#include "constants.hpp"
#include "controllers/aggressive-ai-controller.hpp"
#include "controllers/ai-controller.hpp"
#include "controllers/player-controller.hpp"
#include "controllers/spaceship-controller.hpp"
#include "game-module.hpp"
#include "graphics-module.hpp"
#include "logger.hpp"
#include "logger-manager.hpp"
#include "particle-system.hpp"
#include "planet.hpp"
#include "player-interface.hpp"
#include "ray.hpp"
#include "script.hpp"
#include "spaceship.hpp"
#include "world-module.hpp"

#if defined(WIN32)
    #include <windows.h>
#elif defined(unix) || defined(__unix) || defined(__unix__)
    #include <iostream>
#endif

#endif