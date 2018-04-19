#ifndef GRAVITY_MADNESS_GAME_MODULE
#define GRAVITY_MADNESS_GAME_MODULE

#include "graphics-module.hpp"

class GameModule {

public:

    GameModule ( GraphicsModule * Graphics );
    ~ GameModule ( );

    void update ( );
    void update ( sf::Event &Event );
    void render ( sf::RenderWindow &Window );

private:

    GraphicsModule * Graphics;

    };

#endif
