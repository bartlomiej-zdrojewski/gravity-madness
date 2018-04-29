#ifndef GRAVITY_MADNESS_AI_CONTROLLER
#define GRAVITY_MADNESS_AI_CONTROLLER

#include "spaceship-controller.hpp"

class AIController : public SpaceshipController {

public:

    AIController ( ) : SpaceshipController ( ) {

        MinimumVelocity = 25.f;
        MaximumVelocity = 50.f;
        MinimumDistance = 50.f;

        TargetIn120Degrees = false;
        TargetIn60Degrees = false;
        TargetIn30Degrees = false;
        TargetDistance = 1000000.f;

        ClosestBodyDistance = 1000000.f; }

    void setClosestBodyDistance ( float Distance );
    void setClosestBodyAcceleration ( sf::Vector2f Acceleration );

    void setTargetIn120Degrees ( bool Target, float Distance = 1000000.f );
    void setTargetIn60Degrees ( bool Target, float Distance = 1000000.f );
    void setTargetIn30Degrees ( bool Target, float Distance = 1000000.f );

    virtual void update ( sf::Time ElapsedTime );

protected:

    float MinimumVelocity;
    float MaximumVelocity;
    float MinimumDistance;

    bool TargetIn120Degrees;
    bool TargetIn60Degrees;
    bool TargetIn30Degrees;
    float TargetDistance;

    virtual void onSafeOrbit ( sf::Time ElapsedTime ) { };
    virtual void onUnsafeOrbit ( sf::Time ElapsedTime ) { };

private:

    float ClosestBodyDistance;
    sf::Vector2f ClosestBodyAcceleration;

    };

#endif
