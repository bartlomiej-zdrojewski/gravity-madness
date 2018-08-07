#include "high-energy-power-up.hpp"

void HighEnergyPowerUp::onEffectBegin ( ) {

    MySpaceship->updateEnergy( 4000.f + getRandomFloat() * 2000.f );

    finish(); }
