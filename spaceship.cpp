#include <iostream>
#include "spaceship.hpp"

Spaceship::~Spaceship ( ) {

    if ( Controller ) {

        Controller->setSpaceship( nullptr ); } }

SpaceshipController * Spaceship::getController ( ) {

    return Controller; }

void Spaceship::setController ( SpaceshipController * Controller ) {

    this->Controller = Controller;

    if ( Controller ) {

        Controller->setSpaceship( this ); } }

float Spaceship::getHealth ( ) {

    return Health; }

void Spaceship::setHealth ( float Health ) {

    this->Health = Health; }

float Spaceship::getHealthRestoration ( ) {

    return HealthRestoration; }

void Spaceship::setHealthRestoration ( float HealthRestoration ) {

    this->HealthRestoration = HealthRestoration; }

float Spaceship::getHealthLimit ( ) {

    return HealthLimit; }

void Spaceship::setHealthLimit ( float HealthLimit ) {

    this->HealthLimit = HealthLimit; }

void Spaceship::updateHealth ( float DeltaHealth ) {

    Health += DeltaHealth;

    if ( Health <= 0.f ) {

        Health = 0.f;
        Energy = 0.f;

        destruct(); }

    else if ( Health > HealthLimit ) {

        Health = HealthLimit; } }

float Spaceship::getEnergy ( ) {

    return Energy; }

void Spaceship::setEnergy ( float Energy ) {

    this->Energy = Energy; }

float Spaceship::getEnergyRestoration ( ) {

    return EnergyRestoration; }

void Spaceship::setEnergyRestoration ( float EnergyRestoration ) {

    this->EnergyRestoration = EnergyRestoration; }

float Spaceship::getEnergyLimit ( ) {

    return EnergyLimit; }

void Spaceship::setEnergyLimit ( float EnergyLimit ) {

    this->EnergyLimit = EnergyLimit; }

void Spaceship::updateEnergy ( float DeltaEnergy ) {

    Energy += DeltaEnergy;

    if ( Energy < 0.f ) {

        Energy = 0.f; }

    else if ( Energy > EnergyLimit ) {

        Energy = EnergyLimit; } }

void Spaceship::updateEnergy ( sf::Vector2f Acceleration, sf::Time ElapsedTime ) {

    const float DeltaEnergy = ElapsedTime.asSeconds() * sqrtf( Acceleration.x * Acceleration.x + Acceleration.y * Acceleration.y );

    updateEnergy( - DeltaEnergy ); }

float Spaceship::getThrust ( ) {

    return Thrust; }

void Spaceship::setThrust ( float Thrust ) {

    this->Thrust = Thrust; }

float Spaceship::getRayPower ( ) {

    return RayPower; }

void Spaceship::setRayPower ( float RayPower ) {

    this->RayPower = RayPower; }

void Spaceship::update ( sf::Event &Event ) {

    if ( Controller ) {

        Controller->update( Event ); } }

void Spaceship::update ( sf::Time ElapsedTime ) {

    updateHealth( HealthRestoration * ElapsedTime.asSeconds() );
    updateEnergy( EnergyRestoration * ElapsedTime.asSeconds() );

    if ( Controller ) {

        Controller->update( ElapsedTime );

        if ( Controller->onThrustForward() && Energy >= ( Thrust * ElapsedTime.asSeconds() ) ) {

            float Angle = getVelocityAngle();

            if ( Controller->onThrustLeft() ) {

                Angle -= PI / 3.f; }

            else if ( Controller->onThrustRight() ) {

                Angle += PI / 3.f; }

            sf::Vector2f Acceleration;
            Acceleration.x = Thrust * cosf( Angle );
            Acceleration.y = Thrust * sinf( Angle );

            // TODO SOME ANIMATION

            updateEnergy( Acceleration, ElapsedTime );
            updateVelocity( Acceleration, ElapsedTime ); }

        if ( Controller->onThrustBackward() && Energy >= ( Thrust * ElapsedTime.asSeconds() ) ) {

            const float MinimumVelocity = 1.f;

            if ( fabsf( getVelocity().x ) > MinimumVelocity || fabsf( getVelocity().y ) > MinimumVelocity ) {

                float Angle = getVelocityAngle() + PI;
                float Module = sqrtf( getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y );

                sf::Vector2f Acceleration;
                Acceleration.x = SuppressingFactor * Module * cosf( Angle );
                Acceleration.y = SuppressingFactor * Module * sinf( Angle );

                // TODO SOME ANIMATION

                updateEnergy( Acceleration, ElapsedTime );
                updateVelocity( Acceleration, ElapsedTime ); } }

        if ( Controller->onRayShot() && Energy >= RayPower ) {

            RayShot = true;

            updateEnergy( - RayPower ); }

        if ( Controller->onMissileShot() ) {

            if ( true ) { // TODO CHECK MISSILES

                MissileShot = true; } } }

    updatePosition( ElapsedTime );

    // ...

    }

void Spaceship::render ( sf::RenderWindow &Window ) { // TODO

    sf::CircleShape Circle;

    Circle.setRadius( getRadius() );
    Circle.setOrigin( getRadius(), getRadius() );
    Circle.setFillColor( sf::Color::Blue );

    Circle.setPosition( getPosition() );
    Window.draw( Circle );

    Circle.setFillColor( sf::Color::Green );
    Circle.setPosition( getPosition() + sf::Vector2f( 5.f * cosf( getVelocityAngle() ), 5.f * sinf( getVelocityAngle() ) ) );
    Window.draw( Circle );

    }

bool Spaceship::onRayShot ( ) {

    if ( RayShot ) {

        RayShot = false;

        return true; }

    return false; }

bool Spaceship::onMissileShot ( ) {

    if ( MissileShot ) {

        MissileShot = false;

        return true; }

    return false; }

void Spaceship::onCollision ( Planet * Other ) {

    // TODO CHANGE VELOCITY TO PREPARE PARTICLE EFFECT

    // setVelocity( ... );
    setHealth( 0.f );
    setEnergy( 0.f );

    destruct(); }

void Spaceship::onCollision ( Spaceship * Other ) {

    // TODO MAKE DAMAGE AND DESTRUCT IF NECESSARY

    }

void Spaceship::onDestruction ( ) {

    // TODO SOME PARTICLE EFFECT

    }