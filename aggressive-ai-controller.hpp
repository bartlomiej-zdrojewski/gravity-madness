#ifndef GRAVITY_MADNESS_AGGRESSIVE_AI_CONTROLLER
#define GRAVITY_MADNESS_AGGRESSIVE_AI_CONTROLLER

#include "ai-controller.hpp"

class AggressiveAIController : public AIController {

public:

    AggressiveAIController ( ) : AIController ( ) {

        RayShotRestorationDuration = sf::seconds( 0.2f );
        MissileRestorationDuration = sf::seconds( 3.f );

        };

private:

    void onSafeOrbit ( sf::Time ElapsedTime );
    void onUnsafeOrbit ( sf::Time ElapsedTime );

    sf::Time RayShotRestorationTime;
    sf::Time RayShotRestorationDuration;

    sf::Time MissileRestorationTime;
    sf::Time MissileRestorationDuration;

    };

#endif