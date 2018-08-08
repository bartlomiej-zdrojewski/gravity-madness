#ifndef GRAVITY_MADNESS_HIGH_ENERGY_POWER_UP_HPP
#define GRAVITY_MADNESS_HIGH_ENERGY_POWER_UP_HPP

#include "../graphics-module.hpp"
#include "power-up.hpp"

class HighEnergyPowerUp : public PowerUp {

public:

    HighEnergyPowerUp ( GraphicsModule * Graphics, float * Gravity, unsigned int * AsteroidCount ) :
                        PowerUp ( sf::seconds( 60.f ), Gravity, AsteroidCount ) {

        Texture = Graphics->getTexture( "PowerUpHighEnergy" ); }

private:

    void onEffectBegin ( );

    };

#endif
