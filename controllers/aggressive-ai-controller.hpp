#ifndef GRAVITY_MADNESS_AGGRESSIVE_AI_CONTROLLER
#define GRAVITY_MADNESS_AGGRESSIVE_AI_CONTROLLER

#include "ai-controller.hpp"

class AggressiveAIController : public AIController {

public:

    AggressiveAIController ( ) : AIController ( ) {

        MaximumVelocity = 200.f;

        RayShotRestorationDuration = sf::seconds( 0.25f );
        MissileRestorationDuration = sf::seconds( 5.f );

        };

private:

    void onSafeOrbit ( sf::Time ElapsedTime );
    void onUnsafeOrbit ( sf::Time ElapsedTime );

private:

    sf::Time RayShotRestorationTime;
    sf::Time RayShotRestorationDuration;

    sf::Time MissileRestorationTime;
    sf::Time MissileRestorationDuration;

    };

#endif