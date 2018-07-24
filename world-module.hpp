#ifndef GRAVITY_MADNESS_WORLD_MODULE
#define GRAVITY_MADNESS_WORLD_MODULE

#include "debug-module.hpp"
#include "game-module.hpp"
#include "gameplay-settings.hpp"
#include "graphics-module.hpp"
#include "logger-manager.hpp"
#include "main-menu.hpp"
#include "message.hpp"
#include "pause-menu.hpp"
#include "score-board.hpp"
#include "script.hpp"

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

    explicit WorldModule ( Script * Config ) : Logger ( ) {

        this->Config = Config;
        SpaceshipsConfig = nullptr;
        ControllersConfig = "";

        Log = nullptr;
        Graphics = nullptr;
        // Audio = nullptr;
        Game = nullptr;
        Debug = nullptr;
        Gameplay = nullptr;
        MyMainMenu = nullptr;
        MyPauseMenu = nullptr;
        MyScoreBoard = nullptr;
        MyMessage = nullptr;

        GraphicsThread = nullptr;
        // AudioThread = nullptr;

        Script * GraphicsConfig = nullptr;
        Script * AudioConfig = nullptr;

        Mode = Modes::InitMode;

        if ( !config( &GraphicsConfig, &AudioConfig ) ) {

            Mode = Modes::IdleMode;

            return; }

        Log = new LoggerManager ( LogPath );
        Graphics = new GraphicsModule ( GraphicsConfig, &InitState );
        // Audio = new AudioModule ( );

        InitState = 0;
        VideoChanged = false;

        Log->manage( getLogger() );
        Log->manage( Graphics->getLogger() );
        // Log->manage( Audio->getLogger() );

        Graphics->setWindowSize( InitWindowWidth, InitWindowHeight );
        InitFullScreen ? Graphics->enableFullScreen() : Graphics->disableFullScreen();
        Graphics->setAntialiasingLevel( InitAntialiasing );

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
    void init ( sf::RenderWindow * Window = nullptr );

    void saveSettings ( );

private:

    Script * Config;
    Script * SpaceshipsConfig;
    std::string ControllersConfig;

    LoggerManager * Log;
    GraphicsModule * Graphics;
    // AudioModule * Audio;
    GameModule * Game;
    DebugModule * Debug;
    GameplaySettings * Gameplay;
    MainMenu * MyMainMenu;
    PauseMenu * MyPauseMenu;
    ScoreBoard * MyScoreBoard;
    Message * MyMessage;

    sf::Thread * GraphicsThread;
    // sf::Thread * AudioThread;

    Modes Mode;
    int8_t InitState;
    bool VideoChanged;

    std::string LogPath;
    unsigned int InitWindowWidth;
    unsigned int InitWindowHeight;
    unsigned int InitAntialiasing;
    bool InitFullScreen;
    unsigned int HighScore;
    bool Debugging;

    };

#endif