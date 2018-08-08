#ifndef GRAVITY_MADNESS_HIGH_HEALTH_POWER_UP_HPP
#define GRAVITY_MADNESS_HIGH_HEALTH_POWER_UP_HPP

#include "../graphics-module.hpp"
#include "power-up.hpp"

class HighHealthPowerUp : public PowerUp {

public:

    HighHealthPowerUp ( GraphicsModule * Graphics, float * Gravity, unsigned int * AsteroidCount ) :
                        PowerUp ( sf::seconds( 60.f ), Gravity, AsteroidCount ) {

        Texture = Graphics->getTexture( "power-up-high-health" ); }

private:

    void onEffectBegin ( );

    };

#endif
