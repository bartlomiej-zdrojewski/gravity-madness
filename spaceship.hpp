#ifndef GRAVITY_MADNESS_SPACESHIP
#define GRAVITY_MADNESS_SPACESHIP

#include "definitions.hpp"
#include "body.hpp"
#include "planet.hpp"
#include "spaceship-controller.hpp"
#include "graphics-module.hpp"

class SpaceshipController;

class Spaceship : public Body {

public:

    explicit Spaceship ( float Radius ) : Body ( 1.f, Radius ) {

        Controller = nullptr;
        RayShot = false;
        MissileShot = false;

        Health = 250.f;
        HealthLimit = 250.f;
        HealthRestoration = 1.f;
        Energy = 5000.f;
        EnergyLimit = 5000.f;
        EnergyRestoration = 5.f;
        Thrust = 100.f;
        SuppressingFactor = 0.75f;
        RayPower = 25.f;
        // ...

        }

    ~ Spaceship ( );

    SpaceshipController * getController ( );
    void setController ( SpaceshipController * Controller );

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

    float getRayPower ( );
    void setRayPower ( float RayPower );

    void update ( sf::Event &Event );
    void update ( sf::Time ElapsedTime );
    void render ( sf::RenderWindow &Window );

    bool onRayShot ( );
    bool onMissileShot ( );

    void onCollision ( Planet * Other );
    void onCollision ( Spaceship * Other );
    void onDestruction ( );

private:

    SpaceshipController * Controller;

    bool RayShot;
    bool MissileShot;

    float Health;
    float HealthRestoration;
    float HealthLimit;
    float Energy;
    float EnergyLimit;
    float EnergyRestoration;
    float Thrust;
    float SuppressingFactor;
    float RayPower;

    };

#endif
