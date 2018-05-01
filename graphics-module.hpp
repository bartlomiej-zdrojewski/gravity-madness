#ifndef GRAVITY_MADNESS_GRAPHICS_MODULE
#define GRAVITY_MADNESS_GRAPHICS_MODULE

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "logger.hpp"
#include "script.hpp"

class GraphicsModule : public Logger {

public:

    GraphicsModule ( Script * Config, int8_t * InitState ) : Config ( Config ), InitState( InitState ), Logger ( ) {

        ImageState = 0;
        WindowWidth = 0;
        WindowHeight = 0;
        FullScreen = false;
        AntyaliasingLevel = 0;

        initDefault(); }

    ~ GraphicsModule ( );

    void init ( );
    void initContext ( );

    unsigned int getWindowWidth ( );
    unsigned int getWindowHeight ( );
    void setWindowSize ( unsigned int Width, unsigned int Height );

    bool isFullScreenEnabled ( );
    void enableFullScreen ( );
    void disableFullScreen ( );

    unsigned int getAntyaliasingLevel ( );
    void setAntyaliasingLevel ( unsigned int AntyaliasingLevel );

    sf::Texture& getTexture ( std::string Name );
    sf::Font& getFont ( std::string Name );

private:

    void initDefault ( );

    struct GraphicFile {

        std::string Name;
        std::string Path;

        };

    Script * Config;
    int8_t * InitState;

    volatile int8_t ImageState;
    std::string ImageName;
    sf::Image ImageBuffer;

    unsigned int WindowWidth;
    unsigned int WindowHeight;
    bool FullScreen;
    unsigned int AntyaliasingLevel;

    std::unordered_map <std::string, sf::Texture*> Textures;
    std::unordered_map <std::string, sf::Font*> Fonts;

    };

#endif