#include <iostream>
#include "ray.hpp"

Ray::Ray ( sf::Vector2f Position, float Angle ) {

    while ( Angle > M_PI ) {

        Angle -= 2.f * M_PI; }

    while ( Angle < - M_PI ) {

        Angle += 2.f * M_PI; }

    if ( Angle == ( PI / 2.f ) && Angle == ( - PI / 2.f ) ) {

        Angle += 0.01f; }

    x1 = 1000000.f;

    if ( Angle > ( PI / 2.f ) ) {

        Angle -= PI;
        x1 *= - 1.f; }

    else if ( Angle < ( - PI / 2.f ) ) {

        Angle += PI;
        x1 *= - 1.f; }

    a = tanf( Angle );
    b = Position.y - a * Position.x;
    x0 = Position.x;

    RenderingTime = sf::seconds( 0.f );
    RenderingDuration = sf::seconds( 1.f );

    RayBegin = sf::Vector2f ( x0, a * x0 + b );
    RayEnd = sf::Vector2f ( x1, a * x1 + b );
    RayOpacity = 1.f; }

void Ray::enableRendering ( ) {

    RenderingTime = RenderingDuration;
    RayOpacity = 1.f; }

void Ray::enableRendering ( float Limit ) {

    RenderingTime = RenderingDuration;
    RayEnd = sf::Vector2f ( Limit, a * Limit + b );
    RayOpacity = 1.f; }

bool Ray::isRenderingEnabled ( ) {

    return RenderingTime.asSeconds() > 0.f; }

bool Ray::getIntersection ( sf::Vector2f Center, float Radius, sf::Vector2f &Intersection, float &Distance ) {

    const float m = Center.x;
    const float n = Center.y;
    const float r = Radius;

    const float i = 1 + a * a;
    const float j = 2 * a * ( b - n ) - 2 * m;
    const float k = b * b + m * m + n * n - r * r - 2 * b * n;

    float Delta = j * j - 4 * i * k;

    if ( Delta < 0.f ) {

        Intersection.x = x1;
        Intersection.y = a * Intersection.x + b;
        Distance = 1000000.f;

        return false; }

    else if ( Delta > 0.f ) {

        float IntersectionA = ( - j - sqrtf( Delta ) ) / ( 2 * i );
        float IntersectionB = ( - j + sqrtf( Delta ) ) / ( 2 * i );

        if ( fabsf( x0 - IntersectionA ) < fabsf( x0 - IntersectionB ) ) { // because |x1| >> |x0|

            Intersection.x = IntersectionA; }

        else {

            Intersection.x = IntersectionB; } }

    else {

        Intersection.x = ( - j ) / ( 2 * i ); }

    if ( ( x1 >= x0 && ( Intersection.x < x0 || Intersection.x > x1 ) ) || ( x1 < x0 && ( Intersection.x > x0 || Intersection.x < x1 ) ) ) {

        Intersection.x = x1;
        Intersection.y = a * Intersection.x + b;
        Distance = 1000000.f;

        return false; }

    Intersection.y = a * Intersection.x + b;

    const float DistanceX = x0 - Intersection.x;
    const float DistanceY = ( a * x0 + b ) - Intersection.y;

    Distance = sqrtf( DistanceX * DistanceX + DistanceY * DistanceY );

    return true; }

void Ray::update ( sf::Time ElapsedTime ) {

    if ( !isRenderingEnabled() ) {

        return; }

    RenderingTime -= ElapsedTime;
    RayOpacity = RenderingTime.asSeconds() / RenderingDuration.asSeconds(); }

void Ray::render ( sf::RenderWindow &Window ) {

    if ( !isRenderingEnabled() ) {

        return; }

    std::vector <sf::Vertex> Vertices;

    Vertices.push_back( sf::Vertex( RayBegin, sf::Color( 0, 255, 0, (sf::Uint8) ( RayOpacity * 255.f ) ) ) );
    Vertices.push_back( sf::Vertex( RayEnd, sf::Color( 0, 255, 0, (sf::Uint8) ( RayOpacity * 255.f ) ) ) );

    Window.draw( &Vertices[0], Vertices.size(), sf::Lines );

    }