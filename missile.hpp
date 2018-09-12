#ifndef GRAVITY_MADNESS_MISSILE
#define GRAVITY_MADNESS_MISSILE

#include "asteroid.hpp"
#include "body.hpp"
#include "body-collision.hpp"
#include "constants.hpp"
#include "controllers/spaceship-controller.hpp"
#include "graphics-module.hpp"
#include "particle-system.hpp"
#include "planet.hpp"
#include "score-counter.hpp"

class Missile : public Body {

public:

    Missile ( ) : Body ( 50.f, 15.f ) {

        MySpaceship = nullptr;
        MyScore = nullptr;
        Target = nullptr;

        ExplosionOnDestruction = true;
        ExplosionPower = 100.f;
        Thrust = 250.f;
        ThrustReduction = 25.f;

        // ThrusterTexture;
        ThrusterAngleOffset = 0.f;
        ThrusterMaximumAngleOffset = 0.1f * PI;

        ExplosionDelay = sf::seconds( 5.f );
        ExplosionTime = ExplosionDelay; }

    void setSpaceship ( Spaceship * MySpaceship );
    void setScoreCounter ( ScoreCounter * MyScore );

    float getInfluenceRadius ( );

    float getExplosionPower ( );
    void setExplosionPower ( float ExplosionPower );

    float getThrust ( );
    void setThrust ( float Thrust );

    float getThrustReduction ( );
    void setThrustReduction ( float ThrustReduction );

    sf::Time getExplosionDelay ( );
    void setExplosionDelay ( sf::Time ExplosionDelay );

    void setTexture ( sf::Texture &Texture );
    void setThrusterTexture ( sf::Texture &ThrusterTexture );

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

    Spaceship * MySpaceship;
    ScoreCounter * MyScore;
    Spaceship * Target;

    bool ExplosionOnDestruction;
    float ExplosionPower;
    float Thrust;
    float ThrustReduction;

    sf::Texture Texture;
    sf::Texture ThrusterTexture;
    float ThrusterAngleOffset;
    float ThrusterMaximumAngleOffset;
    ParticleSystem ThrusterExhaust;

    sf::Time ExplosionTime;
    sf::Time ExplosionDelay;

    };

#endif
