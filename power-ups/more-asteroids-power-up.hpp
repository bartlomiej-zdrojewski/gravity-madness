#ifndef GRAVITY_MADNESS_MORE_ASTEROIDS_POWER_UP_HPP
#define GRAVITY_MADNESS_MORE_ASTEROIDS_POWER_UP_HPP

#include "../graphics-module.hpp"
#include "power-up.hpp"

class MoreAsteroidsPowerUp : public PowerUp {

public:

    MoreAsteroidsPowerUp ( GraphicsModule * Graphics, float * Gravity, unsigned int * AsteroidCount ) :
                           PowerUp ( sf::seconds( 30.f ), Gravity, AsteroidCount ) {

        Texture = Graphics->getTexture( "power-up-more-asteroids" );
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
