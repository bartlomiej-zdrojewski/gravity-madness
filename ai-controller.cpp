#include "ai-controller.hpp"

void AIController::setClosestBodyDistance ( float Distance ) {

    ClosestBodyDistance = Distance; }

void AIController::setClosestBodyAcceleration ( sf::Vector2f Acceleration ) {

    ClosestBodyAcceleration = Acceleration; }

void AIController::setTargetIn120Degrees ( bool Target, float Distance ) {

    TargetIn120Degrees = Target;
    TargetDistance = Distance; }

void AIController::setTargetIn60Degrees ( bool Target, float Distance ) {

    TargetIn30Degrees = Target;
    TargetDistance = Distance; }

void AIController::setTargetIn30Degrees ( bool Target, float Distance ) {

    TargetIn30Degrees = Target;
    TargetDistance = Distance; }

void AIController::update ( sf::Time ElapsedTime ) {

    if ( !MySpaceship ) {

        return; }

    ThrustForward = false;
    ThrustBackward = false;
    ThrustLeft = false;
    ThrustRight = false;

    MySpaceship->updateEnergy( EnergyRestoration * ElapsedTime.asSeconds() );

    if ( MySpaceship->getEnergy() < MinimumThrustEnergy ) {

        return; }

    float Distance = ClosestBodyDistance;
    sf::Vector2f Acceleration = ClosestBodyAcceleration;

    float AccelerationAngle = MySpaceship->getAngle( Acceleration );
    float AccelerationModule = sqrtf( Acceleration.x * Acceleration.x + Acceleration.y * Acceleration.y );

    float VelocityAngle = MySpaceship->getVelocityAngle();
    float VelocityModule = sqrtf( MySpaceship->getVelocity().x * MySpaceship->getVelocity().x + MySpaceship->getVelocity().y * MySpaceship->getVelocity().y );

    float AngleDifference = MySpaceship->normalizeAngle( VelocityAngle - AccelerationAngle );

    if ( Distance < MinimumDistance ) {

        if ( AngleDifference >= 0.f ) {

            ThrustForward = true;
            ThrustRight = true; }

        else {

            ThrustForward = true;
            ThrustLeft = true; } }

    else if ( AccelerationModule > 30.f ) {

        if ( AngleDifference >= 0.f && AngleDifference < ( M_PI / 3.f ) ) {

            ThrustForward = true;
            ThrustRight = true; }

        else if ( AngleDifference < 0.f && AngleDifference > ( - M_PI / 3.f ) ) {

            ThrustForward = true;
            ThrustLeft = true; } }

    else if ( AccelerationModule > 10.f || VelocityModule < MinimumVelocity ) {

        if ( AngleDifference >= 0.f && AngleDifference < ( M_PI / 4.f ) ) {

            ThrustForward = true;
            ThrustRight = true; }

        else if ( AngleDifference < 0.f && AngleDifference > ( - M_PI / 4.f ) ) {

            ThrustForward = true;
            ThrustLeft = true; } }

    else if ( VelocityModule > MaximumVelocity ) {

        ThrustBackward = true; }

    else {

        onSafeOrbit( ElapsedTime );

        return; }

    onUnsafeOrbit( ElapsedTime ); }