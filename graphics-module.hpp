#ifndef GRAVITY_MADNESS_GRAPHICS_MODULE
#define GRAVITY_MADNESS_GRAPHICS_MODULE

#include <iostream> // TODO TEMP

#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "script.hpp"
#include "logger.hpp"

class GraphicsModule : public Logger {

public:

    GraphicsModule ( Script * Config, int8_t * InitState ) : Config ( Config ), InitState( InitState ), Logger ( ) {

        ImageState = 0; }

    ~ GraphicsModule ( );

    void init ( );
    void initContext ( );

    sf::Texture * getTexture ( std::string Name );
    sf::Font * getFont ( std::string Name );

private:

    struct GraphicFile {

        std::string Name;
        std::string Path;

        };

    Script * Config;
    int8_t * InitState;
    volatile int8_t ImageState;

    std::string ImageName;
    sf::Image ImageBuffer;

    std::unordered_map <std::string, sf::Texture*> Textures;
    std::unordered_map <std::string, sf::Font*> Fonts;

    };

#endif