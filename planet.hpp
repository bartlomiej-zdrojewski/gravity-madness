#ifndef GRAVITY_MADNESS_PLANET
#define GRAVITY_MADNESS_PLANET

#include "body.hpp"
#include "graphics-module.hpp"

class Planet : public Body {

public:

    explicit Planet ( GraphicsModule * Graphics, float Mass, float Radius ) : Body ( Mass, Radius ) {

        // TODO OCEAN PALETTE
        OceanPalette.emplace_back( sf::Color( 94, 53, 177 ) ); // #5E35B1
        OceanPalette.emplace_back( sf::Color( 57, 73, 171 ) ); // #3949AB
        OceanPalette.emplace_back( sf::Color( 30, 136, 229 ) ); // #1E88E5
        OceanPalette.emplace_back( sf::Color( 3, 155, 229 ) ); // #039BE5
        OceanPalette.emplace_back( sf::Color( 0, 172, 193 ) ); // #00ACC1
        OceanPalette.emplace_back( sf::Color( 0, 137, 123 ) ); // #00897B

        // TODO SURFACE PALETTE
        SurfacePalette.emplace_back( sf::Color( 255, 255, 255 ) ); // #FFFFFF
        SurfacePalette.emplace_back( sf::Color( 255, 255, 255 ) ); // #FFFFFF
        SurfacePalette.emplace_back( sf::Color( 255, 255, 255 ) ); // #FFFFFF
        SurfacePalette.emplace_back( sf::Color( 255, 255, 255 ) ); // #FFFFFF
        SurfacePalette.emplace_back( sf::Color( 255, 255, 255 ) ); // #FFFFFF
        SurfacePalette.emplace_back( sf::Color( 255, 255, 255 ) ); // #FFFFFF

        #if ( SFML_VERSION_MINOR >= 5 )

            sf::ContextSettings Context;
            Context.antialiasingLevel = Graphics->getAntialiasingLevel();

            Buffer.create( (unsigned int) ( 2.f * getRadius() ), (unsigned int) ( 2.f * getRadius() ), Context );

        #else

            Buffer.create( (unsigned int) ( 2.f * getRadius() ), (unsigned int) ( 2.f * getRadius() ) );

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
    void renderClouds ( );
    void renderCloud ( Cloud &ActiveCloud );

private:

    sf::RenderTexture Buffer;

    float RadialPhase;
    float RadialVelocity;
    float CloudVelocity;

    sf::Color OceanColor;
    sf::Color SurfaceColor;
    sf::Color CloudColor;

    std::vector <sf::Color> OceanPalette;
    std::vector <sf::Color> SurfacePalette;
    std::vector <sf::Color> CloudPalette;

    sf::Time CloudPauseTime;
    sf::Time CloudPauseDuration;
    std::list <Cloud> Clouds;

    };

#endif
