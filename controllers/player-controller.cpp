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

    else if ( Event.type == sf::Event::KeyReleased ) {

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

    else if ( Event.type == sf::Event::JoystickButtonPressed ) {

        if ( Keys->getDevice() == PlayerControllerSettings::Devices::Joystick ) {

            if ( Keys->getJoystickIdentifier() == Event.joystickButton.joystickId ) {

                int Key = PlayerControllerSettings::normalizeJoystickKey( Event.joystickButton.button );

                if ( Key == Keys->getForwardKey() ) {

                    ThrustForward = true;
                    ThrustBackward = false;
                    ForceThrust = false; }

                else if ( Key == Keys->getBackwardKey() ) {

                    ThrustForward = false;
                    ThrustBackward = true;
                    ForceThrust = false; }

                else if ( Key == Keys->getLeftKey() ) {

                    ThrustLeft = true;
                    ThrustRight = false; }

                else if ( Key == Keys->getRightKey() ) {

                    ThrustLeft = false;
                    ThrustRight = true; }

                else if ( Key == Keys->getRayShotKey() ) {

                    ForceRayShot = true; }

                else if ( Key == Keys->getMissileShotKey() ) {

                    ForceMissileShot = true; } } } }

    else if ( Event.type == sf::Event::JoystickButtonReleased ) {

        if ( Keys->getDevice() == PlayerControllerSettings::Devices::Joystick ) {

            if ( Keys->getJoystickIdentifier() == Event.joystickButton.joystickId ) {

                int Key = PlayerControllerSettings::normalizeJoystickKey( Event.joystickButton.button );

                if ( Key == Keys->getForwardKey() ) {

                    ThrustForward = false; }

                else if ( Key == Keys->getBackwardKey() ) {

                    ThrustBackward = false; }

                else if ( Key == Keys->getLeftKey() ) {

                    ThrustLeft = false;

                    if ( ForceThrust ) {

                        ForceThrust = false;
                        ThrustForward = false; } }

                else if ( Key == Keys->getRightKey() ) {

                    ThrustRight = false;

                    if ( ForceThrust ) {

                        ForceThrust = false;
                        ThrustForward = false; } }

                else if ( Key == Keys->getRayShotKey() ) {

                    ForceRayShot = false; }

                else if ( Key == Keys->getMissileShotKey() ) {

                    ForceMissileShot = false; } } } }

    else if ( Event.type == sf::Event::JoystickMoved ) {

        if ( Keys->getDevice() == PlayerControllerSettings::Devices::Joystick ) {

            if ( Keys->getJoystickIdentifier() == Event.joystickMove.joystickId ) {

                int Key = PlayerControllerSettings::normalizeJoystickAxis( Event.joystickMove.axis, Event.joystickMove.position );
                bool State = true;

                if ( Key == -1 ) {

                    std::vector <int> PossibleKeys = PlayerControllerSettings::getKeysFromJoysickAxis( Event.joystickMove.axis );

                    for ( auto &PossibleKey : PossibleKeys ) {

                        if ( JoystickAxisState[ PossibleKey - 200 ] ) {

                            Key = PossibleKey;
                            State = false;

                            break; } } }

                if ( JoystickAxisState[ Key - 200 ] != State ) { // Joystick axis state changed

                    JoystickAxisState[ Key - 200 ] = !JoystickAxisState[ Key - 200 ];

                    if ( State ) { // Key pressed

                        if ( Key == Keys->getForwardKey() ) {

                            ThrustForward = true;
                            ThrustBackward = false;
                            ForceThrust = false; }

                        else if ( Key == Keys->getBackwardKey() ) {

                            ThrustForward = false;
                            ThrustBackward = true;
                            ForceThrust = false; }

                        else if ( Key == Keys->getLeftKey() ) {

                            ThrustLeft = true;
                            ThrustRight = false; }

                        else if ( Key == Keys->getRightKey() ) {

                            ThrustLeft = false;
                            ThrustRight = true; }

                        else if ( Key == Keys->getRayShotKey() ) {

                            ForceRayShot = true; }

                        else if ( Key == Keys->getMissileShotKey() ) {

                            ForceMissileShot = true; } }

                    else { // Key released

                        if ( Key == Keys->getForwardKey() ) {

                            ThrustForward = false; }

                        else if ( Key == Keys->getBackwardKey() ) {

                            ThrustBackward = false; }

                        else if ( Key == Keys->getLeftKey() ) {

                            ThrustLeft = false;

                            if ( ForceThrust ) {

                                ForceThrust = false;
                                ThrustForward = false; } }

                        else if ( Key == Keys->getRightKey() ) {

                            ThrustRight = false;

                            if ( ForceThrust ) {

                                ForceThrust = false;
                                ThrustForward = false; } }

                        else if ( Key == Keys->getRayShotKey() ) {

                            ForceRayShot = false; }

                        else if ( Key == Keys->getMissileShotKey() ) {

                            ForceMissileShot = false; } } } } } }

    if ( !ThrustForward && !ThrustBackward && ( ThrustLeft || ThrustRight ) ) {

        ForceThrust = true;
        ThrustForward = true; } }

void PlayerController::update ( sf::Time ElapsedTime ) {

    RayShotRestorationTime -= ElapsedTime;

    if ( ForceRayShot && RayShotRestorationTime.asSeconds() <= 0.f ) {

        RayShot = true;
        RayShotRestorationTime = RayShotRestorationDuration; }

    MissileShotRestorationTime -= ElapsedTime;

    if ( ForceMissileShot && MissileShotRestorationTime.asSeconds() <= 0.f ) {

        MissileShot = true;
        MissileShotRestorationTime = MissileShotRestorationDuration; } }
