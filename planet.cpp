#include "planet.hpp"

void Planet::update ( sf::Time ElapsedTime ) {

    RadialPhase += RadialVelocity * ElapsedTime.asSeconds();

    if ( RadialPhase > 1.f ) {

        RadialPhase = fmodf( RadialPhase, 1.f ); }

    for ( auto i = Clouds.begin(); i != Clouds.end(); ) {

        i->Begin -= CloudVelocity * ElapsedTime.asSeconds();
        i->End -= CloudVelocity * ElapsedTime.asSeconds();

        if ( ( i->End + i->Thickness ) <= 0.f ) {

            i = Clouds.erase( i ); }

        else {

            ++i; } }

    if ( CloudPauseTime.asSeconds() <= 0.f ) {

        Cloud NewCloud {};

        NewCloud.Thickness = 0.05f + 0.05f * getRandomFloat();
        NewCloud.Altitude = 1.f * getRandomFloat();
        NewCloud.Begin = 1.f + NewCloud.Thickness;
        NewCloud.End = NewCloud.Begin + ( 0.1f + 0.1f * getRandomFloat() );

        Clouds.push_back( NewCloud );
        CloudPauseTime = CloudPauseDuration; }

    CloudPauseTime -= ElapsedTime; }

void Planet::render ( sf::RenderWindow &Window ) {

    renderBuffer();

    sf::CircleShape Sprite;

    Sprite.setPointCount( 50 );
    Sprite.setRadius( getRadius() );
    Sprite.setOrigin( getRadius(), getRadius() );
    Sprite.setPosition( getPosition() );
    Sprite.setTexture( &Buffer.getTexture() );

    Window.draw( Sprite ); }

float Planet::getRandomFloat ( ) {

    return ( static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ); }

void Planet::generate ( ) {

    RadialPhase = 0.f;
    RadialVelocity = 0.025f + getRandomFloat() * 0.05f;
    CloudVelocity = 2.f * RadialVelocity + 0.025f;

    OceanColor = OceanPalette[ rand() % OceanPalette.size() ];
    SurfaceColor = SurfacePalette[ rand() % SurfacePalette.size() ];
    CloudColor = sf::Color( 255, 255, 255, 225 );

    CloudPauseTime = sf::seconds( 0.f );
    CloudPauseDuration = sf::seconds( 1.f * powf( 200.f / getRadius(), 2.f ) );

    for ( unsigned int i = 0; i < ( 10.f * powf( getRadius() / 200.f, 2.f ) ); i++ ) {

        auto Size = (unsigned int) ( ( 10.f + getRandomFloat() * 10.f ) * powf( getRadius() / 200.f, 2.f ) );
        sf::Vector2f Begin = sf::Vector2f( getRandomFloat() * 4.f * getRadius(), getRandomFloat() * 2.f * getRadius() );

        for ( unsigned int j = 0; j < Size; j++ ) {

            float Thickness = ( 0.05f + 0.05f * getRandomFloat() ) * 2.f * getRadius();
            float Length = ( 0.1f + 0.1f * getRandomFloat() ) * 2.f * getRadius();
            sf::Vector2f End = Begin + sf::Vector2f( Length, 0.f );

            renderIsland( Begin, End, Thickness );

            Begin.x += ( 0.1f - getRandomFloat() * 0.2f ) * getRadius();
            Begin.y += ( 0.1f - getRandomFloat() * 0.2f ) * getRadius(); } }

    Surface.display();

    for ( unsigned int i = 0; i < 100; i++ ) {

        update( sf::seconds( 0.1f ) ); } }

void Planet::renderBuffer ( ) {

    Buffer.clear( OceanColor );

    renderSurface();
    renderClouds();

    Buffer.display(); }

void Planet::renderSurface ( ) {

    sf::Sprite Sprite ( Surface.getTexture() );

    Sprite.setScale( ( 4.f * getRadius() ) / Surface.getSize().x, ( 2.f * getRadius() ) / Surface.getSize().y );
    Sprite.setPosition( ( 2.f * getRadius() ) * ( - 2.f * RadialPhase ), 0.f );

    Buffer.draw( Sprite );

    Sprite.setPosition( ( 2.f * getRadius() ) * ( 2.f - 2.f * RadialPhase ), 0.f );

    Buffer.draw( Sprite ); }

void Planet::renderIsland ( sf::Vector2f Begin, sf::Vector2f End, float Thickness, bool FixOverflow ) {

    float Angle = PI / 2.f;
    std::vector <sf::Vertex> Vertexes;

    for ( unsigned int i = 0; i <= 20; i++ ) {

        Vertexes.emplace_back( sf::Vertex( Begin + Thickness * sf::Vector2f( cosf( Angle ), sinf( Angle ) ), SurfaceColor ) );

        Angle += PI * ( 1.f / 20.f ); }

    for ( unsigned int i = 0; i <= 20; i++ ) {

        Vertexes.emplace_back( sf::Vertex( End + Thickness * sf::Vector2f( cosf( Angle ), sinf( Angle ) ), SurfaceColor ) );

        Angle += PI * ( 1.f / 20.f ); }

    Surface.draw( &Vertexes[0], Vertexes.size(), sf::TriangleFan );

    if ( FixOverflow ) {

        if ( ( Begin.x - Thickness ) < 0.f ) {

            renderIsland( Begin + sf::Vector2f( 4.f * getRadius(), 0.f ), End + sf::Vector2f( 4.f * getRadius(), 0.f ), Thickness, false ); }

        if ( ( End.x + Thickness ) > ( 4.f * getRadius() ) ) {

            renderIsland( Begin - sf::Vector2f( 4.f * getRadius(), 0.f ), End - sf::Vector2f( 4.f * getRadius(), 0.f ), Thickness, false ); } } }

void Planet::renderClouds ( ) {

    for ( Cloud& ActiveCloud : Clouds ) {

        renderCloud( ActiveCloud ); } }

void Planet::renderCloud ( Cloud &ActiveCloud ) {

    std::vector <sf::Vertex> Vertexes;

    float Angle = PI / 2.f;
    float Module = 2.f * getRadius() * ActiveCloud.Thickness;
    sf::Vector2f Begin = 2.f * getRadius() * sf::Vector2f( ActiveCloud.Begin, ActiveCloud.Altitude );
    sf::Vector2f End = 2.f * getRadius() * sf::Vector2f( ActiveCloud.End, ActiveCloud.Altitude );

    for ( unsigned int i = 0; i <= 20; i++ ) {

        Vertexes.emplace_back( sf::Vertex( Begin + Module * sf::Vector2f( cosf( Angle ), sinf( Angle ) ), CloudColor ) );

        Angle += PI * ( 1.f / 20.f ); }

    for ( unsigned int i = 0; i <= 20; i++ ) {

        Vertexes.emplace_back( sf::Vertex( End + Module * sf::Vector2f( cosf( Angle ), sinf( Angle ) ), CloudColor ) );

        Angle += PI * ( 1.f / 20.f ); }

    Buffer.draw( &Vertexes[0], Vertexes.size(), sf::TriangleFan ); }
