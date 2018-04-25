#ifndef GRAVITY_MADNESS_SPACESHIP_CONTROLLER
#define GRAVITY_MADNESS_SPACESHIP_CONTROLLER

#include <queue>
#include <SFML/Graphics.hpp>

class SpaceshipController {

public:

    SpaceshipController ( ) {

        ThrustForward = false;
        ThrustBackward = false;
        ThrustLeft = false;
        ThrustRight = false;
        // ...

        }

    virtual void update ( sf::Event &Event ) { }
    virtual void update ( sf::Time ElapsedTime ) { }

    bool onThrustForward ( );
    bool onThrustBackward ( );
    bool onThrustLeft ( );
    bool onThrustRight ( );
    // ...

protected:

    bool ThrustForward;
    bool ThrustBackward;
    bool ThrustLeft;
    bool ThrustRight;
    // ...

    };

#endif
