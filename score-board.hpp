#ifndef GRAVITY_MADNESS_SCORE_BOARD_HPP
#define GRAVITY_MADNESS_SCORE_BOARD_HPP

#include <SFML/Graphics.hpp>
#include "graphics-module.hpp"

class ScoreBoard {

public:

    ScoreBoard ( GraphicsModule * Graphics );

    void update ( );
    void update ( sf::Event &Event );
    void render ( sf::RenderWindow &Window );

private:

    GraphicsModule * Graphics;

    };

#endif
