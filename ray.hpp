#ifndef GRAVITY_MADNESS_RAY_HPP
#define GRAVITY_MADNESS_RAY_HPP

#include <cmath>
#include <SFML/Graphics.hpp>
#include "constants.hpp"

class Ray {

public:

    Ray ( sf::Vector2f Position, float Angle );

    void enableRendering ( );
    void enableRendering ( float Limit );
    bool isRenderingEnabled ( );

    sf::Color getColor ( );
    void setColor ( sf::Color Color );

    bool getIntersection ( sf::Vector2f Center, float Radius, sf::Vector2f &Intersection, float &Distance );

    void update ( sf::Time ElapsedTime );
    void render ( sf::RenderWindow &Window );

private:

    float a;
    float b;
    float x0;
    float x1;

    sf::Color Color;
    sf::Time RenderingTime;
    sf::Time RenderingDuration;

    sf::Vector2f RayBegin, RayEnd;
    float RayOpacity;

    };

#endif
