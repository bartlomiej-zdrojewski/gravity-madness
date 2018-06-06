#ifndef GRAVITY_MADNESS_HIGH_ENERGY_POWER_UP_HPP
#define GRAVITY_MADNESS_HIGH_ENERGY_POWER_UP_HPP

#include "../graphics-module.hpp"
#include "power-up.hpp"

class HighEnergyPowerUp : public PowerUp {

public:

    HighEnergyPowerUp ( GraphicsModule * Graphics, float Radius, float * Gravity, unsigned int * AsteroidCount ) :
                        PowerUp ( Radius, sf::seconds( 60.f ), Gravity, AsteroidCount ) {

        Texture = Graphics->getTexture( "power-up-high-energy" ); }

private:

    void updateEffect ( sf::Time ElapsedTime );

    };

#endif
