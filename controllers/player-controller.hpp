#ifndef GRAVITY_MADNESS_PLAYER_CONTROLLER
#define GRAVITY_MADNESS_PLAYER_CONTROLLER

#include "spaceship-controller.hpp"
#include "player-controller-settings.hpp"

class PlayerController : public SpaceshipController {

public:

    explicit PlayerController ( PlayerControllerSettings * Keys ) : SpaceshipController ( ) {

        this->Keys = Keys;

        ForceThrust = false;
        ForceRayShot = false;
        ForceMissileShot = false;

        RayShotRestorationTime = sf::seconds( 0.f );
        RayShotRestorationDuration = sf::seconds( 0.05f );
        MissileShotRestorationTime = sf::seconds( 0.f );
        MissileShotRestorationDuration = sf::seconds( 0.75f ); }

    void update ( sf::Event &Event );
    void update ( sf::Time ElapsedTime );

private:

    PlayerControllerSettings * Keys;

    bool ForceThrust;
    bool ForceRayShot;
    bool ForceMissileShot;

    sf::Time RayShotRestorationTime;
    sf::Time RayShotRestorationDuration;
    sf::Time MissileShotRestorationTime;
    sf::Time MissileShotRestorationDuration;

    };

#endif
