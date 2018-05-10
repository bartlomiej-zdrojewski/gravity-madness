#ifndef GRAVITY_MADNESS_DEBUG_MODULE_HPP
#define GRAVITY_MADNESS_DEBUG_MODULE_HPP

#include <SFML/Graphics.hpp>
#include "game-module.hpp"
#include "graphics-module.hpp"
#include "logger.hpp"

class GameModule;

class DebugModule : public Logger {

public:

    DebugModule ( GraphicsModule * Graphics, GameModule * Game ) : Logger ( ) {

        this->Graphics = Graphics;
        this->Game = Game;

        }

private:

    GraphicsModule * Graphics;
    GameModule * Game;

    };

#endif
