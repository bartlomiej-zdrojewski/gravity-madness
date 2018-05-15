#include "ai-controller.hpp"

void AIController::setClosestBodyDistance ( float Distance ) {

    ClosestBodyDistance = Distance; }

void AIController::setClosestBodyAcceleration ( sf::Vector2f Acceleration ) {

    ClosestBodyAcceleration = Acceleration; }

void AIController::enableShotPanic ( ) {

    ShotPanicTime = ShotPanicDuration;
    ShotPanicDirection = rand() % 3; }

void AIController::enableLimitPanic ( ) {

    LimitPanicTime = LimitPanicDuration; }

void AIController::setTargetIn120Degrees ( Spaceship * Target, float Distance, float Angle ) {

    TargetIn120Degrees = Target;

    if ( Target ) {

        TargetDistance = Distance;
        TargetAngle = Angle; }

    else {

        setTargetIn60Degrees( nullptr ); } }

void AIController::setTargetIn60Degrees ( Spaceship * Target, float Distance, float Angle ) {

    TargetIn60Degrees = Target;

    if ( Target ) {

        TargetDistance = Distance;
        TargetAngle = Angle; }

    else {

        setTargetIn30Degrees( nullptr ); } }

void AIController::setTargetIn30Degrees ( Spaceship * Target, float Distance, float Angle ) {

    TargetIn30Degrees = Target;

    if ( Target ) {

        TargetDistance = Distance;
        TargetAngle = Angle; } }

void AIController::setPowerUp ( PowerUp * MyPowerUp, float Distance, float Angle ) {

    this->MyPowerUp = MyPowerUp;

    if ( MyPowerUp ) {

        PowerUpDistace = Distance;
        PowerUpAngle = Angle; } }

void AIController::update ( sf::Time ElapsedTime ) {

    if ( !MySpaceship ) {

        return; }

    ThrustForward = false;
    ThrustBackward = false;
    ThrustLeft = false;
    ThrustRight = false;

    ShotPanicTime -= ElapsedTime;
    LimitPanicTime -= ElapsedTime;

    float Distance = ClosestBodyDistance;
    sf::Vector2f Acceleration = ClosestBodyAcceleration;

    float AccelerationAngle = MySpaceship->getAngle( Acceleration );
    float AccelerationModule = sqrtf( Acceleration.x * Acceleration.x + Acceleration.y * Acceleration.y );
    float VelocityAngle = MySpaceship->getVelocityAngle();
    float VelocityModule = sqrtf( MySpaceship->getVelocity().x * MySpaceship->getVelocity().x + MySpaceship->getVelocity().y * MySpaceship->getVelocity().y );
    float AngleDifference = MySpaceship->normalizeAngle( VelocityAngle - AccelerationAngle );

    if ( Distance < MinimumDistance ) {

        ThrustForward = true;

        if ( AngleDifference >= 0.f ) {

            ThrustRight = true; }

        else {

            ThrustLeft = true; } }

    else if ( Distance < ( 2.5f * MinimumDistance ) && fabsf( AngleDifference ) < ( PI / 8.f ) ) {

        ThrustForward = true;

        if ( AngleDifference >= 0.f ) {

            ThrustRight = true; }

        else {

            ThrustLeft = true; } }

    else if ( AccelerationModule > ( 0.2f * MySpaceship->getThrust() ) ) {

        if ( AngleDifference >= 0.f && AngleDifference < ( PI / 3.f ) ) {

            ThrustForward = true;
            ThrustRight = true; }

        else if ( AngleDifference < 0.f && AngleDifference > ( - PI / 3.f ) ) {

            ThrustForward = true;
            ThrustLeft = true; } }

    else if ( LimitPanicTime.asSeconds() > 0.f ) {

        if ( VelocityModule > MaximumVelocity ) {

            ThrustBackward = true; }

        else {

            float SafeAngle = atan2f( MySpaceship->getPosition().y, MySpaceship->getPosition().x );
            SafeAngle = MySpaceship->normalizeAngle( SafeAngle - MySpaceship->getVelocityAngle() );

            ThrustForward = true;

            if ( SafeAngle < 0.f ) {

                ThrustRight = true; }

            else if ( SafeAngle > 0.f ) {

                ThrustLeft = true; } }

        onUnsafeOrbit( ElapsedTime ); }

    else if ( MySpaceship->getEnergy() >= MinimumThrustEnergy ) {

        if ( AccelerationModule > ( 0.1f * MySpaceship->getThrust() ) ) {

            if ( AngleDifference >= 0.f && AngleDifference < ( PI / 4.f ) ) {

                ThrustForward = true;
                ThrustRight = true;

                onUnsafeOrbit( ElapsedTime ); }

            else if ( AngleDifference < 0.f && AngleDifference > ( - PI / 4.f ) ) {

                ThrustForward = true;
                ThrustLeft = true;

                onUnsafeOrbit( ElapsedTime ); }

            else {

                onSafeOrbit( ElapsedTime ); } }

        else if ( ShotPanicTime.asSeconds() > 0.f ) {

            ThrustForward = true;

            if ( ShotPanicDirection == 0 ) {

                ThrustRight = true; }

            else if ( ShotPanicDirection == 1 ) {

                ThrustLeft = true; }

            onUnsafeOrbit( ElapsedTime ); }

        else if ( VelocityModule < MinimumVelocity ) {

            ThrustForward = true;

            onUnsafeOrbit( ElapsedTime ); }

        else if ( VelocityModule > MaximumVelocity ) {

            ThrustBackward = true;

            onUnsafeOrbit( ElapsedTime ); }

        else {

            onSafeOrbit( ElapsedTime ); } }

    else {

        onUnsafeOrbit( ElapsedTime ); } }
