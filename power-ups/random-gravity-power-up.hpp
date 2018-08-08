#ifndef GRAVITY_MADNESS_RANDOM_GRAVITY_POWER_UP_HPP
#define GRAVITY_MADNESS_RANDOM_GRAVITY_POWER_UP_HPP

#include "../graphics-module.hpp"
#include "power-up.hpp"

class RandomGravityPowerUp : public PowerUp {

public:

    RandomGravityPowerUp ( GraphicsModule * Graphics, float * Gravity, unsigned int * AsteroidCount ) :
                           PowerUp ( sf::seconds( 30.f ), Gravity, AsteroidCount ) {

        Texture = Graphics->getTexture( "power-up-random-gravity" );
        GravityModifier = true;

        EffectTime = sf::seconds( 0.f );
        EffectDuration = sf::seconds( 30.f );

        for ( unsigned int i = 0; i < 5; i++ ) {

            Amplitude[i] = 0.15f + 0.85f * getRandomFloat();
            Frequency[i] = 0.1f + 1.9f * getRandomFloat();
            Offset[i] = 0.5f + 0.5f * getRandomFloat();
            Phase[i] = asinf( 0.2f / Amplitude[i] - Offset[i] ); } }

private:

    void onEffectBegin ( );
    void onEffectEnd ( );

    void updateEffect ( sf::Time ElapsedTime );

private:

    float Amplitude [5];
    float Frequency [5];
    float Phase [5];
    float Offset [5];

    sf::Time EffectTime;
    sf::Time EffectDuration;

    };

#endif
