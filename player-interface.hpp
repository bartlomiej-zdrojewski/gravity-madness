#ifndef GRAVITY_MADNESS_PLAYER_INTERFACE
#define GRAVITY_MADNESS_PLAYER_INTERFACE

#include <SFML/Graphics.hpp>

#include "graphics-module.hpp"
#include "spaceship.hpp"

class PlayerInterface {

public:

    enum Orientations {

        Left,
        Right

        };

    PlayerInterface ( GraphicsModule * Graphics );

    void setSpaceship ( Spaceship * MySpaceship );
    void setViewport ( sf::FloatRect Viewport );
    void setOrientation ( Orientations Orientation );

    void update ( );
    void render ( sf::RenderWindow &Window );

private:

    void renderEnergyBar ( sf::RenderWindow &Window );
    void renderMissileBar ( sf::RenderWindow &Window );
    void renderScoreBar ( sf::RenderWindow &Window );

private:

    GraphicsModule * Graphics;

    Spaceship * MySpaceship;
    sf::FloatRect Viewport;
    Orientations Orientation;

    float Energy;

    };

#endif
