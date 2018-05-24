#ifndef GRAVITY_MADNESS_POWER_UP_HPP
#define GRAVITY_MADNESS_POWER_UP_HPP

#include <SFML/Graphics.hpp>
#include "spaceship.hpp"

class PowerUp {

public:

    PowerUp ( float Radius, sf::Time Duration, float * Gravity, unsigned int * AsteroidCount );

    bool isCaught ( );
    bool isExpired ( );

    bool isGravityModifier ( );
    bool isAsteroidModifier ( );

    sf::Vector2f getPosition ( );
    void setPosition ( sf::Vector2f Position );

    float getRadius ( );
    void setRadius ( float Radius );

    void update ( sf::Time ElapsedTime );
    void render ( sf::RenderWindow &Window );
    void finish ( );

    void onCatch ( Spaceship * MySpaceship );

protected:

    float getRandomFloat ( );

    virtual void onEffectBegin ( ) { }
    virtual void onEffectEnd ( ) { }

    virtual void updateEffect ( sf::Time ElapsedTime ) {

        Expired = true; };

    Spaceship * MySpaceship;
    float * Gravity;
    unsigned int * AsteroidCount;
    sf::Texture * Texture;

    bool Caught;
    bool Expired;

    bool GravityModifier;
    bool AsteroidModifier;

private:

    float Radius;
    sf::Vector2f Position;
    sf::Time ExistenceTime;

    };

#endif
