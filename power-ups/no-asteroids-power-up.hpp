#ifndef GRAVITY_MADNESS_NO_ASTEROIDS_POWER_UP
#define GRAVITY_MADNESS_NO_ASTEROIDS_POWER_UP

#include "../graphics-module.hpp"
#include "power-up.hpp"

class NoAsteroidsPowerUp : public PowerUp {

public:

    NoAsteroidsPowerUp ( GraphicsModule * Graphics, float * Gravity, unsigned int * AsteroidCount ) :
                         PowerUp ( sf::seconds( 15.f ), Gravity, AsteroidCount ) {

        Texture = Graphics->getTexture( "PowerUpNoAsteroids" );
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
