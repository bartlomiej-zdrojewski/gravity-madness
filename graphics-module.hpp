#ifndef GRAVITY_MADNESS_GRAPHICS_MODULE
#define GRAVITY_MADNESS_GRAPHICS_MODULE

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "logger.hpp"
#include "script.hpp"

class GraphicsModule : public Logger {

public:

    GraphicsModule ( Script * Config, int8_t * InitState ) : Config ( Config ), InitState( InitState ), Logger ( ) {

        InitProgress = 0.f;
        ImageState = 0;
        WindowWidth = 0;
        WindowHeight = 0;
        FullScreen = false;
        EpilepsyProtection = false;
        AntialiasingLevel = 0;

        initDefault(); }

    ~ GraphicsModule ( );

    void init ( );
    void initContext ( );
    float getInitProgress ( );

    unsigned int getWindowWidth ( );
    unsigned int getWindowHeight ( );
    void setWindowSize ( unsigned int Width, unsigned int Height );

    bool isFullScreenEnabled ( );
    void enableFullScreen ( );
    void disableFullScreen ( );

    bool isEpilepsyProtectionEnabled ( );
    void enableEpilepsyProtection ( );
    void disableEpilepsyProtection ( );

    unsigned int getAntialiasingLevel ( );
    void setAntialiasingLevel ( unsigned int AntialiasingLevel );

    sf::Texture& getTexture ( std::string Name );
    sf::Font& getFont ( std::string Name );

private:

    void initDefault ( );

    struct GraphicFile {

        std::string Name;
        std::string Path;

        };

private:

    Script * Config;
    int8_t * InitState;
    float InitProgress;

    volatile int8_t ImageState;
    std::string ImageName;
    sf::Image ImageBuffer;

    unsigned int WindowWidth;
    unsigned int WindowHeight;
    bool FullScreen;
    bool EpilepsyProtection;
    unsigned int AntialiasingLevel;

    std::unordered_map <std::string, sf::Texture*> Textures;
    std::unordered_map <std::string, sf::Font*> Fonts;

    };

#endif