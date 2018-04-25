#include "spaceship.hpp"

SpaceshipController * Spaceship::getSpaceshipController ( ) {

    return Controller; }

void Spaceship::setSpaceshipController ( SpaceshipController * Controller ) {

    this->Controller = Controller; }

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

            updateVelocity( Acceleration, ElapsedTime ); }

        else if ( Controller->onThrustBackward() ) { // TODO CALIBRATE

            float MinimumVelocity = 1.f;

            if ( fabsf( getVelocity().x ) > MinimumVelocity || fabsf( getVelocity().y ) > MinimumVelocity ) {

                float Angle = getVelocityAngle() + 3.14159f;

                sf::Vector2f Acceleration;
                Acceleration.x = Thrust * cosf( Angle );
                Acceleration.y = Thrust * sinf( Angle );

                // TODO SOME ANIMATION

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