#include <iostream>
#include "missile.hpp"

float Missile::getInfluenceRadius ( ) {

    // TODO
    return getRadius();

    }

float Missile::getExplosionPower ( ) {

    return ExplosionPower; }

void Missile::setExplosionPower ( float ExplosionPower ) {

    this->ExplosionPower = ExplosionPower; }

float Missile::getThrust ( ) {

    return Thrust; }

void Missile::setThrust ( float Thrust ) {

    this->Thrust = Thrust; }

float Missile::getThrustReduction ( ) {

    return ThrustReduction; }

void Missile::setThrustReduction ( float ThrustReduction ) {

    this->ThrustReduction = ThrustReduction; }

sf::Time Missile::getExplosionDelay ( ) {

    return ExplosionDelay; }

void Missile::setExplosionDelay ( sf::Time ExplosionDelay ) {

    ExplosionTime = ExplosionDelay;
    this->ExplosionDelay = ExplosionDelay; }

Spaceship * Missile::getTarget ( ) {

    return Target; }

void Missile::setTarget ( Spaceship * Target ) {

    this->Target = Target; }
    
void Missile::update ( sf::Time ElapsedTime ) {

    ExplosionTime -= ElapsedTime;

    if ( ExplosionTime.asSeconds() <= 0.f ) {

        destruct(); }

    else {

        float Angle = getVelocityAngle();

        if ( Target ) {

            float AngleDifference = atan2f( Target->getPosition().y - getPosition().y, Target->getPosition().x - getPosition().x );
            AngleDifference = normalizeAngle( Angle - AngleDifference );

            if ( AngleDifference > 0.f ) {

                Angle -= PI / 3.f; }

            else if ( AngleDifference < 0.f ) {

                Angle += PI / 3.f; } }

        Thrust -= ThrustReduction * ElapsedTime.asSeconds();

        if ( Thrust > 0.f ) {

            sf::Vector2f Acceleration;
            Acceleration.x = Thrust * cosf( Angle );
            Acceleration.y = Thrust * sinf( Angle );

            updateVelocity( Acceleration, ElapsedTime ); }

        updatePosition( ElapsedTime ); } }

void Missile::render ( sf::RenderWindow &Window ) { // TODO

    sf::CircleShape Circle;

    Circle.setRadius( getRadius() );
    Circle.setOrigin( getRadius(), getRadius() );
    Circle.setPosition( getPosition() );
    Circle.setFillColor( sf::Color( 0, 0, 255 ) );

    Window.draw( Circle );

    }

ParticleSystem * Missile::onCollision ( Planet * Other ) { // TODO

    destruct();
    return nullptr;

    }

ParticleSystem * Missile::onCollision ( Asteroid * Other ) { // TODO

    destruct();
    return nullptr;

    }

ParticleSystem * Missile::onCollision ( Spaceship * Other ) { // TODO

    Other->updateHealth( - ExplosionPower );

    destruct();
    return nullptr;

    }

ParticleSystem * Missile::onCollision ( Missile * Other ) {

    destruct();
    return nullptr;

    }

ParticleSystem * Missile::onDestruction ( ) { // TODO

    if ( !ExplosionOnDestruction ) {

        return nullptr; }

    auto * Explosion = new ParticleSystem ( );

    Explosion->setOriginPosition( getPosition() );
    Explosion->setOriginVelocity( getVelocity() );
    Explosion->setAngleRange( 0.f, PI );
    Explosion->setVelocityRange( - 100.f, 100.f );
    Explosion->setColorRange( sf::Color ( 200, 0, 50 ), sf::Color ( 255, 50, 150 ) );
    Explosion->setDuration( sf::seconds( 1.f ), sf::seconds( 3.f ) );
    Explosion->generateParticles( (unsigned int) ( ExplosionPower * 20 ) );

    return Explosion; }
