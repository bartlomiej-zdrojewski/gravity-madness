#ifndef GRAVITY_MADNESS_SPACESHIP_CONTROLLER
#define GRAVITY_MADNESS_SPACESHIP_CONTROLLER

#include <queue>
#include <SFML/Graphics.hpp>

#include "Spaceship.hpp"

class Spaceship;

class SpaceshipController {

public:

    SpaceshipController ( ) {

        MySpaceship = nullptr;

        EnergyRestoration = 5.f;
        MinimumThrustEnergy = 10.f;
        // ...

        ThrustForward = false;
        ThrustBackward = false;
        ThrustLeft = false;
        ThrustRight = false;
        // ...

        }

    void setSpaceship ( Spaceship * MySpaceship );

    virtual void update ( sf::Event &Event ) { }
    virtual void update ( sf::Time ElapsedTime ) { }

    bool onThrustForward ( );
    bool onThrustBackward ( );
    bool onThrustLeft ( );
    bool onThrustRight ( );
    bool onRayShot ( );
    bool onMissileShot ( );

protected:

    Spaceship * MySpaceship;

    float EnergyRestoration;
    float MinimumThrustEnergy;
    // ...

    bool ThrustForward;
    bool ThrustBackward;
    bool ThrustLeft;
    bool ThrustRight;
    bool RayShot;
    bool MissileShot;

    };

#endif
