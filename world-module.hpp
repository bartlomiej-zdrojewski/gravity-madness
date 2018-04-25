#ifndef GRAVITY_MADNESS_WORLD_MODULE
#define GRAVITY_MADNESS_WORLD_MODULE

#include "script.hpp"
#include "logger-manager.hpp"
#include "graphics-module.hpp"
#include "game-module.hpp"

class WorldModule : public Logger {

public:

    enum Modes {

        IdleMode,
        InitMode,
        InitTimeWarningMode,
        InitTimeErrorMode,
        RunTimeErrorMode,
        MainMenuMode,
        GameMode,
        PauseMenuMode,
        ScoreBoardMode,
        DebugMode

        };

    explicit WorldModule ( Script Config ) : Config ( Config ), Logger ( ) {

        Mode = Modes::InitMode;

        Log = nullptr;
        Graphics = nullptr;
        // Audio = nullptr;
        Game = nullptr;

        Script * GraphicsConfig = nullptr;
        Script * AudioConfig = nullptr;

        if ( !config( &GraphicsConfig, &AudioConfig ) ) {

            Mode = Modes::IdleMode;

            return; }

        Log = new LoggerManager ( "log.txt" );
        Graphics = new GraphicsModule ( GraphicsConfig, &InitState );
        // Audio = new AudioModule ( );

        InitState = 0;
        VideoChanged = false;

        Log->manage( getLogger() );
        Log->manage( Graphics->getLogger() );
        // Log->manage( Audio->getLogger() );

        Graphics->setWindowSize( InitWindowWidth, InitWindowHeight );
        InitFullScreen ? Graphics->enableFullScreen() : Graphics->disableFullScreen();
        Graphics->setAntyaliasingLevel( InitAntyaliasing );

        // Audio options

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

    bool config ( Script ** GraphicsConfig, Script ** AudioConfig );
    void init ( );

private:

    Script Config;

    LoggerManager * Log;
    GraphicsModule * Graphics;
    // AudioModule * Audio;
    GameModule * Game;

    sf::Thread * GraphicsThread;
    // sf::Thread * AudioThread;

    Modes Mode;
    int8_t InitState;
    bool VideoChanged;

    unsigned int InitWindowWidth;
    unsigned int InitWindowHeight;
    unsigned int InitAntyaliasing;
    bool InitFullScreen;
    unsigned int HighScore;
    bool Debugging;

    };

#endif