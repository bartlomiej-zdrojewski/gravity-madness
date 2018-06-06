#include "high-energy-power-up.hpp"

void HighEnergyPowerUp::updateEffect ( sf::Time ElapsedTime ) {

    MySpaceship->updateEnergy( 4000.f + getRandomFloat() * 2000.f );

    Expired = true; }
