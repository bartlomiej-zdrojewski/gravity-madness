#include "player-controller.hpp"

void PlayerController::update ( sf::Event &Event ) {

    if ( Event.type == sf::Event::KeyPressed ) {

        switch ( Event.key.code ) {

            case sf::Keyboard::W: {

                ThrustForward = true;
                ThrustBackward = false;

                break; }

            case sf::Keyboard::S: {

                ThrustForward = false;
                ThrustBackward = true;

                break; }

            case sf::Keyboard::A: {

                ThrustLeft = true;
                ThrustRight = false;

                break; }

            case sf::Keyboard::D: {

                ThrustLeft = false;
                ThrustRight = true;

                break; }

            case sf::Keyboard::Space: {

                ForceRayShot = true;

                break; }

                // ...

            default: {

                break; } } }

    else if ( Event.type == sf::Event::KeyReleased ) {

        switch ( Event.key.code ) {

            case sf::Keyboard::W: {

                ThrustForward = false;

                break; }

            case sf::Keyboard::S: {

                ThrustBackward = false;

                break; }

            case sf::Keyboard::A: {

                ThrustLeft = false;

                break; }

            case sf::Keyboard::D: {

                ThrustRight = false;

                break; }

            case sf::Keyboard::Space: {

                ForceRayShot = false;

                break; }

                // ...

            default: {

                break; } } }

    // ...

    }

void PlayerController::update ( sf::Time ElapsedTime ) {

    RayShotRestorationTime -= ElapsedTime;

    if ( ForceRayShot && RayShotRestorationTime.asSeconds() <= 0.f ) {

        RayShot = true;
        RayShotRestorationTime = RayShotRestorationDuration; }

    }