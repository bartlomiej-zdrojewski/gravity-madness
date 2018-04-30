#ifndef GRAVITY_MADNESS_PLAYER_CONTROLLER
#define GRAVITY_MADNESS_PLAYER_CONTROLLER

#include "spaceship-controller.hpp"

class PlayerController : public SpaceshipController {

public:

    PlayerController ( ) : SpaceshipController ( ) {

        KeepRayShot = false;

        }

    void update ( sf::Event &Event );
    void update ( sf::Time ElapsedTime );

private:

    bool KeepRayShot;

    };

#endif
