#ifndef GRAVITY_MADNESS_ASTEROID
#define GRAVITY_MADNESS_ASTEROID

#include "body.hpp"
#include "body-collision.hpp"
#include "graphics-module.hpp"
#include "planet.hpp"
#include "spaceship.hpp"

class Spaceship;

class Asteroid : public Body {

public:

    Asteroid ( GraphicsModule * Graphics, float Mass, float Radius ) : Body ( Mass, Radius ) {

        this->Graphics = Graphics;

        if ( Radius < 12.f ) {

            Texture = Graphics->getTexture( "AsteroidSmall" + std::to_string( 1 + rand() % 3 ) ); }

        else if ( Radius < 18.f ) {

            Texture = Graphics->getTexture( "AsteroidMedium" + std::to_string( 1 + rand() % 3 ) ); }

        else {

            Texture = Graphics->getTexture( "AsteroidBig" + std::to_string( 1 + rand() % 3 ) ); }

        Angle = ( - PI ) + getRandomFloat() * ( 2.f * PI );
        AngularSpeed = 0.1f + getRandomFloat() * 2.9f;

        ExistenceDuration = sf::seconds( 20.f );
        ExistenceTime = ExistenceDuration;
        DestructionDuration = sf::seconds( 2.f );
        DestructionTime = sf::seconds( 0.1f ); }

    void resetExistenceTime ( );

    void update ( sf::Time ElapsedTime );
    void render ( sf::RenderWindow &Window );

    ParticleSystem * onCollision ( Planet * Other );
    ParticleSystem * onCollision ( Asteroid * Other );

private:

    static float getRandomFloat ( );

private:

    GraphicsModule * Graphics;
    sf::Texture Texture;

    float Angle;
    float AngularSpeed;

    sf::Time ExistenceTime;
    sf::Time ExistenceDuration;
    sf::Time DestructionTime;
    sf::Time DestructionDuration;

    };

#endif