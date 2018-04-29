#include "body.hpp"

Body::Body ( float Mass, float Radius ) {

    this->Mass = Mass;
    this->Radius = Radius;

    Destructed = false; }

float Body::getAngle ( sf::Vector2f Vector ) {

    if ( Vector.x == 0.f && Vector.y == 0.f ) {

        return 0.f; }

    return ( Vector.y >= 0.f ? 1.f : -1.f ) * acosf( Vector.x / sqrtf( Vector.x * Vector.x + Vector.y * Vector.y ) ); }

float Body::normalizeAngle ( float Angle ) {

    while ( Angle > M_PI ) {

        Angle -= 2.f * M_PI; }

    while ( Angle < - M_PI ) {

        Angle += 2.f * M_PI; }

    return Angle; }

float Body::getMass ( ) {

    return Mass; }

void Body::setMass ( float Mass ) {

    this->Mass = Mass; }

float Body::getRadius ( ) {

    return Radius; }

void Body::setRadius ( float Radius ) {

    this->Radius = Radius; }

sf::Vector2f Body::getPosition ( ) {

    return Position; }

void Body::setPosition ( sf::Vector2f Position ) {

    this->Position = Position; }

void Body::updatePosition ( sf::Time ElapsedTime ) {

    Position += Velocity * ElapsedTime.asSeconds(); }

sf::Vector2f Body::getVelocity ( ) {

    return Velocity; }

float Body::getVelocityAngle ( ) {

    return getAngle( Velocity ); }

void Body::setVelocity ( sf::Vector2f Velocity ) {

    this->Velocity = Velocity; }

void Body::updateVelocity ( sf::Vector2f Acceleration, sf::Time ElapsedTime ) {

    Velocity += Acceleration * ElapsedTime.asSeconds(); }

void Body::destruct ( ) {

    Destructed = true; }

bool Body::isDestructed ( ) {

    return Destructed; }
