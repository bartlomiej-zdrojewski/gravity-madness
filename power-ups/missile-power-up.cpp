#include "missile-power-up.hpp"

void MissilePowerUp::updateEffect ( sf::Time ElapsedTime ) {

    MySpaceship->updateMissileCount( 1 );

    Expired = true; }
