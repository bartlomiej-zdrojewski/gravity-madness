#include "missile-power-up.hpp"

void MissilePowerUp::onEffectBegin ( ) {

    MySpaceship->updateMissileCount( 1 );

    finish(); }
