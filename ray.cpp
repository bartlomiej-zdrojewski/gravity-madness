#include "ray.hpp"

Ray::Ray ( sf::Vector2f Position, float Angle ) {

    while ( Angle > M_PI ) {

        Angle -= 2.f * M_PI; }

    while ( Angle < - M_PI ) {

        Angle += 2.f * M_PI; }

    if ( Angle == ( PI / 2.f ) && Angle == ( - PI / 2.f ) ) {

        Angle += ALMOST_ZERO; }

    xe = ALMOST_INFINITY;

    if ( Angle > ( PI / 2.f ) ) {

        Angle -= PI;
        xe *= - 1.f; }

    else if ( Angle < ( - PI / 2.f ) ) {

        Angle += PI;
        xe *= - 1.f; }

    a = tanf( Angle );
    b = Position.y - a * Position.x;
    xs = Position.x;

    Color = sf::Color ( 255, 255, 255 );
    RenderingTime = sf::seconds( 0.f );
    RenderingDuration = sf::seconds( 1.f );

    RayBegin = sf::Vector2f ( xs, a * xs + b );
    RayEnd = sf::Vector2f ( xe, a * xe + b );
    RayOpacity = 1.f; }

bool Ray::isRenderingEnabled ( ) {

    return RenderingTime.asSeconds() > 0.f; }

void Ray::enableRendering ( ) {

    RenderingTime = RenderingDuration;
    RayOpacity = 1.f; }

void Ray::enableRendering ( float Limit ) {

    RenderingTime = RenderingDuration;
    RayEnd = sf::Vector2f ( Limit, a * Limit + b );
    RayOpacity = 1.f; }

sf::Color Ray::getColor ( ) {

    return Color; }

void Ray::setColor ( sf::Color Color ) {

    this->Color = Color; }

bool Ray::getIntersection ( Shape * MyShape, sf::Vector2f &Intersection, float &Distance ) {

    sf::Vector2f Begin = sf::Vector2f( xs, a * xs + b );
    sf::Vector2f End = sf::Vector2f( xe, a * xe + b );

    return MyShape->getIntersection( Begin, End, Intersection, Distance ); }

bool Ray::getIntersection ( sf::Vector2f Center, float Radius, sf::Vector2f &Intersection, float &Distance ) {

    const float l = 1 + a * a;
    const float m = 2 * ( a * ( b - Center.y ) - Center.x );
    const float n = b * b + Center.x * Center.x + Center.y * Center.y - Radius * Radius - 2 * b * Center.y;

    float Delta = m * m - 4 * l * n;

    if ( Delta < 0.f ) {

        Intersection.x = xe;
        Intersection.y = a * Intersection.x + b;
        Distance = 1000000.f;

        return false; }

    else if ( Delta > 0.f ) {

        float IntersectionA = ( - m - sqrtf( Delta ) ) / ( 2 * l );
        float IntersectionB = ( - m + sqrtf( Delta ) ) / ( 2 * l );

        if ( fabsf( xs - IntersectionA ) < fabsf( xs - IntersectionB ) ) { // because |xe| >> |xs|

            Intersection.x = IntersectionA; }

        else {

            Intersection.x = IntersectionB; } }

    else {

        Intersection.x = ( - m ) / ( 2 * l ); }

    if ( ( xe >= xs && ( Intersection.x < xs || Intersection.x > xe ) ) || ( xe < xs && ( Intersection.x > xs || Intersection.x < xe ) ) ) {

        Intersection.x = xe;
        Intersection.y = a * Intersection.x + b;
        Distance = 1000000.f;

        return false; }

    Intersection.y = a * Intersection.x + b;

    const float DistanceX = xs - Intersection.x;
    const float DistanceY = ( a * xs + b ) - Intersection.y;

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

    Vertices.emplace_back( sf::Vertex( RayBegin, sf::Color( Color.r, Color.g, Color.b, (sf::Uint8) ( RayOpacity * 255.f ) ) ) );
    Vertices.emplace_back( sf::Vertex( RayEnd, sf::Color( Color.r, Color.g, Color.b, (sf::Uint8) ( RayOpacity * 255.f ) ) ) );

    Window.draw( &Vertices[0], Vertices.size(), sf::Lines ); }

void Ray::render ( sf::RenderTexture &Buffer ) {

    if ( !isRenderingEnabled() ) {

        return; }

    std::vector <sf::Vertex> Vertices;

    Vertices.emplace_back( sf::Vertex( RayBegin, sf::Color( Color.r, Color.g, Color.b, (sf::Uint8) ( RayOpacity * 255.f ) ) ) );
    Vertices.emplace_back( sf::Vertex( RayEnd, sf::Color( Color.r, Color.g, Color.b, (sf::Uint8) ( RayOpacity * 255.f ) ) ) );

    Buffer.draw( &Vertices[0], Vertices.size(), sf::Lines ); }
