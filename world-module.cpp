#include "world-module.hpp"

WorldModule::~WorldModule ( ) {

    delete MyMessage;
    delete MyScoreBoard;
    delete MyMainMenu;
    delete MyPauseMenu;
    delete Gameplay;
    delete Debug;
    delete Game;
    delete Graphics;
    // delete Audio;
    delete Log;

    }

WorldModule::Modes WorldModule::getMode ( ) {

    return Mode; }

void WorldModule::setMode ( Modes Mode ) {

    this->Mode = Mode; }

bool WorldModule::hasVideoChanged ( ) {

    if ( VideoChanged ) {

        VideoChanged = false;

        return true; }

    return false; }

sf::VideoMode WorldModule::getVideoMode ( ) {

    return { Graphics->getWindowWidth(), Graphics->getWindowHeight() }; }

uint32_t WorldModule::getVideoStyle ( ) {

    if ( Graphics->isFullScreenEnabled() ) {

        return sf::Style::Fullscreen; }

    return sf::Style::Titlebar | sf::Style::Close; }

sf::ContextSettings WorldModule::getVideoContext ( ) {

    sf::ContextSettings Context;
    Context.antialiasingLevel = Graphics->getAntialiasingLevel();

    return Context; }

void WorldModule::update ( ) {

    switch ( Mode ) {

        case IdleMode: {

            return; }

        case InitMode: {

            init();

            break; }

        case InitTimeWarningMode: {

            MyMessage->update();

            if ( MyMessage->onClose() ) {

                MyMessage->setType( Message::Types::None );

                if ( Debugging ) {

                    Debug = new DebugModule ( Graphics, Game );
                    Log->manage( Debug->getLogger() );

                    setMode( Modes::DebugMode ); }

                else {

                    MyMainMenu = new MainMenu ( Graphics, Gameplay );
                    MyPauseMenu = new PauseMenu ( Graphics );
                    MyScoreBoard = new ScoreBoard ( Graphics, Gameplay );

                    setMode( Modes::MainMenuMode ); } }

            break; }

        case InitTimeErrorMode: {

            MyMessage->update();

            if ( MyMessage->onClose() ) {

                setMode( Modes::IdleMode ); }

            break; }

        case RunTimeErrorMode: {

            MyMessage->update();

            if ( MyMessage->onClose() ) {

                setMode( Modes::IdleMode ); }

            break; }

        case MainMenuMode: {

            MyMainMenu->update();

            if ( MyMainMenu->onLaunch() ) {

                Game->setGameplay( Gameplay );

                setMode( Modes::GameMode ); }

            else if ( MyMainMenu->onTerminate() ) {

                setMode( Modes::IdleMode ); }

            if ( MyMainMenu->onVideoChanged() ) {

                VideoChanged = true; }

            if ( MyMainMenu->onSettingsChanged() ) {

                // TODO UPDATE CONFIG

                }

            break; }

        case GameMode: {

            Game->update();

            if ( Game->onPause() ) {

                setMode( Modes::PauseMenuMode ); }

            else if ( Game->onTerminate() ) {

                setMode( Modes::ScoreBoardMode ); }

            break; }

        case PauseMenuMode: {

            MyPauseMenu->update();

            if ( MyPauseMenu->onClose() ) {

                setMode( Modes::GameMode ); }

            else if ( MyPauseMenu->onTerminate() ) {

                Game->terminate();

                setMode( Modes::GameMode ); }

            break; }

        case ScoreBoardMode: {

            MyScoreBoard->update();

            if ( MyScoreBoard->onClose() ) {

                MyMainMenu->reset();

                setMode( Modes::MainMenuMode ); }

            break; }

        case DebugMode: {

            Debug->update();

            if ( Debug->onTerminate() ) {

                setMode( Modes::IdleMode ); }

            break; }

        default: {

            return; } }

    Log->update();

    if ( Mode > Modes::RunTimeErrorMode && Log->wasErrorLogged() ) {

        MyMessage->setType( Message::Types::RunTimeError );

        setMode( Modes::RunTimeErrorMode ); } }

void WorldModule::update ( sf::Event &Event ) {

    switch ( Mode ) {

        case IdleMode: {

            return; }

        case InitMode: {

            return; }

        case InitTimeWarningMode: {

            MyMessage->update( Event );

            if ( MyMessage->onClose() ) {

                MyMessage->setType( Message::Types::None );

                if ( Debugging ) {

                    Debug = new DebugModule ( Graphics, Game );
                    Log->manage( Debug->getLogger() );

                    setMode( Modes::DebugMode ); }

                else {

                    MyMainMenu = new MainMenu ( Graphics, Gameplay );
                    MyPauseMenu = new PauseMenu ( Graphics );
                    MyScoreBoard = new ScoreBoard ( Graphics, Gameplay );

                    setMode( Modes::MainMenuMode ); } }

            break; }

        case InitTimeErrorMode: {

            MyMessage->update( Event );

            if ( MyMessage->onClose() ) {

                setMode( Modes::IdleMode ); }

            break; }

        case RunTimeErrorMode: {

            MyMessage->update( Event );

            if ( MyMessage->onClose() ) {

                setMode( Modes::IdleMode ); }

            break; }

        case MainMenuMode: {

            MyMainMenu->update( Event );

            if ( MyMainMenu->onLaunch() ) {

                Game->setGameplay( Gameplay );

                setMode( Modes::GameMode ); }

            else if ( MyMainMenu->onTerminate() ) {

                setMode( Modes::IdleMode ); }

            if ( MyMainMenu->onVideoChanged() ) {

                VideoChanged = true; }

            break; }

        case GameMode: {

            Game->update( Event );

            if ( Game->onPause() ) {

                setMode( Modes::PauseMenuMode ); }

            else if ( Game->onTerminate() ) {

                setMode( Modes::ScoreBoardMode ); }

            break; }

        case PauseMenuMode: {

            MyPauseMenu->update( Event );

            if ( MyPauseMenu->onClose() ) {

                setMode( Modes::GameMode ); }

            else if ( MyPauseMenu->onTerminate() ) {

                Game->terminate();

                setMode( Modes::GameMode ); }

            break; }

        case ScoreBoardMode: {

            MyScoreBoard->update( Event );

            if ( MyScoreBoard->onClose() ) {

                MyMainMenu->reset();

                setMode( Modes::MainMenuMode ); }

            break; }

        case DebugMode: {

            Debug->update( Event );

            if ( Debug->onTerminate() ) {

                setMode( Modes::IdleMode ); }

            break; }

        default: {

            return; } } }

void WorldModule::render ( sf::RenderWindow &Window ) {

    switch ( Mode ) {

        case IdleMode: {

            return; }

        case InitMode: {

            init( &Window );

            return; }

        case InitTimeWarningMode: {

            MyMessage->render( Window );

            break; }

        case InitTimeErrorMode: {

            MyMessage->render( Window );

            break; }

        case RunTimeErrorMode: {

            MyMessage->render( Window );

            break; }

        case MainMenuMode: {

            MyMainMenu->render( Window );

            break; }

        case GameMode: {

            Game->render( Window );

            break; }

        case PauseMenuMode: {

            Game->render( Window );
            MyPauseMenu->render( Window );

            break; }

        case ScoreBoardMode: {

            MyScoreBoard->render( Window );

            break; }

        case DebugMode: {

            Debug->render( Window );

            break; }

        default: {

            return; } } }

bool WorldModule::config ( Script ** GraphicsConfig, Script ** AudioConfig ) {

    LogPath = "log.txt";
    InitWindowWidth = 0;
    InitWindowHeight = 0;
    InitAntialiasing = 0;
    InitFullScreen = false;
    HighScore = 0;
    Debugging = false;

    pugi::xml_node * Root = Config->getRoot();

    if ( !Root ) {

        return false; }

    auto SettingsNode = Config->getChildren( *Root );

    if ( SettingsNode.empty() ) {

        return false; }

    auto SettingNodes = Config->getChildren( SettingsNode[0] );

    for ( auto Setting : SettingNodes ) {

        if ( std::string( Setting.name() ) == "GraphicsSettings" ) {

            delete *GraphicsConfig;
            *GraphicsConfig = new Script ( Config->getTextValue( Setting ) ); }

        else if ( std::string( Setting.name() ) == "AudioSettings" ) {

            // delete AudioConfig;
            // AudioConfig = new Script ( Config.getTextValue( Setting ) );

            }

        else if ( std::string( Setting.name() ) == "SpaceshipsSettings" ) {

            delete SpaceshipsConfig;
            SpaceshipsConfig = new Script ( Config->getTextValue( Setting ) ); }

        else if ( std::string( Setting.name() ) == "Log" ) {

            LogPath = Config->getTextValue( Setting ); }

        else if ( std::string( Setting.name() ) == "WindowWidth" ) {

            InitWindowWidth = (unsigned int) Config->getIntegerValue( Setting ); }

        else if ( std::string( Setting.name() ) == "WindowHeight" ) {

            InitWindowHeight = (unsigned int) Config->getIntegerValue( Setting ); }

        else if ( std::string( Setting.name() ) == "FullScreen" ) {

            InitFullScreen = Config->getBooleanValue( Setting ); }

        else if ( std::string( Setting.name() ) == "Antialiasing" ) {

            InitAntialiasing = (unsigned int) Config->getIntegerValue( Setting ); }

        else if ( std::string( Setting.name() ) == "HighScore" ) {

            HighScore = (unsigned int) Config->getIntegerValue( Setting ); }

        else if ( std::string( Setting.name() ) == "Debug" ) {

            Debugging = Config->getBooleanValue( Setting ); } }

    return !( InitWindowWidth == 0 || InitWindowHeight == 0 ); }

void WorldModule::init ( sf::RenderWindow * Window ) {

    if ( InitState == 0 ) {

        GraphicsThread = new sf::Thread ( &GraphicsModule::init, Graphics );
        // AudioThread = new sf::Thread ( &GraphicsModule::init, Audio );

        GraphicsThread->launch();
        // SoundThread->launch();

        InitState++; }

    else if ( InitState < 2 ) { // TODO 3 with sounds module

        Graphics->initContext();

        if ( Window ) {

            // TODO UPDATE LOADING SCREEN

            } }

    else {

        delete GraphicsThread;
        //delete AudioThread;

        Log->update();

        if ( Log->wasErrorLogged() ) {

            MyMessage = new Message ( Graphics );
            MyMessage->setType( Message::Types::InitTimeError );

            setMode( Modes::InitTimeErrorMode ); }

        else {

            Game = new GameModule ( Graphics );
            Gameplay = new GameplaySettings ( );

            Log->manage( Gameplay->getLogger() );
            Gameplay->loadSpaceshipPrototypes( SpaceshipsConfig );
            Log->update();

            if ( Log->wasWarningLogged() ) {

                MyMessage = new Message ( Graphics );
                MyMessage->setType( Message::Types::InitTimeWarning );

                setMode( Modes::InitTimeWarningMode ); }

            else if ( Debugging ) {

                MyMessage = new Message ( Graphics );
                Debug = new DebugModule ( Graphics, Game );
                Log->manage( Debug->getLogger() );

                setMode( Modes::DebugMode ); }

            else {

                MyMainMenu = new MainMenu ( Graphics, Gameplay );
                MyPauseMenu = new PauseMenu ( Graphics );
                MyScoreBoard = new ScoreBoard ( Graphics, Gameplay );
                MyMessage = new Message ( Graphics );

                setMode( Modes::MainMenuMode ); } } } }
