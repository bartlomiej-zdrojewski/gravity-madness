#ifndef GRAVITY_MADNESS_SCORE_BOARD
#define GRAVITY_MADNESS_SCORE_BOARD

#include "gameplay-settings.hpp"
#include "graphics-module.hpp"

class ScoreBoard {

public:

    ScoreBoard ( GraphicsModule * Graphics, GameplaySettings * Gameplay );

    void update ( );
    void update ( sf::Event &Event );
    void render ( sf::RenderWindow &Window );

    bool onClose ( );

private:

    GraphicsModule * Graphics;
    GameplaySettings * Gameplay;

    bool Close;

    };

#endif
