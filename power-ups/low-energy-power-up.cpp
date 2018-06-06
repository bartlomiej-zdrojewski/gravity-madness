#include "low-energy-power-up.hpp"

void LowEnergyPowerUp::updateEffect ( sf::Time ElapsedTime ) {

    MySpaceship->updateEnergy( 2000.f + getRandomFloat() * 1000.f );

    Expired = true; }
