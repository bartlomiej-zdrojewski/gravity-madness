#include "energy-power-up.hpp"

void EnergyPowerUp::updateEffect ( sf::Time ElapsedTime ) {

    MySpaceship->updateEnergy( 2500.f );

    Expired = true; }
