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