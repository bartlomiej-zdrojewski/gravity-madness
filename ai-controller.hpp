#ifndef GRAVITY_MADNESS_AI_CONTROLLER
#define GRAVITY_MADNESS_AI_CONTROLLER

#include "definitions.hpp"
#include "spaceship-controller.hpp"

class AIController : public SpaceshipController {

public:

    AIController ( ) : SpaceshipController ( ) {

        MinimumVelocity = 50.f;
        MaximumVelocity = 150.f;
        MinimumDistance = 100.f;
        MinimumThrustEnergy = 50.f;
        MinimumRayShotEnergy = 100.f;

        TargetIn120Degrees = nullptr;
        TargetIn60Degrees = nullptr;
        TargetIn30Degrees = nullptr;
        TargetDistance = 1000000.f;
        TargetAngle = PI;

        ClosestBodyDistance = 1000000.f;
        ShotPanicTime = sf::seconds( 0.f );
        ShotPanicDuration = sf::seconds( 3.f );
        ShotPanicDirection = 0; }

    void setClosestBodyDistance ( float Distance );
    void setClosestBodyAcceleration ( sf::Vector2f Acceleration );
    void enableShotPanic ( );

    void setTargetIn120Degrees ( Spaceship * Target, float Distance = 1000000.f, float Angle = 0.f );
    void setTargetIn60Degrees ( Spaceship * Target, float Distance = 1000000.f, float Angle = 0.f );
    void setTargetIn30Degrees ( Spaceship * Target, float Distance = 1000000.f, float Angle = 0.f );

    void update ( sf::Time ElapsedTime );

protected:

    float MinimumVelocity;
    float MaximumVelocity;
    float MinimumDistance;
    float MinimumThrustEnergy;
    float MinimumRayShotEnergy;

    Spaceship * TargetIn120Degrees;
    Spaceship * TargetIn60Degrees;
    Spaceship * TargetIn30Degrees;
    float TargetDistance;
    float TargetAngle;

    virtual void onSafeOrbit ( sf::Time ElapsedTime ) { };
    virtual void onUnsafeOrbit ( sf::Time ElapsedTime ) { };

private:

    float ClosestBodyDistance;
    sf::Vector2f ClosestBodyAcceleration;

    sf::Time ShotPanicTime;
    sf::Time ShotPanicDuration;
    int ShotPanicDirection;

    };

#endif
