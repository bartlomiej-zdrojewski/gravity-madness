#include "energy-power-up.hpp"

void EnergyPowerUp::updateEffect ( sf::Time ElapsedTime ) {

    MySpaceship->updateEnergy( 1000.f );

    Expired = true; }
