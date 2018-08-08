#include "aggressive-ai-controller.hpp"

void AggressiveAIController::onSafeOrbit ( sf::Time ElapsedTime ) {

    RayShotRestorationTime -= ElapsedTime;
    MissileRestorationTime -= ElapsedTime;

    if ( TargetIn30Degrees ) {

        if ( TargetDistance > 50.f ) {

            ThrustForward = true;

            if ( TargetAngle < 0.f ) {

                ThrustRight = true; }

            else if ( TargetAngle > 0.f ) {

                ThrustLeft = true; } }

        else {

            ThrustBackward = true; }

        if ( MySpaceship->getEnergy() >= MinimumRayShotEnergy && RayShotRestorationTime.asSeconds() <= 0.f ) {

            RayShot = true;
            RayShotRestorationTime = RayShotRestorationDuration; }

        if ( TargetDistance < 250.f ) {

            if ( MissileRestorationTime.asSeconds() <= 0.f ) {

                MissileShot = true;
                MissileRestorationTime = MissileRestorationDuration; } } }

    else if ( TargetIn60Degrees || TargetIn120Degrees ) {

        if ( TargetDistance < 500.f ) {

            ThrustForward = true;

            if ( TargetAngle < 0.f ) {

                ThrustRight = true; }

            else if ( TargetAngle > 0.f ) {

                ThrustLeft = true; } } }

    else if ( MyPowerUp ) {

        if ( ( ( PowerUpDistance < 50.f ) && ( fabsf( PowerUpAngle ) > ( PI / 24.f ) ) ) ||
             ( ( PowerUpDistance < 250.f ) && ( fabsf( PowerUpAngle ) > ( PI / 12.f ) ) ) ||
             ( ( PowerUpDistance < 500.f ) && ( fabsf( PowerUpAngle ) > ( PI / 4.f ) ) ) ) {

            ThrustForward = true;

            if ( PowerUpAngle < 0.f ) {

                ThrustRight = true; }

            else if ( PowerUpAngle > 0.f ) {

                ThrustLeft = true; } } } }

void AggressiveAIController::onUnsafeOrbit ( sf::Time ElapsedTime ) {

    RayShotRestorationTime -= ElapsedTime;
    MissileRestorationTime -= ElapsedTime;

    if ( TargetIn30Degrees ) {

        if ( MySpaceship->getEnergy() >= MinimumRayShotEnergy && RayShotRestorationTime.asSeconds() <= 0.f ) {

            RayShot = true;
            RayShotRestorationTime = RayShotRestorationDuration; } }

    else if ( TargetIn60Degrees ) {

        if ( TargetDistance < 500.f ) {

            if ( MissileRestorationTime.asSeconds() <= 0.f ) {

                MissileShot = true;
                MissileRestorationTime = MissileRestorationDuration; } } } }
