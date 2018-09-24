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
#include "shape.hpp"

class Missile : public Body {

public:

    Missile ( ) : Body ( 50.f, 20.f ) {

        MySpaceship = nullptr;
        MyScore = nullptr;
        MyShape = new Shape ( );
        Target = nullptr;

        MyShape->loadOutline( "(0.71,0.00),(0.53,13.00),(0.12,104.00),(0.50,135.00),(0.68,153.00),(0.35,162.00),(0.50,162.00),"
                              "(0.50,-162.00),(0.35,-162.00),(0.68,-153.00),(0.50,-135.00),(0.12,-104.00),(0.53,-13.00)", 20.f );

        Thrust = 250.f;
        ThrustReduction = 25.f;
        ExplosionPower = 100.f;
        ExplosionOnDestruction = true;

        ThrusterAngleOffset = 0.f;
        ThrusterMaximumAngleOffset = 0.1f * PI;

        ExplosionDelay = sf::seconds( 5.f );
        ExplosionTime = ExplosionDelay; }

    ~ Missile ( );

    void setSpaceship ( Spaceship * MySpaceship );
    void setScoreCounter ( ScoreCounter * MyScore );

    Shape * getShape ( );
    sf::FloatRect getInfluenceArea ( );

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
    void render ( sf::RenderWindow &Window, bool Debug = false );
    void render ( sf::RenderTexture &Buffer );

    void onShot ( );
    ParticleSystem * onCollision ( Planet * Other );
    ParticleSystem * onCollision ( Asteroid * Other );
    ParticleSystem * onCollision ( Spaceship * Other );
    ParticleSystem * onCollision ( Missile * Other );
    ParticleSystem * onDestruction ( );

private:

    Spaceship * MySpaceship;
    ScoreCounter * MyScore;
    Shape * MyShape;
    Spaceship * Target;

    float Thrust;
    float ThrustReduction;
    float ExplosionPower;
    bool ExplosionOnDestruction;
    sf::Time ReactionTime;
    sf::Time ReactionDuration;

    sf::Texture Texture;
    sf::Texture ThrusterTexture;
    float ThrusterAngleOffset;
    float ThrusterMaximumAngleOffset;
    ParticleSystem ThrusterExhaust;

    sf::Time ExplosionTime;
    sf::Time ExplosionDelay;

    };

#endif
