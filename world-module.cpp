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
    Context.antialiasingLevel = Graphics->getAntyaliasingLevel();

    return Context; }

void WorldModule::update ( ) {

    switch ( Mode ) {

        case IdleMode: {

            return; }

        case InitMode: {

            init();

            break; }

        case InitTimeWarningMode: {

            // TODO

            if ( Debugging ) {

                Debug = new DebugModule ( Graphics, Game );
                Log->manage( Debug->getLogger() );

                setMode( Modes::DebugMode ); }

            else {

                MyMainMenu = new MainMenu ( Graphics, Gameplay );
                MyPauseMenu = new PauseMenu ( Graphics );
                MyScoreBoard = new ScoreBoard ( Graphics );

                setMode( Modes::MainMenuMode ); }

            break; }

        case InitTimeErrorMode: {

            // TODO

            break; }

        case RunTimeErrorMode: {

            // TODO

            break; }

        case MainMenuMode: {

            MyMainMenu->update();

            // TODO DELETE
            setMode( Modes::GameMode );

            // TODO

            break; }

        case GameMode: {

            Game->update();

            if ( Game->onPause() ) {

                setMode( Modes::PauseMenuMode ); }

            else if ( Game->onEndingCondition() ) {

                setMode( Modes::ScoreBoardMode ); }

            break; }

        case PauseMenuMode: {

            MyPauseMenu->update();

            // TODO

            break; }

        case ScoreBoardMode: {

            MyScoreBoard->update();

            // TODO

            break; }

        case DebugMode: {

            // TODO

            break; }

        default: {

            return; } }

    Log->update();

    if ( Mode > Modes::RunTimeErrorMode && Log->wasErrorLogged() ) {

        setMode( Modes::RunTimeErrorMode ); } }

void WorldModule::update ( sf::Event &Event ) {

    switch ( Mode ) {

        case IdleMode: {

            return; }

        case InitMode: {

            return; }

        case InitTimeWarningMode: {

            // TODO

            break; }

        case InitTimeErrorMode: {

            // TODO

            break; }

        case RunTimeErrorMode: {

            // TODO

            break; }

        case MainMenuMode: {

            MyMainMenu->update( Event );

            // TODO

            break; }

        case GameMode: {

            Game->update( Event );

            if ( Game->onPause() ) {

                setMode( Modes::PauseMenuMode ); }

            else if ( Game->onEndingCondition() ) {

                setMode( Modes::ScoreBoardMode ); }

            break; }

        case PauseMenuMode: {

            MyPauseMenu->update( Event );

            // TODO

            break; }

        case ScoreBoardMode: {

            MyScoreBoard->update( Event );

            // TODO

            break; }

        case DebugMode: {

            // TODO

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

            // TODO

            break; }

        case InitTimeErrorMode: {

            // TODO

            break; }

        case RunTimeErrorMode: {

            // TODO

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

            // TODO

            break; }

        default: {

            return; } }

    }

bool WorldModule::config ( Script ** GraphicsConfig, Script ** AudioConfig ) {

    LogPath = "log.txt";
    InitWindowWidth = 0;
    InitWindowHeight = 0;
    InitAntyaliasing = 0;
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

        else if ( std::string( Setting.name() ) == "Antyaliasing" ) {

            InitAntyaliasing = (unsigned int) Config->getIntegerValue( Setting ); }

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

            setMode( Modes::InitTimeErrorMode ); }

        else {

            Game = new GameModule ( Graphics );
            Gameplay = new GameplaySettings ( );

            Log->manage( Gameplay->getLogger() );
            Gameplay->loadSpaceshipPrototypes( SpaceshipsConfig );
            Log->update();

            if ( Log->wasWarningLogged() ) {

                MyMessage = new Message ( Graphics );

                setMode( Modes::InitTimeWarningMode ); }

            else if ( Debugging ) {

                MyMessage = new Message ( Graphics );
                Debug = new DebugModule ( Graphics, Game );
                Log->manage( Debug->getLogger() );

                setMode( Modes::DebugMode ); }

            else {

                MyMainMenu = new MainMenu ( Graphics, Gameplay );
                MyPauseMenu = new PauseMenu ( Graphics );
                MyScoreBoard = new ScoreBoard ( Graphics );
                MyMessage = new Message ( Graphics );

                setMode( Modes::MainMenuMode ); } } } }
