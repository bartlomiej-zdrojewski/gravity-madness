#ifndef GRAVITY_MADNESS_MESSAGE_HPP
#define GRAVITY_MADNESS_MESSAGE_HPP

#include <SFML/Graphics.hpp>
#include "graphics-module.hpp"

class Message {

public:

    Message ( GraphicsModule * Graphics );

    void update ( );
    void update ( sf::Event &Event );
    void render ( sf::RenderWindow &Window );

private:

    GraphicsModule * Graphics;

    };

#endif
