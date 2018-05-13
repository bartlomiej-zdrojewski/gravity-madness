#ifndef GRAVITY_MADNESS_PAUSE_MENU_HPP
#define GRAVITY_MADNESS_PAUSE_MENU_HPP

#include <SFML/Graphics.hpp>
#include "graphics-module.hpp"

class PauseMenu {

public:

    explicit PauseMenu ( GraphicsModule * Graphics );

    void update ( );
    void update ( sf::Event &Event );
    void render ( sf::RenderWindow &Window );

    bool onClose ( );
    bool onTerminate ( );

private:

    GraphicsModule * Graphics;

    bool Close;
    bool Terminate;

    };

#endif
