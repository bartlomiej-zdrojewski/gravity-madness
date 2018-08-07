#ifndef GRAVITY_MADNESS_LOW_HEALTH_POWER_UP_HPP
#define GRAVITY_MADNESS_LOW_HEALTH_POWER_UP_HPP

#include "../graphics-module.hpp"
#include "power-up.hpp"

class LowHealthPowerUp : public PowerUp {

public:

    LowHealthPowerUp ( GraphicsModule * Graphics, float Radius, float * Gravity, unsigned int * AsteroidCount ) :
                       PowerUp ( Radius, sf::seconds( 60.f ), Gravity, AsteroidCount ) {

        Texture = Graphics->getTexture( "power-up-low-health" ); }

private:

    void onEffectBegin ( );

    };

#endif
