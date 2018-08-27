#ifndef GRAVITY_MADNESS_LOW_HEALTH_POWER_UP_HPP
#define GRAVITY_MADNESS_LOW_HEALTH_POWER_UP_HPP

#include "../graphics-module.hpp"
#include "power-up.hpp"

class LowHealthPowerUp : public PowerUp {

public:

    LowHealthPowerUp ( GraphicsModule * Graphics, float * Gravity, unsigned int * AsteroidCount ) :
                       PowerUp ( sf::seconds( 30.f ), Gravity, AsteroidCount ) {

        Texture = Graphics->getTexture( "PowerUpLowHealth" ); }

private:

    void onEffectBegin ( );

    };

#endif
