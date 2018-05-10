#ifndef GRAVITY_MADNESS_COLLISION_HPP
#define GRAVITY_MADNESS_COLLISION_HPP

#include "body.hpp"

class BodyCollision {

public:

    enum Types {

        Elastic,
        Inelastic

        };

    BodyCollision ( Types Type, Body * First, Body * Second, float Efficiency = 1.f );

    sf::Vector2f getFirstVelocity ( );
    sf::Vector2f getSecondVelocity ( );
    float getReleasedEnergy ( );

private:

    float getLength ( sf::Vector2f Vector );

private:

    sf::Vector2f FirstVelocity;
    sf::Vector2f SecondVelocity;
    float ReleasedEnergy;

    };

#endif
