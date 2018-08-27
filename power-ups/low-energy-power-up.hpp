#ifndef GRAVITY_MADNESS_LOW_ENERGY_POWER_UP_HPP
#define GRAVITY_MADNESS_LOW_ENERGY_POWER_UP_HPP

#include "../graphics-module.hpp"
#include "power-up.hpp"

class LowEnergyPowerUp : public PowerUp {

public:

    LowEnergyPowerUp ( GraphicsModule * Graphics, float * Gravity, unsigned int * AsteroidCount ) :
                       PowerUp ( sf::seconds( 30.f ), Gravity, AsteroidCount ) {

        Texture = Graphics->getTexture( "PowerUpLowEnergy" ); }

private:

    void onEffectBegin ( );

    };

#endif
