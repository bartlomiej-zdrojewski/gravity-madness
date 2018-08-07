#include "more-asteroids-power-up.hpp"

void MoreAsteroidsPowerUp::onEffectBegin ( ) {

    AsteroidCountCopy = *AsteroidCount;
    *AsteroidCount *= 2; }

void MoreAsteroidsPowerUp::onEffectEnd ( ) {

    *AsteroidCount = AsteroidCountCopy; }

void MoreAsteroidsPowerUp::updateEffect ( sf::Time ElapsedTime ) {

    EffectDuration -= ElapsedTime;

    if ( EffectDuration.asSeconds() <= 0.f ) {

        finish(); } }
