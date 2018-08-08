#include "passive-ai-controller.hpp"

void PassiveAIController::onSafeOrbit ( sf::Time ElapsedTime ) {

    RayShotRestorationTime -= ElapsedTime;
    MissileRestorationTime -= ElapsedTime;

    if ( TargetIn30Degrees ) {

        if ( TargetDistance > 150.f ) {

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

        if ( TargetDistance < 200.f ) {

            if ( MissileRestorationTime.asSeconds() <= 0.f ) {

                MissileShot = true;
                MissileRestorationTime = MissileRestorationDuration; } } }

    else if ( MySpaceship->getEnergy() >= MinimumRayShotEnergy && ( TargetIn60Degrees || TargetIn120Degrees ) ) {

        if ( TargetDistance < 300.f ) {

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

void PassiveAIController::onUnsafeOrbit ( sf::Time ElapsedTime ) {

    RayShotRestorationTime -= ElapsedTime;
    MissileRestorationTime -= ElapsedTime;

    if ( TargetIn30Degrees ) {

        if ( TargetDistance < 200.f ) {

            if ( MySpaceship->getEnergy() >= MinimumRayShotEnergy && RayShotRestorationTime.asSeconds() <= 0.f ) {

                RayShot = true;
                RayShotRestorationTime = RayShotRestorationDuration; } } } }
