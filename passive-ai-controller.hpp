#ifndef GRAVITY_MADNESS_PASSIVE_AI_CONTROLLER
#define GRAVITY_MADNESS_PASSIVE_AI_CONTROLLER

#include "ai-controller.hpp"

class PassiveAIController : public AIController {

public:

    PassiveAIController ( ) : AIController ( ) {

        MinimumVelocity = 25.f;
        MaximumVelocity = 100.f;
        MinimumRayShotEnergy = 250.f;

        RayShotRestorationDuration = sf::seconds( 1.f );
        MissileRestorationDuration = sf::seconds( 15.f );

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