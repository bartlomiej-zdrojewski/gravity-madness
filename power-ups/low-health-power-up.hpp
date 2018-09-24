#ifndef GRAVITY_MADNESS_LOW_HEALTH_POWER_UP
#define GRAVITY_MADNESS_LOW_HEALTH_POWER_UP

#include "../graphics-module.hpp"
#include "power-up.hpp"

class LowHealthPowerUp : public PowerUp {

public:

    LowHealthPowerUp ( GraphicsModule * Graphics, float * Gravity, unsigned int * AsteroidCount ) :
                       PowerUp ( sf::seconds( 30.f ), Gravity, AsteroidCount ) {

        Texture = Graphics->getTexture( "PowerUpLowHealth" ); }

    void * clone ( GraphicsModule * Graphics );

private:

    void onEffectBegin ( );

    };

#endif
