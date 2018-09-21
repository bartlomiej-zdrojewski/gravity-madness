#ifndef GRAVITY_MADNESS_PLANET
#define GRAVITY_MADNESS_PLANET

#include "body.hpp"
#include "graphics-module.hpp"

class Planet : public Body {

public:

    explicit Planet ( GraphicsModule * Graphics, float Mass, float Radius ) : Body ( Mass, Radius ) {

        OceanPalette.emplace_back( sf::Color( 142, 36, 170 ) ); // #8E24AA
        OceanPalette.emplace_back( sf::Color( 94, 53, 177 ) ); // #5E35B1
        OceanPalette.emplace_back( sf::Color( 57, 73, 171 ) ); // #3949AB
        OceanPalette.emplace_back( sf::Color( 30, 136, 229 ) ); // #1E88E5
        OceanPalette.emplace_back( sf::Color( 3, 155, 229 ) ); // #039BE5
        OceanPalette.emplace_back( sf::Color( 0, 172, 193 ) ); // #00ACC1

        SurfacePalette.emplace_back( sf::Color( 198, 40, 40 ) ); // #C62828
        SurfacePalette.emplace_back( sf::Color( 173, 20, 87 ) ); // #AD1457
        SurfacePalette.emplace_back( sf::Color( 46, 125, 50 ) ); // #2E7D32
        SurfacePalette.emplace_back( sf::Color( 85, 139, 47 ) ); // #558B2F
        SurfacePalette.emplace_back( sf::Color( 78, 52, 46 ) ); // #4E342E
        SurfacePalette.emplace_back( sf::Color( 66, 66, 66 ) ); // #424242

        #if ( SFML_VERSION_MINOR >= 5 )

            sf::ContextSettings Context;
            Context.antialiasingLevel = Graphics->getAntialiasingLevel();

            Buffer.create( (unsigned int) ( 2.f * getRadius() ), (unsigned int) ( 2.f * getRadius() ), Context );
            Surface.create( (unsigned int) ( 4.f * getRadius() ), (unsigned int) ( 2.f * getRadius() ), Context );

        #else

            Buffer.create( (unsigned int) ( 2.f * getRadius() ), (unsigned int) ( 2.f * getRadius() ) );
            Surface.create( (unsigned int) ( 4.f * getRadius() ), (unsigned int) ( 2.f * getRadius() ) );

        #endif

        generate(); }

    void update ( sf::Time ElapsedTime );
    void render ( sf::RenderWindow &Window );

private:

    struct Cloud {

        float Begin;
        float End;
        float Altitude;
        float Thickness;

        };

private:

    static float getRandomFloat ( );

    void generate ( );

    void renderBuffer ( );
    void renderSurface ( );
    void renderIsland ( sf::Vector2f Begin, sf::Vector2f End, float Thickness, bool FixOverflow = true );
    void renderClouds ( );
    void renderCloud ( Cloud &ActiveCloud );

private:

    sf::RenderTexture Buffer;
    sf::RenderTexture Surface;

    float RadialPhase;
    float RadialVelocity;
    float CloudVelocity;

    sf::Color OceanColor;
    sf::Color SurfaceColor;
    sf::Color CloudColor;

    std::vector <sf::Color> OceanPalette;
    std::vector <sf::Color> SurfacePalette;

    sf::Time CloudPauseTime;
    sf::Time CloudPauseDuration;
    std::list <Cloud> Clouds;

    };

#endif
