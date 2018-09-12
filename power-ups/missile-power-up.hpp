#ifndef GRAVITY_MADNESS_MISSILE_POWER_UP
#define GRAVITY_MADNESS_MISSILE_POWER_UP

#include "../graphics-module.hpp"
#include "power-up.hpp"

class MissilePowerUp : public PowerUp {

public:

    MissilePowerUp ( GraphicsModule * Graphics, float * Gravity, unsigned int * AsteroidCount ) :
                     PowerUp ( sf::seconds( 30.f ), Gravity, AsteroidCount ) {

        Texture = Graphics->getTexture( "PowerUpMissile" ); }

private:

    void onEffectBegin ( );

    };

#endif
