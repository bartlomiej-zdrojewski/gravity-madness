#include "low-health-power-up.hpp"

void * LowHealthPowerUp::clone ( GraphicsModule * Graphics ) {

    auto NewPowerUp = new LowHealthPowerUp ( Graphics, Gravity, AsteroidCount );

    NewPowerUp->setPosition( getPosition() );

    return NewPowerUp; }

void LowHealthPowerUp::onEffectBegin ( ) {

    MySpaceship->updateHealth( 100.f + getRandomFloat() * 50.f );

    finish(); }
