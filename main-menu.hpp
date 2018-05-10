#ifndef GRAVITY_MADNESS_MAIN_MENU_HPP
#define GRAVITY_MADNESS_MAIN_MENU_HPP

#include <SFML/Graphics.hpp>
#include "gameplay-settings.hpp"
#include "graphics-module.hpp"

class MainMenu {

public:

    MainMenu ( GraphicsModule * Graphics, GameplaySettings * Gameplay );

    void update ( );
    void update ( sf::Event &Event );
    void render ( sf::RenderWindow &Window );

private:

    GraphicsModule * Graphics;
    GameplaySettings * Gameplay;

    };

#endif
