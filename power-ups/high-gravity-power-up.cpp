#include "high-gravity-power-up.hpp"

void HighGravityPowerUp::onEffectBegin ( ) {

    *Gravity = 5.f; }

void HighGravityPowerUp::onEffectEnd ( ) {

    *Gravity = 1.f; }

void HighGravityPowerUp::updateEffect ( sf::Time ElapsedTime ) {

    EffectDuration -= ElapsedTime;

    if ( EffectDuration.asSeconds() <= 0.f ) {

        finish(); } }
