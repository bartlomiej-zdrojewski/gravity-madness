#ifndef GRAVITY_MADNESS_WORLD_MODULE
#define GRAVITY_MADNESS_WORLD_MODULE

#include <iostream> // TODO TEMP

#include "script.hpp"
#include "graphics-module.hpp"
#include "logger-manager.hpp"

class WorldModule : public Logger {

public:

    enum Modes {

        Idle,
        Init,
        InitTimeWarning,
        InitTimeError,
        RunTimeError,
        MainMenu,
        Game,
        PauseMenu,
        ScoreMenu,
        Finish,
        Debug

        };

    explicit WorldModule ( Script Config ) : Config ( Config ), Logger ( ) {

        Mode = Modes::Init;

        Script * GraphicsConfig = nullptr;
        Script * SoundsConfig = nullptr;

        if ( !config( Config, GraphicsConfig, SoundsConfig ) ) {

            Mode = Modes::Idle;

            return; }

        Log = new LoggerManager ( "log.txt" );
        Graphics = new GraphicsModule ( GraphicsConfig, &InitState );
        // Sounds = new SoundsModule ( );

        InitState = 0;
        VideoChanged = false;

        Log->manage( getLogger() );
        Log->manage( Graphics->getLogger() );
        // Log->manage( Sounds->getLogger() );

        }

    ~ WorldModule ( );

    Modes getMode ( );
    void setMode ( Modes Mode );

    bool hasVideoChanged ( );
    sf::VideoMode getVideoMode ( );
    uint32_t getVideoStyle ( );
    sf::ContextSettings getVideoContext ( );

    void update ( );
    void update ( sf::Event &Event );
    void render ( sf::RenderWindow &Window );

private:

    bool config ( Script &Config, Script * GraphicsConfig, Script * SoundsConfig );
    void init ( );

private:

    Script Config;

    LoggerManager * Log;
    GraphicsModule * Graphics;
    // SoundsModule * Sounds;

    sf::Thread * GraphicsThread;
    // sf::Thread * SoundsThread;

    Modes Mode;
    bool Debugging;
    int8_t InitState;
    bool VideoChanged;

    };

#endif