#include "planet.hpp"

void Planet::update ( sf::Time ElapsedTime ) {

    // TODO

    }

void Planet::render ( sf::RenderWindow &Window ) { // TODO

    sf::CircleShape Circle;

    Circle.setRadius( getRadius() );
    Circle.setOrigin( getRadius(), getRadius() );
    Circle.setPosition( getPosition() );
    Circle.setFillColor( sf::Color::Red );

    Window.draw( Circle );

    }