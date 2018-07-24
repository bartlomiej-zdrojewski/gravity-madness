#include <iostream>
#include "player-controller.hpp"

void PlayerController::update ( sf::Event &Event ) {

    if ( Event.type == sf::Event::KeyPressed ) {

        if ( Keys->getDevice() == PlayerControllerSettings::Devices::Keyboard ) {

            if ( Event.key.code == Keys->getForwardKey() ) {

                ThrustForward = true;
                ThrustBackward = false;
                ForceThrust = false; }

            else if ( Event.key.code == Keys->getBackwardKey() ) {

                ThrustForward = false;
                ThrustBackward = true;
                ForceThrust = false; }

            else if ( Event.key.code == Keys->getLeftKey() ) {

                ThrustLeft = true;
                ThrustRight = false; }

            else if ( Event.key.code == Keys->getRightKey() ) {

                ThrustLeft = false;
                ThrustRight = true; }

            else if ( Event.key.code == Keys->getRayShotKey() ) {

                ForceRayShot = true; }

            else if ( Event.key.code == Keys->getMissileShotKey() ) {

                ForceMissileShot = true; } } }

    if ( Event.type == sf::Event::KeyReleased ) {

        if ( Keys->getDevice() == PlayerControllerSettings::Devices::Keyboard ) {

            if ( Event.key.code == Keys->getForwardKey() ) {

                ThrustForward = false; }

            else if ( Event.key.code == Keys->getBackwardKey() ) {

                ThrustBackward = false; }

            else if ( Event.key.code == Keys->getLeftKey() ) {

                ThrustLeft = false;

                if ( ForceThrust ) {

                    ForceThrust = false;
                    ThrustForward = false; } }

            else if ( Event.key.code == Keys->getRightKey() ) {

                ThrustRight = false;

                if ( ForceThrust ) {

                    ForceThrust = false;
                    ThrustForward = false; } }

            else if ( Event.key.code == Keys->getRayShotKey() ) {

                ForceRayShot = false; }

            else if ( Event.key.code == Keys->getMissileShotKey() ) {

                ForceMissileShot = false; } } }

    // TODO Joystick

    if ( !ThrustForward && !ThrustBackward && ( ThrustLeft || ThrustRight ) ) {

        ForceThrust = true;
        ThrustForward = true; }

    }

void PlayerController::update ( sf::Time ElapsedTime ) {

    RayShotRestorationTime -= ElapsedTime;

    if ( ForceRayShot && RayShotRestorationTime.asSeconds() <= 0.f ) {

        RayShot = true;
        RayShotRestorationTime = RayShotRestorationDuration; }

    MissileShotRestorationTime -= ElapsedTime;

    if ( ForceMissileShot && MissileShotRestorationTime.asSeconds() <= 0.f ) {

        MissileShot = true;
        MissileShotRestorationTime = MissileShotRestorationDuration; } }
