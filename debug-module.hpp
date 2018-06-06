#ifndef GRAVITY_MADNESS_DEBUG_MODULE_HPP
#define GRAVITY_MADNESS_DEBUG_MODULE_HPP

#include <SFML/Graphics.hpp>
#include "game-module.hpp"
#include "graphics-module.hpp"
#include "logger.hpp"

class GameModule;

class DebugModule : public Logger {

public:

    DebugModule ( GraphicsModule * Graphics, GameModule * Game ) : Logger ( ) {

        this->Graphics = Graphics;
        this->Game = Game;

        Terminate = false;

        TestIndex = 0;
        TestTitle[0] = "Normal Gravity Test";
        TestTitle[1] = "Low Gravity Test";
        TestTitle[2] = "High Gravity Test";
        TestTitle[3] = "Asteroid-Asteroid Collision Test";
        TestTitle[4] = "Spaceship-Asteroid Collision Test";
        TestTitle[5] = "Spaceship-Spaceship Collision Test";
        TestTitle[6] = "Missile Tracking Test";
        TestDuration[0] = sf::seconds( 15.f );
        TestDuration[1] = sf::seconds( 15.f );
        TestDuration[2] = sf::seconds( 8.f );
        TestDuration[3] = sf::seconds( 10.f );
        TestDuration[4] = sf::seconds( 7.f );
        TestDuration[5] = sf::seconds( 8.f );
        TestDuration[6] = sf::seconds( 5.f );

            prepareTest(); }

    void update ( );
    void update ( sf::Event &Event );
    void render ( sf::RenderWindow &Window );

    bool onTerminate ( );

private:

    void prepareTest ( );
    Planet * getPlanet ( );
    Asteroid * getAsteroid ( );
    Spaceship * getSpaceship ( );
    Missile * getMissile ( );

private:

    GraphicsModule * Graphics;
    GameModule * Game;

    bool Terminate;
    sf::Clock Clock;

    unsigned int TestIndex;
    const static unsigned int TestCount = 7;
    std::string TestTitle [TestCount];
    sf::Time TestDuration [TestCount];

    };

#endif
