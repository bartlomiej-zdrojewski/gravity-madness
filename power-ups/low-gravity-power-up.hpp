#ifndef GRAVITY_MADNESS_LOW_GRAVITY_POWER_UP_HPP
#define GRAVITY_MADNESS_LOW_GRAVITY_POWER_UP_HPP

#include "../graphics-module.hpp"
#include "power-up.hpp"

class LowGravityPowerUp : public PowerUp {

public:

    LowGravityPowerUp ( GraphicsModule * Graphics, float Radius, float * Gravity, unsigned int * AsteroidCount ) :
                        PowerUp ( Radius, sf::seconds( 30.f ), Gravity, AsteroidCount ) {

        Texture = Graphics->getTexture( "power-up-low-gravity" );
        GravityModifier = true;
        EffectDuration = sf::seconds( 15.f ); }

private:

    void onEffectBegin ( );
    void onEffectEnd ( );

    void updateEffect ( sf::Time ElapsedTime );

private:

    sf::Time EffectDuration;

    };

#endif
