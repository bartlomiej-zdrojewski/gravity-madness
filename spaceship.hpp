#ifndef GRAVITY_MADNESS_SPACESHIP
#define GRAVITY_MADNESS_SPACESHIP

#include "body.hpp"
#include "planet.hpp"
#include "spaceship-controller.hpp"
#include "graphics-module.hpp"

class Spaceship : public Body {

public:

    explicit Spaceship ( float Radius ) : Body ( 1.f, Radius ) {

        Controller = nullptr;
        RayShot = false;
        MissileShot = false;

        Thrust = 100.f;
        // ...

        }

    SpaceshipController * getSpaceshipController ( );
    void setSpaceshipController ( SpaceshipController * Controller );

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

    float Thrust;

    };

#endif
