#ifndef GRAVITY_MADNESS_POWER_UP_HPP
#define GRAVITY_MADNESS_POWER_UP_HPP

#include <SFML/Graphics.hpp>
#include "../spaceship.hpp"

class PowerUp {

public:

    PowerUp ( sf::Time Duration, float * Gravity, unsigned int * AsteroidCount );

    bool isCaught ( );
    bool isExpired ( );

    bool isGravityModifier ( );
    bool isAsteroidModifier ( );

    sf::Vector2f getPosition ( );
    void setPosition ( sf::Vector2f Position );

    float getRadius ( );

    void update ( sf::Time ElapsedTime );
    void render ( sf::RenderWindow &Window );
    void finish ( );

    void onCatch ( Spaceship * MySpaceship );

protected:

    static float getRandomFloat ( );

    virtual void onEffectBegin ( ) { }
    virtual void onEffectEnd ( ) { }

    virtual void updateEffect ( sf::Time ElapsedTime ) {

        Expired = true; };

    Spaceship * MySpaceship;
    float * Gravity;
    unsigned int * AsteroidCount;
    sf::Texture Texture;

    bool Caught;
    bool Expired;

    bool GravityModifier;
    bool AsteroidModifier;

private:

    sf::Vector2f Position;
    const float Radius = 16.f;

    sf::Time FadeTime;
    sf::Time FadeDuration;
    sf::Time OscillationTime;
    sf::Vector2f OscillationFrequency;
    sf::Time ExistenceTime;

    };

#endif
