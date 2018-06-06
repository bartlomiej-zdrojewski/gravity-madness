#ifndef GRAVITY_MADNESS_LOW_ENERGY_POWER_UP_HPP
#define GRAVITY_MADNESS_LOW_ENERGY_POWER_UP_HPP

#include "../graphics-module.hpp"
#include "power-up.hpp"

class LowEnergyPowerUp : public PowerUp {

public:

    LowEnergyPowerUp ( GraphicsModule * Graphics, float Radius, float * Gravity, unsigned int * AsteroidCount ) :
                       PowerUp ( Radius, sf::seconds( 60.f ), Gravity, AsteroidCount ) {

        Texture = Graphics->getTexture( "power-up-low-energy" ); }

private:

    void updateEffect ( sf::Time ElapsedTime );

    };

#endif
