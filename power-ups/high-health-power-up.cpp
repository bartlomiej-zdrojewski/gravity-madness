#include "high-health-power-up.hpp"

void HighHealthPowerUp::updateEffect ( sf::Time ElapsedTime ) {

    MySpaceship->updateHealth( 250.f + getRandomFloat() * 100.f );

    Expired = true; }
