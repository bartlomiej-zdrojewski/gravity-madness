#ifndef GRAVITY_MADNESS_ASTEROID
#define GRAVITY_MADNESS_ASTEROID

#include <SFML/Graphics.hpp>
#include "body.hpp"
#include "planet.hpp"
#include "spaceship.hpp"

class Spaceship;

class Asteroid : public Body {

public:

    Asteroid ( float Mass, float Radius ) : Body ( Mass, Radius ) {

        ExistenceDuration = sf::seconds( 20.f );
        ExistenceTime = ExistenceDuration;
        DestructionDuration = sf::seconds( 2.f );
        DestructionTime = sf::seconds( 0.1f );
        // ...

        }

    void resetExistenceTime ( );

    void update ( sf::Time ElapsedTime );
    void render ( sf::RenderWindow &Window );

    ParticleSystem * onCollision ( Planet * Other );
    ParticleSystem * onCollision ( Asteroid * Other );
    ParticleSystem * onCollision ( Spaceship * Other );

private:

    sf::Time ExistenceTime;
    sf::Time ExistenceDuration;
    sf::Time DestructionTime;
    sf::Time DestructionDuration;

    // TODO ROTATION

    };

#endif