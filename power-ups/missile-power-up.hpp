#ifndef GRAVITY_MADNESS_MISSILE_POWER_UP_HPP
#define GRAVITY_MADNESS_MISSILE_POWER_UP_HPP

#include "../graphics-module.hpp"
#include "power-up.hpp"

class MissilePowerUp : public PowerUp {

public:

    MissilePowerUp ( GraphicsModule * Graphics, float * Gravity, unsigned int * AsteroidCount ) :
                     PowerUp ( sf::seconds( 60.f ), Gravity, AsteroidCount ) {

        Texture = Graphics->getTexture( "power-up-missile" ); }

private:

    void onEffectBegin ( );

    };

#endif
