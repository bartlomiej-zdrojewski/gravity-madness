#include <iostream>
#include "spaceship.hpp"

SpaceshipController * Spaceship::getSpaceshipController ( ) {

    return Controller; }

void Spaceship::setSpaceshipController ( SpaceshipController * Controller ) {

    this->Controller = Controller;

    if ( Controller ) {

        Controller->setSpaceship( this ); } }

void Spaceship::setEnergy ( float Energy ) {

    this->Energy = Energy; }

float Spaceship::getEnergy ( ) {

    return Energy; }

void Spaceship::updateEnergy ( float DeltaEnergy ) {

    Energy += DeltaEnergy;

    if ( Energy < 0.f ) {

        Energy = 0.f; } }

void Spaceship::updateEnergy ( sf::Vector2f Acceleration, sf::Time ElapsedTime ) {

    const float DeltaEnergy = ElapsedTime.asSeconds() * sqrtf( Acceleration.x * Acceleration.x + Acceleration.y * Acceleration.y );

    updateEnergy( - DeltaEnergy ); }

void Spaceship::update ( sf::Event &Event ) {

    if ( Controller ) {

        Controller->update( Event ); } }

void Spaceship::update ( sf::Time ElapsedTime ) {

    if ( Controller ) {

        Controller->update( ElapsedTime );

        if ( Controller->onThrustForward() ) {

            float Angle = getVelocityAngle();

            if ( Controller->onThrustLeft() ) {

                Angle -= 3.14159f / 3.f; }

            else if ( Controller->onThrustRight() ) {

                Angle += 3.14159f / 3.f; }

            sf::Vector2f Acceleration;
            Acceleration.x = Thrust * cosf( Angle );
            Acceleration.y = Thrust * sinf( Angle );

            // TODO SOME ANIMATION

            updateEnergy( Acceleration, ElapsedTime );
            updateVelocity( Acceleration, ElapsedTime ); }

        else if ( Controller->onThrustBackward() ) {

            const float MinimumVelocity = 1.f;

            if ( fabsf( getVelocity().x ) > MinimumVelocity || fabsf( getVelocity().y ) > MinimumVelocity ) {

                float Angle = getVelocityAngle() + 3.14159f;
                float Module = sqrtf( getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y );

                sf::Vector2f Acceleration;
                Acceleration.x = SuppressingFactor * Module * cosf( Angle );
                Acceleration.y = SuppressingFactor * Module * sinf( Angle );

                // TODO SOME ANIMATION

                updateEnergy( Acceleration, ElapsedTime );
                updateVelocity( Acceleration, ElapsedTime ); } }

        // ...

        }

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

    destruct(); }

void Spaceship::onCollision ( Spaceship * Other ) {

    // TODO MAKE DAMAGE AND DESTRUCT IF NECESSARY

    }

void Spaceship::onDestruction ( ) {

    // TODO SOME PARTICLE EFFECT

    }