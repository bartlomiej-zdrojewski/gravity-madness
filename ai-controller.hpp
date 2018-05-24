#ifndef GRAVITY_MADNESS_AI_CONTROLLER
#define GRAVITY_MADNESS_AI_CONTROLLER

#include "definitions.hpp"
#include "power-up.hpp"
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

        MyPowerUp = nullptr;
        PowerUpDistace = 1000000.f;
        PowerUpAngle = PI;

        ClosestBodyDistance = 1000000.f;
        ShotPanicTime = sf::seconds( 0.f );
        ShotPanicDuration = sf::seconds( 3.f );
        ShotPanicDirection = 0;
        LimitPanicTime = sf::seconds( 0.f );
        LimitPanicDuration = sf::seconds( 1.f ); }

    void setClosestBodyDistance ( float Distance );
    void setClosestBodyAcceleration ( sf::Vector2f Acceleration );
    void enableShotPanic ( );
    void enableLimitPanic ( );

    void setTargetIn120Degrees ( Spaceship * Target, float Distance = 1000000.f, float Angle = PI );
    void setTargetIn60Degrees ( Spaceship * Target, float Distance = 1000000.f, float Angle = PI );
    void setTargetIn30Degrees ( Spaceship * Target, float Distance = 1000000.f, float Angle = PI );
    void setPowerUp ( PowerUp * MyPowerUp, float Distance = 1000000.f, float Angle = PI );

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

    PowerUp * MyPowerUp;
    float PowerUpDistace;
    float PowerUpAngle;

    virtual void onSafeOrbit ( sf::Time ElapsedTime ) { };
    virtual void onUnsafeOrbit ( sf::Time ElapsedTime ) { };

private:

    float ClosestBodyDistance;
    sf::Vector2f ClosestBodyAcceleration;

    sf::Time ShotPanicTime;
    sf::Time ShotPanicDuration;
    int ShotPanicDirection;

    sf::Time LimitPanicTime;
    sf::Time LimitPanicDuration;

    };

#endif
