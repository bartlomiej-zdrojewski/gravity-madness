#include "spaceship-controller.hpp"

void SpaceshipController::setSpaceship ( Spaceship * MySpaceship ) {

    this->MySpaceship = MySpaceship; }

bool SpaceshipController::onThrustForward ( ) {

    return ThrustForward; }

bool SpaceshipController::onThrustBackward ( ) {

    return ThrustBackward; }

bool SpaceshipController::onThrustLeft ( ) {

    return ThrustLeft; }

bool SpaceshipController::onThrustRight ( ) {

    return ThrustRight; }

bool SpaceshipController::onRayShot ( ) {

    if ( RayShot ) {

        RayShot = false;

        return true; }

    return false; }

bool SpaceshipController::onMissileShot ( ) {

    if ( MissileShot ) {

        MissileShot = false;

        return true; }

    return false; }