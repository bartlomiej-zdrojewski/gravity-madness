#include "high-health-power-up.hpp"

void HighHealthPowerUp::onEffectBegin ( ) {

    MySpaceship->updateHealth( 250.f + getRandomFloat() * 100.f );

    finish(); }
