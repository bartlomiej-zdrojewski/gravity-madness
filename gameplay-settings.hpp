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
#include "shape.hpp"

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
        std::string Shape;
        float HealthLimit;
        float HealthRestoration;
        float EnergyLimit;
        float EnergyRestoration;
        float Thrust;
        float BrakingFactor;
        sf::Color FuelColor;
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

        for ( unsigned int i = 0; i < MAXIMUM_PLAYER_COUNT; i++ ) {

            SpaceshipAssignments[i] = -1; }

        PlayerNames[0] = "Faraday"; // Michael Faraday (physics)
        PlayerNames[1] = "Mendel"; // Gregor Mendel (biology)
        PlayerNames[2] = "Lavoisier"; // Marie-Anne Paulze Lavoisier (chemistry)
        PlayerNames[3] = "Euclid"; // Euclid (math)
        PlayerColors[0] = sf::Color( 0, 176, 255 ); // #00B0FF
        PlayerColors[1] = sf::Color( 0, 230, 118 ); // #00E676
        PlayerColors[2] = sf::Color( 255, 145, 0 ); // #FF9100
        PlayerColors[3] = sf::Color( 255, 234, 0 ); // #FFEA00

        loadDefaultSpaceshipPrototypes(); }

    ~ GameplaySettings ( );

    std::string * getPlayerNames ( );
    std::string getPlayerName ( unsigned int Index );
    std::string getTheLongestPlayerName ( );

    sf::Color * getPlayerColors ( );
    sf::Color getPlayerColor ( unsigned int Index );

    void loadSpaceshipPrototypes ( Script * Config );
    std::vector <SpaceshipPrototype> getSpaceshipPrototypes ( );
    SpaceshipPrototype getSpaceshipPrototype ( unsigned int PlayerIndex );
    std::string getTheLongestSpaceshipPrototypeName ( );

    void loadControllersSettingsRegister ( std::string Config );
    PlayerControllerSettings ** getControllersSettingsRegister ( );
    PlayerControllerSettings * getControllerSettings ( unsigned int Index );

    int * getSpaceshipAssignments ( );
    int getSpaceshipAssignment ( unsigned int Index );
    void assignSpaceship ( unsigned int PlayerIndex, int SpaceshipIndex );

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

    std::string PlayerNames [ MAXIMUM_PLAYER_COUNT ];
    sf::Color PlayerColors [ MAXIMUM_PLAYER_COUNT ];
    std::vector <SpaceshipPrototype> SpaceshipPrototypes;
    int SpaceshipAssignments [ MAXIMUM_PLAYER_COUNT ];
    PlayerControllerSettings * ControllersSettingsRegister [ MAXIMUM_PLAYER_COUNT ];

    };

#endif
