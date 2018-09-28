#ifndef GRAVITY_MADNESS_TUTORIAL_MODULE
#define GRAVITY_MADNESS_TUTORIAL_MODULE

#include "gameplay-settings.hpp"
#include "game-module.hpp"
#include "graphics-module.hpp"
#include <vector>

class GameModule;

class TutorialModule {

public:

    TutorialModule ( GraphicsModule * Graphics, GameModule * Game, GameplaySettings * Gameplay );

    void update ( );
    void update ( sf::Event &Event );
    void render ( sf::RenderWindow &Window );

    bool onTerminate ( );

private:

    static std::string blankUnderscore ( std::string Text );

    Spaceship * getPlayerSpaceship ( );
    Spaceship * getEnemySpaceship ( );

    void reset ( );
    bool loadNextChallenge ( );
    void loadNonStaticDescriptions ( );

private:

    struct Challenge {

        enum EndingConditions {

            None,
            Time,
            InAreaAndNoVelocity,
            PowerUpCaught,
            PowerUpCaughtAndTime,
            NoEnemies

            };

        Challenge ( ) {

            AreaRadius = 300.f;
            AsteroidCount = 0;
            EndingCondition = EndingConditions::None;

            PlayerRay = false;
            PlayerMissile = false;
            Planet = false;
            PlanetMass = 2000000.f;
            PlanetRadius = 150.f;
            Enemy = false;
            LowHealthPowerUpPrototype = nullptr;
            RandomGravityPowerUpPrototype = nullptr; }

        ~ Challenge ( ) {

            delete LowHealthPowerUpPrototype;
            delete RandomGravityPowerUpPrototype; }

        unsigned int Index;
        std::string Title;
        std::string Description;

        float AreaRadius;
        unsigned int AsteroidCount;
        EndingConditions EndingCondition;
        sf::Time TimeLimit;

        sf::Vector2f PlayerPosition;
        sf::Vector2f PlayerVelocity;
        bool PlayerRay;
        bool PlayerMissile;

        bool Planet;
        sf::Vector2f PlanetPosition;
        float PlanetMass;
        float PlanetRadius;

        bool Enemy;
        sf::Vector2f EnemyPosition;
        sf::Vector2f EnemyVelocity;

        LowHealthPowerUp * LowHealthPowerUpPrototype;
        RandomGravityPowerUp * RandomGravityPowerUpPrototype;

        };

    GraphicsModule * Graphics;
    GameModule * Game;
    GameplaySettings * Gameplay;

    bool Terminate;
    sf::Clock Clock;
    uint8_t ChallengeState;
    int ChallengeIndex;
    sf::Time ChallengeTime;

    std::string TitleText;
    unsigned int TitleFontSize;
    float TitlePosition;

    std::string SubTitleText;
    unsigned int SubTitleFontSize;
    float SubTitlePosition;

    std::string ContentText;
    unsigned int ContentFontSize;
    float ContentPosition;

    unsigned int MenuOptionCount;
    unsigned int MenuOption;
    std::string MenuOptionText [2];
    unsigned int MenuOptionFontSize;
    float MenuOptionPosition [2];

    std::vector <Challenge> Challenges;

    };

#endif
