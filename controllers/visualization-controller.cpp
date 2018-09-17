#include <iostream>
#include "visualization-controller.hpp"

sf::Vector2f VisualizationController::getDesiredPosition ( ) {

    return DesiredPosition; }

void VisualizationController::setDesiredPosition ( sf::Vector2f DesiredPosition ) {

    this->DesiredPosition = DesiredPosition; }

float VisualizationController::getResetDistance ( ) {

    return ResetDistance; }

void VisualizationController::setResetDistance ( float ResetDistance ) {

    this->ResetDistance = ResetDistance; }

void VisualizationController::update ( sf::Time ElapsedTime ) {

    if ( !MySpaceship ) {

        return; }

    if ( getDistance( DesiredPosition, MySpaceship->getPosition() ) > ResetDistance ) {

        MySpaceship->setVelocity( sf::Vector2f( 25.f, 0.f ) );
        MySpaceship->setPosition( DesiredPosition ); }

    ReactionTime -= ElapsedTime;
    RayShotRestorationTime -= ElapsedTime;
    MissileShotRestorationTime -= ElapsedTime;

    if ( ReactionTime.asSeconds() > 0.f ) {

        return; }

    else {

        ReactionTime = ReactionDuration; }

    ThrustForward = false;
    ThrustBackward = false;
    ThrustLeft = false;
    ThrustRight = false;

    float AngleDifference = atan2f( DesiredPosition.y - MySpaceship->getPosition().y, DesiredPosition.x - MySpaceship->getPosition().x );
    AngleDifference = MySpaceship->normalizeAngle( MySpaceship->getVelocityAngle() - AngleDifference );

    if ( fabsf( DesiredPosition.x - MySpaceship->getPosition().x ) > ( MySpaceship->getRadius() / 2.f ) ) {

        if ( fabsf( AngleDifference ) < ( PI / 2.f ) ) {

            ThrustForward = true; }

        else {

            ThrustBackward = true; } }

    if ( ThrustForward && fabsf( DesiredPosition.y - MySpaceship->getPosition().y ) > ( MySpaceship->getRadius() / 6.f ) ) {

        if ( AngleDifference > 0.f ) {

            ThrustLeft = true; }

        else {

            ThrustRight = true; } }

    if ( RayShotRestorationTime.asSeconds() <= 0.f ) {

        RayShot = true;
        RayShotRestorationTime = ( 0.5f + 0.5f * getRandomFloat() ) * RayShotRestorationDuration; }

    if ( MissileShotRestorationTime.asSeconds() <= 0.f ) {

        MissileShot = true;
        MissileShotRestorationTime = ( 0.5f + 0.5f * getRandomFloat() ) * MissileShotRestorationDuration; } }

float VisualizationController::getRandomFloat ( ) {

    return ( static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ); }

float VisualizationController::getDistance ( sf::Vector2f A, sf::Vector2f B ) {

    const float DistanceX = ( A.x - B.x );
    const float DistanceY = ( A.y - B.y );

    return sqrtf( DistanceX * DistanceX + DistanceY * DistanceY ); }
