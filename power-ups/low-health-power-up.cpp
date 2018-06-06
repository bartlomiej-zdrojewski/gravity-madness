#include "low-health-power-up.hpp"

void LowHealthPowerUp::updateEffect ( sf::Time ElapsedTime ) {

    MySpaceship->updateHealth( 100.f + getRandomFloat() * 50.f );

    Expired = true; }
