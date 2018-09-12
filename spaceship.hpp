#ifndef GRAVITY_MADNESS_SPACESHIP
#define GRAVITY_MADNESS_SPACESHIP

#include "asteroid.hpp"
#include "body.hpp"
#include "controllers/spaceship-controller.hpp"
#include "constants.hpp"
#include "particle-system.hpp"
#include "planet.hpp"

class Asteroid;
class SpaceshipController;

class Spaceship : public Body {

public:

    explicit Spaceship ( float Mass, float Radius ) : Body ( Mass, Radius ) {

        Controller = nullptr;
        RayShot = false;
        MissileShot = false;
        ExplosionOnDestruction = true;

        Health = 250.f;
        HealthLimit = 250.f;
        HealthRestoration = 2.f;
        Energy = 5000.f;
        EnergyLimit = 5000.f;
        EnergyRestoration = 40.f;
        Thrust = 120.f;
        BrakingFactor = 0.75f;
        RayPower = 30.f;
        RayColor = sf::Color( 255, 0, 0 );
        MissileCount = 3;
        MissileLimit = 5;
        ThrusterAngleOffset = 0.f;
        ThrusterMaximumAngleOffset = 0.1f * PI; }

    ~ Spaceship ( );

    SpaceshipController * getController ( );
    void setController ( SpaceshipController * Controller );

    float getInfluenceRadius ( );

    float getHealth ( );
    void setHealth ( float Health );
    float getHealthRestoration ( );
    void setHealthRestoration ( float HealthRestoration );
    float getHealthLimit ( );
    void setHealthLimit ( float HealthLimit );
    void updateHealth ( float DeltaHealth );

    float getEnergy ( );
    void setEnergy ( float Energy );
    float getEnergyRestoration ( );
    void setEnergyRestoration ( float EnergyRestoration );
    float getEnergyLimit ( );
    void setEnergyLimit ( float EnergyLimit );
    void updateEnergy ( float DeltaEnergy );
    void updateEnergy ( sf::Vector2f Acceleration, sf::Time ElapsedTime );

    float getThrust ( );
    void setThrust ( float Thrust );

    float getBrakingFactor ( );
    void setBrakingFactor ( float BrakingFactor );

    float getRayPower ( );
    void setRayPower ( float RayPower );
    sf::Color getRayColor ( );
    void setRayColor ( sf::Color RayColor );

    unsigned int getMissileCount ( );
    void setMissileCount ( unsigned int MissileCount );
    unsigned int getMissileLimit ( );
    void setMissileLimit ( unsigned int MissileLimit );
    void updateMissileCount ( int DeltaMissileCount );

    void setTexture ( sf::Texture &Texture );
    void setAccentTexture ( sf::Texture &AccentTexture, sf::Color AccentColor );
    void setThrusterTexture ( sf::Texture &ThrusterTexture, sf::Color ThrusterFuelColor );

    void update ( sf::Event &Event );
    void update ( sf::Time ElapsedTime );
    void render ( sf::RenderWindow &Window );

    bool onRayShot ( );
    bool onMissileShot ( );

    ParticleSystem * onCollision ( Planet * Other );
    ParticleSystem * onCollision ( Asteroid * Other );
    ParticleSystem * onCollision ( Spaceship * Other );
    ParticleSystem * onDestruction ( );

private:

    SpaceshipController * Controller;

    bool RayShot;
    bool MissileShot;
    bool ExplosionOnDestruction;

    float Health;
    float HealthRestoration;
    float HealthLimit;
    float Energy;
    float EnergyRestoration;
    float EnergyLimit;
    float Thrust;
    float BrakingFactor;
    float RayPower;
    sf::Color RayColor;
    unsigned int MissileCount;
    unsigned int MissileLimit;

    sf::Texture Texture;
    sf::Texture AccentTexture;
    sf::Texture ThrusterTexture;
    sf::Color AccentColor;
    float ThrusterAngleOffset;
    float ThrusterMaximumAngleOffset;
    ParticleSystem ThrusterExhaust;
    sf::Color ThrusterFuelColor;

    };

#endif
