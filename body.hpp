#ifndef GRAVITY_MADNESS_BODY
#define GRAVITY_MADNESS_BODY

#include <cmath>
#include <SFML/Graphics.hpp>

class Body {

public:

    Body ( float Mass, float Radius );

    float getAngle ( sf::Vector2f Vector );
    float normalizeAngle ( float Angle );

    float getMass ( );
    void setMass ( float Mass );

    float getRadius ( );
    void setRadius ( float Radius );

    sf::Vector2f getPosition ( );
    void setPosition ( sf::Vector2f Position );
    void updatePosition ( sf::Time ElapsedTime );

    sf::Vector2f getVelocity ( );
    float getVelocityAngle ( );
    void setVelocity ( sf::Vector2f Velocity );
    void updateVelocity ( sf::Vector2f Acceleration, sf::Time ElapsedTime );

    void destruct ( );
    bool isDestructed ( );

    virtual void onDestruction ( ) { }

private:

    float Mass;
    float Radius;
    bool Destructed;

    sf::Vector2f Position;
    sf::Vector2f Velocity;

    };

#endif