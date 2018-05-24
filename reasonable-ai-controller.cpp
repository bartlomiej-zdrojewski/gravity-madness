#include "reasonable-ai-controller.hpp"

void ReasonableAIController::onSafeOrbit ( sf::Time ElapsedTime ) {

    RayShotRestorationTime -= ElapsedTime;
    MissileRestorationTime -= ElapsedTime;

    if ( TargetIn30Degrees ) {

        if ( TargetDistance > 100.f ) {

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

    else if ( MySpaceship->getEnergy() >= MinimumRayShotEnergy && ( TargetIn60Degrees || TargetIn120Degrees ) ) {

        if ( TargetDistance < 500.f ) {

            ThrustForward = true;

            if ( TargetAngle < 0.f ) {

                ThrustRight = true; }

            else if ( TargetAngle > 0.f ) {

                ThrustLeft = true; } } }

    else if ( MyPowerUp ) {

        if ( PowerUpDistace < 200.f || ( ( PowerUpDistace < 500.f ) && ( fabsf( PowerUpAngle ) > ( PI / 12.f ) ) ) ) {

            ThrustForward = true;

            if ( PowerUpAngle < 0.f ) {

                ThrustRight = true; }

            else if ( PowerUpAngle > 0.f ) {

                ThrustLeft = true; } } } }

void ReasonableAIController::onUnsafeOrbit ( sf::Time ElapsedTime ) {

    RayShotRestorationTime -= ElapsedTime;
    MissileRestorationTime -= ElapsedTime;

    if ( TargetIn30Degrees ) {

        if ( MySpaceship->getEnergy() >= MinimumRayShotEnergy && RayShotRestorationTime.asSeconds() <= 0.f ) {

            RayShot = true;
            RayShotRestorationTime = RayShotRestorationDuration; } }

    else if ( TargetIn60Degrees ) {

        if ( TargetDistance < 250.f ) {

            if ( MissileRestorationTime.asSeconds() <= 0.f ) {

                MissileShot = true;
                MissileRestorationTime = MissileRestorationDuration; } } } }
