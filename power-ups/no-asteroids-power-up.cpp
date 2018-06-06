#include "no-asteroids-power-up.hpp"

void NoAsteroidsPowerUp::onEffectBegin ( ) {

    AsteroidCountCopy = *AsteroidCount;
    *AsteroidCount = 0; }

void NoAsteroidsPowerUp::onEffectEnd ( ) {

    *AsteroidCount = AsteroidCountCopy; }

void NoAsteroidsPowerUp::updateEffect ( sf::Time ElapsedTime ) {

    EffectDuration -= ElapsedTime;

    if ( EffectDuration.asSeconds() <= 0.f ) {

        onEffectEnd();

        Expired = true; } }
