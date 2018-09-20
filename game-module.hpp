#ifndef GRAVITY_MADNESS_GAME_MODULE
#define GRAVITY_MADNESS_GAME_MODULE

#include <algorithm>
#include <cmath>
#include <list>
#include <random>
#include "asteroid.hpp"
#include "body.hpp"
#include "constants.hpp"
#include "controllers/aggressive-ai-controller.hpp"
#include "controllers/ai-controller.hpp"
#include "controllers/passive-ai-controller.hpp"
#include "controllers/player-controller.hpp"
#include "controllers/reasonable-ai-controller.hpp"
#include "gameplay-settings.hpp"
#include "graphics-module.hpp"
#include "missile.hpp"
#include "particle-system.hpp"
#include "planet.hpp"
#include "player-interface.hpp"
#include "power-ups/high-energy-power-up.hpp"
#include "power-ups/high-gravity-power-up.hpp"
#include "power-ups/high-health-power-up.hpp"
#include "power-ups/low-gravity-power-up.hpp"
#include "power-ups/low-energy-power-up.hpp"
#include "power-ups/low-health-power-up.hpp"
#include "power-ups/missile-power-up.hpp"
#include "power-ups/more-asteroids-power-up.hpp"
#include "power-ups/no-asteroids-power-up.hpp"
#include "power-ups/power-up.hpp"
#include "power-ups/random-gravity-power-up.hpp"
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

    static float getMinDistance ( sf::Vector2f A, sf::Vector2f B );
    static float getDistance ( sf::Vector2f A, sf::Vector2f B );
    static float getRandomFloat ( );

    bool isPlayer ( Spaceship * MySpaceship );
    bool isOnScreen ( sf::Vector2f Center, float Radius );
    bool isOnScreen ( sf::FloatRect Area );

    unsigned int getAlivePlayerCount ( );
    int getLastAlivePlayer ( );

    void destructBody ( Body * Object );
    void displayNotification ( std::string Message );

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
    void updateIntentionalCollisions ( sf::Time ElapsedTime );
    void updateIntentionalCollisions ( Spaceship * DestructedSpaceship );

    void updateViews ( );
    void renderViewsOutline ( sf::RenderWindow &Window );

    void initAreaLimit ( );
    void renderAreaLimit ( sf::RenderWindow &Window );

private:

    struct IntentionalCollision {

        Spaceship * Target;
        ScoreCounter * Score;
        sf::Time Time;

        };

    GraphicsModule * Graphics;
    GameplaySettings * Gameplay;

    bool Pause;
    bool EndingCondition;

    sf::Clock Clock;
    float Gravity;
    float DetectionDistance;
    float AreaRadius;
    sf::Time GameplayTime;
    float ScoreMultiplier;
    sf::Time IntentionalCollisionDuration;
    sf::Time SkipProtectionTime;

    unsigned int PlayerCount;
    Spaceship * PlayerSpaceship [ MAXIMUM_PLAYER_COUNT ];
    ScoreCounter * PlayerScore [ MAXIMUM_PLAYER_COUNT ];
    sf::Vector2f PlayerFinalVelocity [ MAXIMUM_PLAYER_COUNT ];
    sf::View Views [ MAXIMUM_PLAYER_COUNT ];
    PlayerInterface * Interface [ MAXIMUM_PLAYER_COUNT ];

    unsigned int AsteroidCount;
    sf::Time AsteroidPauseTime;
    sf::Time AsteroidPauseDuration;

    unsigned int PowerUpLimit;
    sf::Time PowerUpPauseTime;
    sf::Time PowerUpPauseDuration;
    PowerUp * GravityPowerUp;
    PowerUp * AsteroidPowerUp;

    std::list <Planet*> Planets;
    std::list <Asteroid*> Asteroids;
    std::list <Spaceship*> Spaceships;
    std::list <Missile*> Missiles;
    std::list <PowerUp*> PowerUps;
    std::list <Ray*> RayShots;
    std::list <ParticleSystem*> ParticleSystems;
    std::list <IntentionalCollision*> IntentionalCollisions;
    std::vector <sf::Vertex> ViewsOutline;
    std::vector <sf::Vertex> AreaLimit;

    };

#endif