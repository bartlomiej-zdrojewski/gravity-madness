#ifndef GRAVITY_MADNESS_PAUSE_MENU_HPP
#define GRAVITY_MADNESS_PAUSE_MENU_HPP

#include <SFML/Graphics.hpp>
#include "graphics-module.hpp"

class PauseMenu {

public:

    PauseMenu ( GraphicsModule * Graphics );

    void update ( );
    void update ( sf::Event &Event );
    void render ( sf::RenderWindow &Window );

private:

    GraphicsModule * Graphics;

    };

#endif
