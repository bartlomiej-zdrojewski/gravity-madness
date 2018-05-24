#ifndef GRAVITY_MADNESS_PAUSE_MENU_HPP
#define GRAVITY_MADNESS_PAUSE_MENU_HPP

#include <cmath>
#include <SFML/Graphics.hpp>
#include "graphics-module.hpp"

class PauseMenu {

public:

    explicit PauseMenu ( GraphicsModule * Graphics );

    void update ( );
    void update ( sf::Event &Event );
    void render ( sf::RenderWindow &Window );

    bool onClose ( );
    bool onReset ( );
    bool onTerminate ( );

private:

    void renderBackground ( sf::RenderWindow &Window );

private:

    GraphicsModule * Graphics;

    bool Close;
    bool Reset;
    bool Terminate;

    unsigned int Option;
    unsigned int OptionCount;
    std::string OptionText [3];
    unsigned int OptionFontSize;
    sf::Vector2f OptionPosition [3];

    };

#endif
