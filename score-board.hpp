#ifndef GRAVITY_MADNESS_SCORE_BOARD_HPP
#define GRAVITY_MADNESS_SCORE_BOARD_HPP

#include <SFML/Graphics.hpp>
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
