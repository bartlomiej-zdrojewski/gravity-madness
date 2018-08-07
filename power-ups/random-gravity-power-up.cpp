#include "random-gravity-power-up.hpp"

void RandomGravityPowerUp::onEffectBegin ( ) {

    *Gravity = 1.f; }

void RandomGravityPowerUp::onEffectEnd ( ) {

    *Gravity = 1.f; }

void RandomGravityPowerUp::updateEffect ( sf::Time ElapsedTime ) {

    EffectTime += ElapsedTime;

    if ( EffectTime < EffectDuration ) {

        *Gravity = 0.f;

        for ( unsigned int i = 0; i < 5; i++ ) {

            *Gravity += Amplitude[i] * ( Offset[i] + sinf( Frequency[i] * ( EffectTime.asSeconds() ) + Phase[i] ) ); } }

    else {

        finish(); } }
