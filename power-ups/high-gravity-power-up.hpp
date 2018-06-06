#ifndef GRAVITY_MADNESS_HIGH_GRAVITY_POWER_UP_HPP
#define GRAVITY_MADNESS_HIGH_GRAVITY_POWER_UP_HPP

#include "../graphics-module.hpp"
#include "power-up.hpp"

class HighGravityPowerUp : public PowerUp {

public:

    HighGravityPowerUp ( GraphicsModule * Graphics, float Radius, float * Gravity, unsigned int * AsteroidCount ) :
                         PowerUp ( Radius, sf::seconds( 30.f ), Gravity, AsteroidCount ) {

        Texture = Graphics->getTexture( "power-up-high-gravity" );
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
