#ifndef GRAVITY_MADNESS_GAMEPLAY
#define GRAVITY_MADNESS_GAMEPLAY

#include <sstream>
#include <vector>
#include <SFML/System.hpp>
#include "constants.hpp"
#include "controllers/player-controller-settings.hpp"
#include "logger.hpp"
#include "score-counter.hpp"
#include "script.hpp"

class GameplaySettings : public Logger {

public:

    enum AreaSizes {

        Tiny = 1500,
        Small = 2000,
        Medium = 2500,
        Big = 3000,
        Huge = 3500

        };

    enum AsteroidFrequencies {

        Rarely,
        Occasionally,
        Often

        };

    enum AIPersonalities {

        Random,
        Passive,
        Reasonable,
        Aggressive

        };

    enum EndingConditions {

        Time,
        NoEnemies,
        LastPlayer,
        LastSpaceship

        };

    struct SpaceshipPrototype {

        std::string Name;
        std::string Texture;
        std::string AccentTexture;
        float Mass;
        float Radius;
        float HealthLimit;
        float HealthRestoration;
        float EnergyLimit;
        float EnergyRestoration;
        float Thrust;
        float SuppressingFactor;
        sf::Color ExhaustColor;
        float RayPower;
        sf::Color RayColor;
        unsigned int MissileCount;
        unsigned int MissileLimit;
        float ScoreMultiplier;

        };

    GameplaySettings ( ) : Logger ( ) {

        AreaSize = AreaSizes::Medium;
        AsteroidFrequency = AsteroidFrequencies::Occasionally;
        SpaceshipCount = 15;
        PlayerCount = 1;
        AIPersonality = AIPersonalities::Random;
        EndingCondition = EndingConditions::NoEnemies;
        TimeLimit = sf::seconds( 5.f * 60.f );
        Winner = 0;

        loadDefaultSpaceshipPrototypes(); }

    ~ GameplaySettings ( );

    void loadSpaceshipPrototypes ( Script * Config );
    void assignSpaceships ( std::vector <int> SpaceshipAssignment );
    std::vector <SpaceshipPrototype> getSpaceshipPrototypes ( );
    SpaceshipPrototype getSpaceshipPrototype ( unsigned int Index );

    void loadPlayerControllerSettingsRegister ( std::string Config );
    PlayerControllerSettings ** getPlayerControllerSettingsRegister ( );
    PlayerControllerSettings * getPlayerControllerSettings ( unsigned int Index );

    float getAreaSize ( );
    std::string getAreaSizeText ( );
    void setAreaSize ( AreaSizes AreaSize );
    void setNextAreaSize ( );
    void setPreviousAreaSize ( );

    AsteroidFrequencies getAsteroidFrequency ( );
    std::string getAsteroidFrequencyText ( );
    void setAsteroidFrequency ( AsteroidFrequencies AsteroidFrequency );
    void setNextAsteroidFrequency ( );
    void setPreviousAsteroidFrequency ( );

    unsigned int getPlayerCount ( );
    void setPlayerCount ( unsigned int PlayerCount );

    unsigned int getSpaceshipCount ( );
    void setSpaceshipCount ( unsigned int SpaceshipCount );

    AIPersonalities getAIPersonality ( );
    std::string getAIPersonalityText ( );
    void setAIPersonality ( AIPersonalities AIPersonality );
    void setNextAIPersonality ( );
    void setPreviousAIPersonality ( );

    EndingConditions getEndingCondition ( );
    std::string getEndingConditionText ( );
    void setEndingCondition ( EndingConditions EndingCondition );
    void setNextEndingCondition ( );
    void setPreviousEndingCondition ( );

    sf::Time getTimeLimit ( );
    void setTimeLimit ( sf::Time TimeLimit );

    ScoreCounter * getScores ( );

    unsigned char getWinner ( );
    void setWinner ( unsigned char Winner );

private:

    void loadDefaultSpaceshipPrototypes ( );

private:

    AreaSizes AreaSize;
    AsteroidFrequencies AsteroidFrequency;
    unsigned int PlayerCount;
    unsigned int SpaceshipCount;
    AIPersonalities AIPersonality;
    EndingConditions EndingCondition;
    sf::Time TimeLimit;

    ScoreCounter Scores [ MAXIMUM_PLAYER_COUNT ];
    unsigned char Winner;

    std::vector <SpaceshipPrototype> SpaceshipPrototypes;
    std::vector <int> SpaceshipAssignment;
    PlayerControllerSettings * PlayerControllerSettingsRegister [ MAXIMUM_PLAYER_COUNT ];

    };

#endif
