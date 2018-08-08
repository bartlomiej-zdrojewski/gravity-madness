#ifndef GRAVITY_MADNESS_MISSILE_HPP
#define GRAVITY_MADNESS_MISSILE_HPP

#include "asteroid.hpp"
#include "body.hpp"
#include "body-collision.hpp"
#include "constants.hpp"
#include "controllers/spaceship-controller.hpp"
#include "graphics-module.hpp"
#include "particle-system.hpp"
#include "planet.hpp"

class Missile : public Body {

public:

    Missile ( ) : Body ( 50.f, 15.f ) {

        ExplosionOnDestruction = true;
        ExplosionPower = 100.f;
        Thrust = 250.f;
        ThrustReduction = 25.f;

        ExplosionDelay = sf::seconds( 5.f );
        ExplosionTime = ExplosionDelay;

        Target = nullptr;

        }

    float getInfluenceRadius ( );

    float getExplosionPower ( );
    void setExplosionPower ( float ExplosionPower );

    float getThrust ( );
    void setThrust ( float Thrust );

    float getThrustReduction ( );
    void setThrustReduction ( float ThrustReduction );

    sf::Time getExplosionDelay ( );
    void setExplosionDelay ( sf::Time ExplosionDelay );

    Spaceship * getTarget ( );
    void setTarget ( Spaceship * Target );

    void update ( sf::Time ElapsedTime );
    void render ( sf::RenderWindow &Window );

    void onShot ( );
    ParticleSystem * onCollision ( Planet * Other );
    ParticleSystem * onCollision ( Asteroid * Other );
    ParticleSystem * onCollision ( Spaceship * Other );
    ParticleSystem * onCollision ( Missile * Other );
    ParticleSystem * onDestruction ( );

private:

    bool ExplosionOnDestruction;
    float ExplosionPower;
    float Thrust;
    float ThrustReduction;

    sf::Time ExplosionTime;
    sf::Time ExplosionDelay;

    Spaceship * Target;

    };

#endif
