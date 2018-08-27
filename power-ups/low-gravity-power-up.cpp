#include "low-gravity-power-up.hpp"

void LowGravityPowerUp::onEffectBegin ( ) {

    *Gravity = 0.2f; }

void LowGravityPowerUp::onEffectEnd ( ) {

    *Gravity = 1.f; }

void LowGravityPowerUp::updateEffect ( sf::Time ElapsedTime ) {

    EffectDuration -= ElapsedTime;

    if ( EffectDuration.asSeconds() <= 0.f ) {

        finish(); } }
