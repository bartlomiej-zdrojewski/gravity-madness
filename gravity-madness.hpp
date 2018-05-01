#ifndef GRAVITY_MADNESS
#define GRAVITY_MADNESS

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "aggressive-ai-controller.hpp"
#include "ai-controller.hpp"
#include "body.hpp"
#include "definitions.hpp"
#include "game-module.hpp"
#include "graphics-module.hpp"
#include "logger.hpp"
#include "logger-manager.hpp"
#include "particle-system.hpp"
#include "planet.hpp"
#include "player-controller.hpp"
#include "player-interface.hpp"
#include "ray.hpp"
#include "script.hpp"
#include "spaceship.hpp"
#include "spaceship-controller.hpp"
#include "world-module.hpp"

#if defined(WIN32)
    #include <windows.h>
#elif defined(unix) || defined(__unix) || defined(__unix__)
    #include <iostream>
#endif

#endif