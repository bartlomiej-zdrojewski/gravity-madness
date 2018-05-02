#include "asteroid.hpp"

void Asteroid::resetExistenceTime ( ) {

    ExistenceTime = ExistenceDuration; }

void Asteroid::update ( sf::Time ElapsedTime ) {

    ExistenceTime -= ElapsedTime;

    if ( ExistenceTime.asSeconds() <= 0.f ) {

        DestructionTime -= ElapsedTime;

        if ( DestructionTime.asSeconds() <= 0.f ) {

            destruct(); } }

    else if ( DestructionTime < DestructionDuration ) {

        DestructionTime += 2.f * ElapsedTime; }

    if ( DestructionTime > DestructionDuration ) {

        DestructionTime = DestructionDuration; }

    updatePosition( ElapsedTime ); }

void Asteroid::render ( sf::RenderWindow &Window ) { // TODO

    sf::CircleShape Circle;

    Circle.setRadius( getRadius() );
    Circle.setOrigin( getRadius(), getRadius() );
    Circle.setPosition( getPosition() );
    Circle.setFillColor( sf::Color( 255, 0, 0, (sf::Uint8) ( 255.f * DestructionTime.asSeconds() / DestructionDuration.asSeconds() ) ) );

    Window.draw( Circle );

    }

ParticleSystem * Asteroid::onCollision ( Planet * Other ) {

    destruct();

    auto * Explosion = new ParticleSystem ( );
    float Normal = PI + atan2f( Other->getPosition().y - getPosition().y, Other->getPosition().x - getPosition().x );
    float Velocity = sqrtf( getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y );

    Explosion->setOriginPosition( Other->getPosition() + sf::Vector2f( Other->getRadius() * cosf( Normal ), Other->getRadius() * sinf( Normal ) ) );
    Explosion->setOriginVelocity( sf::Vector2f( 0, 0 ) );
    Explosion->setAngleRange( Normal, 0.95f * PI );
    Explosion->setVelocityRange( 10.f, 10.f + 0.8f * Velocity );
    Explosion->setColorRange( sf::Color ( 25, 25, 50 ), sf::Color ( 125, 125, 150 ) );
    Explosion->setDuration( sf::seconds( 0.5f ), sf::seconds( 4.f ) );
    Explosion->generateParticles( (unsigned int) ( ( Velocity > 200.f ? 20000 : 10000 ) * ( getMass() / 10.f ) ) );

    return Explosion; }

ParticleSystem * Asteroid::onCollision ( Asteroid * Other ) {

    // TODO
    return nullptr;

    }

ParticleSystem * Asteroid::onCollision ( Spaceship * Other ) {

    // TODO
    return nullptr;

    }