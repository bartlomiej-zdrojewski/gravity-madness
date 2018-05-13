#ifndef GRAVITY_MADNESS_GAME_MODULE
#define GRAVITY_MADNESS_GAME_MODULE

#include <algorithm>
#include <cmath>
#include <list>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "definitions.hpp"
#include "aggressive-ai-controller.hpp"
#include "ai-controller.hpp"
#include "asteroid.hpp"
#include "body.hpp"
#include "energy-power-up.hpp"
#include "gameplay-settings.hpp"
#include "graphics-module.hpp"
#include "missile.hpp"
#include "particle-system.hpp"
#include "planet.hpp"
#include "player-controller.hpp"
#include "player-interface.hpp"
#include "power-up.hpp"
#include "ray.hpp"
#include "spaceship.hpp"

class DebugModule;

class GameModule {

    friend class DebugModule;

public:

    explicit GameModule ( GraphicsModule * Graphics );
    ~ GameModule ( );

    void setGameplay ( GameplaySettings * Gameplay );
    GameplaySettings * getGameplay ( );

    void update ( );
    void update ( sf::Event &Event );
    void render ( sf::RenderWindow &Window );

    void reset ( );
    void terminate ( );

    bool onPause ( );
    bool onTerminate ( );

private:

    void destructBody ( Body * Object );

    float getMinDistance ( sf::Vector2f A, sf::Vector2f B );
    float getDistance ( sf::Vector2f A, sf::Vector2f B );
    float getRandomFloat ( );

    bool isPlayer ( Spaceship * MySpaceship );
    bool isOnScreen ( sf::Vector2f Center, float Radius );
    bool isOnScreen ( sf::FloatRect Area );

    Spaceship * getRayTarget ( Spaceship * Requester, sf::Vector2f &Intersection, bool AffectMissiles = true );
    Spaceship * getAngularTarget ( Spaceship * Requester, float MaximumAngle, float &Distance, float &Angle );
    Spaceship * getAngularTarget ( Missile * Requester, float MaximumAngle );
    PowerUp * detectPowerUp ( Spaceship * Requester, float &Distance, float &Angle );

    void updatePlanets ( sf::Time ElapsedTime );
    void updateAsteroids ( sf::Time ElapsedTime );
    void updateSpaceships ( sf::Time ElapsedTime );
    void updateMissiles ( sf::Time ElapsedTime );
    void updatePowerUps ( sf::Time ElapsedTime );
    void updateRayShots ( sf::Time ElapsedTime );
    void updateParticleSystems ( sf::Time ElapsedTime );

    void updateViews ( );
    void renderViewsOutline ( sf::RenderWindow &Window );

    void prepareAreaLimit ( );
    void renderAreaLimit ( sf::RenderWindow &Window );

private:

    GraphicsModule * Graphics;
    GameplaySettings * Gameplay;

    bool Pause;
    bool EndingCondition;

    sf::Clock Clock;
    float Gravity;
    float DetectionDistance;
    float AreaRadius;
    sf::Time GameplayTime;

    unsigned int PlayerCount;
    const static int MaximumPlayerCount = 4;
    Spaceship * PlayerSpaceship [MaximumPlayerCount];
    unsigned int PlayerScore [MaximumPlayerCount];
    float PlayerScoreMultiplier [MaximumPlayerCount];
    sf::Vector2f PlayerFinalVelocity [MaximumPlayerCount];
    sf::View Views [MaximumPlayerCount];
    PlayerInterface * Interface [MaximumPlayerCount];

    unsigned int AsteroidCount;
    sf::Time AsteroidPauseTime;
    sf::Time AsteroidPauseDuration;

    sf::Time PowerUpPauseTime;
    sf::Time PowerUpPauseDuration;
    PowerUp * GravityPowerUp;
    PowerUp * AsteroidPowerUp;
    const float PowerUpRadius = 15.f;

    std::list <Planet*> Planets;
    std::list <Asteroid*> Asteroids;
    std::list <Spaceship*> Spaceships;
    std::list <Missile*> Missiles;
    std::list <PowerUp*> PowerUps;
    std::list <Ray*> RayShots;
    std::list <ParticleSystem*> ParticleSystems;
    std::vector <sf::Vertex> ViewsOutline;
    std::vector <sf::Vertex> AreaLimit;

    };

#endif