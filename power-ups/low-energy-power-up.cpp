#include "low-energy-power-up.hpp"

void LowEnergyPowerUp::onEffectBegin ( ) {

    MySpaceship->updateEnergy( 2000.f + getRandomFloat() * 1000.f );

    finish(); }
