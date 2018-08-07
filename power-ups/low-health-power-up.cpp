#include "low-health-power-up.hpp"

void LowHealthPowerUp::onEffectBegin ( ) {

    MySpaceship->updateHealth( 100.f + getRandomFloat() * 50.f );

    finish(); }
