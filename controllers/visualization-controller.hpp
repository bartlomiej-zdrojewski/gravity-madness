#ifndef GRAVITY_MADNESS_VISUALIZATION_CONTROLLER
#define GRAVITY_MADNESS_VISUALIZATION_CONTROLLER

#include "../constants.hpp"
#include "spaceship-controller.hpp"

class VisualizationController : public SpaceshipController {

public:

    VisualizationController ( ) : SpaceshipController ( ) {

        ResetDistance = 100.f;

        ReactionDuration = sf::seconds( 0.1f );
        ReactionTime = ReactionDuration;
        RayShotRestorationDuration = sf::seconds( 10.f );
        RayShotRestorationTime = ( 0.5f + 0.5f * getRandomFloat() ) * RayShotRestorationDuration;
        MissileShotRestorationDuration = sf::seconds( 20.f );
        MissileShotRestorationTime = ( 0.5f + 0.5f * getRandomFloat() ) * MissileShotRestorationDuration; }

    sf::Vector2f getDesiredPosition ( );
    void setDesiredPosition ( sf::Vector2f DesiredPosition );

    float getResetDistance ( );
    void setResetDistance ( float ResetDistance );

    void update ( sf::Time ElapsedTime );

private:

    float getRandomFloat ( );
    float getDistance ( sf::Vector2f A, sf::Vector2f B );

private:

    sf::Vector2f DesiredPosition;
    float ResetDistance;

    sf::Time RayShotRestorationTime;
    sf::Time RayShotRestorationDuration;
    sf::Time MissileShotRestorationTime;
    sf::Time MissileShotRestorationDuration;

    sf::Time ReactionTime;
    sf::Time ReactionDuration;

    };

#endif
