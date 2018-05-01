#ifndef GRAVITY_MADNESS_GAME_MODULE
#define GRAVITY_MADNESS_GAME_MODULE

#include <list>
#include <cmath>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "definitions.hpp"
#include "graphics-module.hpp"
#include "body.hpp"
#include "planet.hpp"
#include "spaceship.hpp"
#include "player-interface.hpp"
#include "player-controller.hpp"
#include "ai-controller.hpp"
#include "aggressive-ai-controller.hpp"
#include "particle-system.hpp"

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

    bool isPlayer ( Spaceship * MySpaceship );
    bool isOnScreen ( sf::Vector2f Center, float Radius );

    Spaceship * getRayTarget ( Spaceship * Requester, sf::Vector2f &Intersection );
    Spaceship * getAngularTarget ( Spaceship * Requester, float MaximumAngle, float &Distance, float &Angle );

    void updatePlanets ( sf::Time ElapsedTime );
    void updateSpaceships ( sf::Time ElapsedTime );
    void updateRayShots ( sf::Time ElapsedTime );
    void updateMissiles ( sf::Time ElapsedTime );
    void updatePowerUps ( sf::Time ElapsedTime );
    void updateParticleSystems ( sf::Time ElapsedTime );

private:

    GraphicsModule * Graphics;

    unsigned int PlayerCount;
    const static int MaximumPlayerCount = 4;
    Spaceship * PlayerSpaceship [MaximumPlayerCount];
    PlayerInterface * Interface [MaximumPlayerCount];

    sf::Clock Clock;
    float Gravity;
    float DetectionDistance;

    std::list <Planet*> Planets;
    std::list <Spaceship*> Spaceships;
    std::list <Ray*> RayShots;
    std::list <ParticleSystem*> ParticleSystems;

    };

#endif