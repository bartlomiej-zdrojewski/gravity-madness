#ifndef GRAVITY_MADNESS_PLAYER_CONTROLLER
#define GRAVITY_MADNESS_PLAYER_CONTROLLER

#include "spaceship-controller.hpp"

class PlayerController : public SpaceshipController {

public:

    PlayerController ( ) : SpaceshipController ( ) {

        RayShotRestorationTime = sf::seconds( 0.f );
        RayShotRestorationDuration = sf::seconds( 0.05f );
        ForceRayShot = false;

        }

    void update ( sf::Event &Event );
    void update ( sf::Time ElapsedTime );

private:

    bool ForceRayShot;
    sf::Time RayShotRestorationTime;
    sf::Time RayShotRestorationDuration;

    };

#endif
