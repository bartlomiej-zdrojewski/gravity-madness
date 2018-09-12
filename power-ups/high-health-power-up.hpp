#ifndef GRAVITY_MADNESS_HIGH_HEALTH_POWER_UP
#define GRAVITY_MADNESS_HIGH_HEALTH_POWER_UP

#include "../graphics-module.hpp"
#include "power-up.hpp"

class HighHealthPowerUp : public PowerUp {

public:

    HighHealthPowerUp ( GraphicsModule * Graphics, float * Gravity, unsigned int * AsteroidCount ) :
                        PowerUp ( sf::seconds( 30.f ), Gravity, AsteroidCount ) {

        Texture = Graphics->getTexture( "PowerUpHighHealth" ); }

private:

    void onEffectBegin ( );

    };

#endif
