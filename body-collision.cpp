#include "body-collision.hpp"

BodyCollision::BodyCollision ( BodyCollision::Types Type, Body * First, Body * Second, float Efficiency ) {

    if ( Type == Elastic ) {

        float MassSum = First->getMass() + Second->getMass();

        FirstVelocity = ( First->getVelocity() * ( First->getMass() - Second->getMass() ) + 2.f * Second->getMass() * Second->getVelocity() ) / MassSum;
        SecondVelocity = ( Second->getVelocity() * ( Second->getMass() - First->getMass() ) + 2.f * First->getMass() * First->getVelocity() ) / MassSum;

        FirstVelocity *= Efficiency;
        SecondVelocity *= Efficiency;

        float FirstBeginEnergy = 0.5f * First->getMass() * powf( getLength( First->getVelocity() ), 2.f );
        float SecondBeginEnergy = 0.5f * Second->getMass() * powf( getLength( Second->getVelocity() ), 2.f );
        float BeginEnergy = FirstBeginEnergy + SecondBeginEnergy;

        float FirstEndEnergy = 0.5f * First->getMass() * powf( getLength( FirstVelocity ), 2.f );
        float SecondEndEnergy = 0.5f * Second->getMass() * powf( getLength( SecondVelocity ), 2.f );
        float EndEnergy = FirstEndEnergy + SecondEndEnergy;

        ReleasedEnergy = ( BeginEnergy - EndEnergy ) / 1000.f; }

    if ( Type == Inelastic ) {

        sf::Vector2f FirstMomentum = First->getMass() * First->getVelocity();
        sf::Vector2f SecondMomentum = Second->getMass() * Second->getVelocity();
        sf::Vector2f Velocity = ( FirstMomentum + SecondMomentum ) / ( First->getMass() + Second->getMass() );

        float FirstEnergy = 0.5f * First->getMass() * powf( getLength( First->getVelocity() ), 2.f );
        float SecondEnergy = 0.5f * First->getMass() * powf( getLength( First->getVelocity() ), 2.f );
        float FinalEnergy = 0.5f * First->getMass() * powf( getLength( Velocity ), 2.f );

        FirstVelocity = Velocity;
        SecondVelocity = Velocity;
        ReleasedEnergy = ( FirstEnergy + SecondEnergy - FinalEnergy ) / 1000.f; } }

sf::Vector2f BodyCollision::getFirstVelocity ( ) {

    return FirstVelocity; }

sf::Vector2f BodyCollision::getSecondVelocity ( ) {

    return SecondVelocity; }

float BodyCollision::getReleasedEnergy ( ) {

    return ReleasedEnergy; }

float BodyCollision::getLength ( sf::Vector2f Vector ) {

    return sqrtf( Vector.x * Vector.x + Vector.y * Vector.y ); }