#include "power-up.hpp"

PowerUp::PowerUp ( float Radius, sf::Time Duration, float * Gravity, unsigned int * AsteroidCount ) {

    MySpaceship = nullptr;
    this->Gravity = Gravity;
    this->AsteroidCount = AsteroidCount;

    Caught = false;
    Expired = false;
    GravityModifier = false;
    AsteroidModifier = false;
    this->Radius = Radius;
    ExistenceTime = Duration;

    }

bool PowerUp::isCaught ( ) {

    return Caught; }

bool PowerUp::isExpired ( ) {

    return Expired; }

bool PowerUp::isGravityModifier ( ) {

    return GravityModifier; }

bool PowerUp::isAsteroidModifier ( ) {

    return AsteroidModifier; }

sf::Vector2f PowerUp::getPosition ( ) {

    return Position; }

void PowerUp::setPosition ( sf::Vector2f Position ) {

    this->Position = Position; }

float PowerUp::getRadius ( ) {

    return Radius; }

void PowerUp::setRadius ( float Radius ) {

    this->Radius = Radius; }

void PowerUp::update ( sf::Time ElapsedTime ) {

    if ( Caught ) {

        updateEffect( ElapsedTime ); }

    else {

        ExistenceTime -= ElapsedTime;

        if ( ExistenceTime.asSeconds() <= 0.f ) {

            Expired = true; } } }

void PowerUp::render ( sf::RenderWindow &Window ) { // TODO

    if ( !Caught ) {

        sf::CircleShape Circle;

        Circle.setRadius( Radius );
        Circle.setOrigin( getRadius(), getRadius() );
        Circle.setPosition( getPosition() );
        Circle.setFillColor( sf::Color( 0, 255, 0 ) );

        Window.draw( Circle );

        }

    }

void PowerUp::finish ( ) {

    Expired = true;

    onEffectEnd(); }

void PowerUp::onCatch ( Spaceship * MySpaceship ) {

    Caught = true;
    this->MySpaceship = MySpaceship;

    onEffectBegin(); }