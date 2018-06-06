#ifndef GRAVITY_MADNESS_NO_ASTEROIDS_POWER_UP_HPP
#define GRAVITY_MADNESS_NO_ASTEROIDS_POWER_UP_HPP

#include "../graphics-module.hpp"
#include "power-up.hpp"

class NoAsteroidsPowerUp : public PowerUp {

public:

    NoAsteroidsPowerUp ( GraphicsModule * Graphics, float Radius, float * Gravity, unsigned int * AsteroidCount ) :
                         PowerUp ( Radius, sf::seconds( 30.f ), Gravity, AsteroidCount ) {

        Texture = Graphics->getTexture( "power-up-no-asteroids" );
        AsteroidModifier = true;
        EffectDuration = sf::seconds( 30.f ); }

private:

    void onEffectBegin ( );
    void onEffectEnd ( );

    void updateEffect ( sf::Time ElapsedTime );

private:

    unsigned int AsteroidCountCopy;
    sf::Time EffectDuration;

    };

#endif
