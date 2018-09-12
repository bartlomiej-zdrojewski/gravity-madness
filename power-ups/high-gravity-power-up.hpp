#ifndef GRAVITY_MADNESS_HIGH_GRAVITY_POWER_UP
#define GRAVITY_MADNESS_HIGH_GRAVITY_POWER_UP

#include "../graphics-module.hpp"
#include "power-up.hpp"

class HighGravityPowerUp : public PowerUp {

public:

    HighGravityPowerUp ( GraphicsModule * Graphics, float * Gravity, unsigned int * AsteroidCount ) :
                         PowerUp ( sf::seconds( 15.f ), Gravity, AsteroidCount ) {

        Texture = Graphics->getTexture( "PowerUpHighGravity" );
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
