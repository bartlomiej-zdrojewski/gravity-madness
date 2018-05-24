#ifndef GRAVITY_MADNESS_REASONABLE_AI_CONTROLLER
#define GRAVITY_MADNESS_REASONABLE_AI_CONTROLLER

#include "ai-controller.hpp"

class ReasonableAIController : public AIController {

public:

    ReasonableAIController ( ) : AIController ( ) {

        MinimumRayShotEnergy = 200.f;

        RayShotRestorationDuration = sf::seconds( 0.5f );
        MissileRestorationDuration = sf::seconds( 10.f );

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
