#include <iostream>
#include "ai-controller.hpp"

void AIController::setClosestBodyDistance ( float Distance ) {

    ClosestBodyDistance = Distance; }

void AIController::setClosestBodyAcceleration ( sf::Vector2f Acceleration ) {

    ClosestBodyAcceleration = Acceleration; }

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

void AIController::update ( sf::Time ElapsedTime ) {

    if ( !MySpaceship ) {

        return; }

    ThrustForward = false;
    ThrustBackward = false;
    ThrustLeft = false;
    ThrustRight = false;

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

    else if ( AccelerationModule > ( 0.3f * MySpaceship->getThrust() ) ) {

        if ( AngleDifference >= 0.f && AngleDifference < ( PI / 3.f ) ) {

            ThrustForward = true;
            ThrustRight = true; }

        else if ( AngleDifference < 0.f && AngleDifference > ( - PI / 3.f ) ) {

            ThrustForward = true;
            ThrustLeft = true; } }

    else if ( MySpaceship->getEnergy() >= MinimumThrustEnergy ) {

        if ( AccelerationModule > ( 0.1f * MySpaceship->getThrust() ) || VelocityModule < MinimumVelocity ) {

            if ( AngleDifference >= 0.f && AngleDifference < ( PI / 4.f ) ) {

                ThrustForward = true;
                ThrustRight = true; }

            else if ( AngleDifference < 0.f && AngleDifference > ( - PI / 4.f ) ) {

                ThrustForward = true;
                ThrustLeft = true; } }

        else if ( VelocityModule > MaximumVelocity ) {

            ThrustBackward = true; }

        else {

            onSafeOrbit( ElapsedTime );

            return; }

        onUnsafeOrbit( ElapsedTime ); } }