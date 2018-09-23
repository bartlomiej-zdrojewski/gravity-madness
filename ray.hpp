#ifndef GRAVITY_MADNESS_RAY
#define GRAVITY_MADNESS_RAY

#include <cmath>
#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "shape.hpp"

class Ray {

public:

    Ray ( sf::Vector2f Position, float Angle );

    bool isRenderingEnabled ( );
    void enableRendering ( );
    void enableRendering ( float Limit );

    sf::Color getColor ( );
    void setColor ( sf::Color Color );

    bool getIntersection ( Shape * MyShape, sf::Vector2f &Intersection, float &Distance );
    bool getIntersection ( sf::Vector2f Center, float Radius, sf::Vector2f &Intersection, float &Distance );

    void update ( sf::Time ElapsedTime );
    void render ( sf::RenderWindow &Window );
    void render ( sf::RenderTexture &Buffer );

private:

    float a;
    float b;
    float xs;
    float xe;

    sf::Color Color;
    sf::Time RenderingTime;
    sf::Time RenderingDuration;

    sf::Vector2f RayBegin, RayEnd;
    float RayOpacity;

    };

#endif
