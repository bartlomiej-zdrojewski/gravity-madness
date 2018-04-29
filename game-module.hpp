#ifndef GRAVITY_MADNESS_GAME_MODULE
#define GRAVITY_MADNESS_GAME_MODULE

#include <list>
#include <cmath>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "graphics-module.hpp"
#include "body.hpp"
#include "planet.hpp"
#include "spaceship.hpp"
#include "player-interface.hpp"
#include "player-controller.hpp"
#include "ai-controller.hpp"

// Asteroid
// Missile
// PowerUp
// ParticleSystem / ParticleEffect

class GameModule {

public:

    explicit GameModule ( GraphicsModule * Graphics );
    ~ GameModule ( );

    void update ( );
    void update ( sf::Event &Event );
    void render ( sf::RenderWindow &Window );

private:

    void destructBody ( Body * Object );

    float getMinDistance ( sf::Vector2f A, sf::Vector2f B );
    float getDistance ( sf::Vector2f A, sf::Vector2f B );

    Body * getRayTarget ( sf::Vector2f Position, float Angle );
    Body * getAngularTarget ( sf::Vector2f Position, sf::Vector2f Angle );

    void updatePlanets ( sf::Time ElapsedTime );
    void updateSpaceships ( sf::Time ElapsedTime );

private:

    GraphicsModule * Graphics;

    unsigned int PlayerCount;
    const static int MaximumPlayerCount = 4;
    Spaceship * PlayerSpaceship [MaximumPlayerCount];
    PlayerInterface * Interface [MaximumPlayerCount];

    sf::Clock Clock;
    float Gravity;

    std::list <Planet*> Planets;
    std::list <Spaceship*> Spaceships;

    };

#endif