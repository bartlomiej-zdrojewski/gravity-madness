#ifndef GRAVITY_MADNESS_GAMEPLAY_HPP
#define GRAVITY_MADNESS_GAMEPLAY_HPP

#include <vector>
#include "script.hpp"

class GameplaySettings {

public:

    enum AreaSizes {

        Small = 1500,
        Medium = 2500,
        Huge = 3500

        };

    enum AIPersonalities {

        Random,
        Aggressive,
        Reasonable,
        Passive

        };

    enum EndingConditions {

        // TODO

        };

    struct SpaceshipPrototype {

        std::string Name;
        float Mass;
        float Radius;
        float HealthLimit;
        float HealthRestoration;
        float EnergyLimit;
        float EnergyRestoration;
        float Thrust;
        float SuppressingFactor;
        float RayPower;
        unsigned int MissileCount;
        unsigned int MissileLimit;

        };

    GameplaySettings ( );
    ~ GameplaySettings ( );

    void loadSpaceshipPrototypes ( Script * Config );
    void assignSpaceshipPrototypes ( std::vector <int> SpaceshipPrototypesAssignment );

    std::vector <SpaceshipPrototype> getSpaceshipPrototypes ( );
    SpaceshipPrototype getSpaceshipPrototype ( unsigned int Index );

    float getAreaSize ( );
    void setAreaSize ( AreaSizes AreaSize );

    unsigned int getAsteroidCount ( );
    void setAsteroidCount ( unsigned int AsteroidCount );

    unsigned int getSpaceshipCount ( );
    void setSpaceshipCount ( unsigned int SpaceshipCount );

    unsigned int getPlayerCount ( );
    void setPlayerCount ( unsigned int PlayerCount );

    AIPersonalities getAIPersonality ( );
    void setAIPersonality ( AIPersonalities AIPersonality );

    EndingConditions getEndingCondition ( );
    void setEndingCondition ( EndingConditions EndingCondition );

    unsigned int * getScore ( );
    void setScore ( unsigned int * Score );

private:

    AreaSizes AreaSize;
    unsigned int AsteroidCount;
    unsigned int SpaceshipCount;
    unsigned int PlayerCount;
    AIPersonalities AIPersonality;
    EndingConditions EndingCondition;
    unsigned int * Score;

    std::vector <SpaceshipPrototype> SpaceshipPrototypes;
    std::vector <int> SpaceshipPrototypesAssignment;

    };

#endif
