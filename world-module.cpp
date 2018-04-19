#include "world-module.hpp"

WorldModule::~WorldModule ( ) {

    delete Game;
    delete Log;
    delete Graphics;
    // delete Sounds;

    }

WorldModule::Modes WorldModule::getMode ( ) {

    return Mode; }

void WorldModule::setMode ( Modes Mode ) {

    this->Mode = Mode; }

bool WorldModule::hasVideoChanged ( ) {

    if ( VideoChanged ) {

        VideoChanged = false;

        return true;}

    return false; }

sf::VideoMode WorldModule::getVideoMode ( ) {

    return { Graphics->getWindowWidth(), Graphics->getWindowHeight() }; }

uint32_t WorldModule::getVideoStyle ( ) {

    if ( Graphics->isFullScreenEnabled() ) {

        return sf::Style::Fullscreen; }

    return sf::Style::Titlebar | sf::Style::Close; }

sf::ContextSettings WorldModule::getVideoContext ( ) { // TODO Antyaliasing

    return sf::ContextSettings ( ); }

void WorldModule::update ( ) {

    switch ( Mode ) {

        case IdleMode: {

            return; }

        case InitMode: {

            init();

            break; }

        case MainMenuMode: {

            setMode( Modes::GameMode );
            // ...

            break; }

        case GameMode: {

            Game->update();

            break; }

        // ...

        default: {

            return; } }

    Log->update();

    if ( Mode > Modes::RunTimeErrorMode && Log->wasErrorLogged() ) {

        setMode( Modes::RunTimeErrorMode ); } }

void WorldModule::update ( sf::Event &Event ) {

    switch ( Mode ) {

        // ...

        case GameMode: {

            Game->update( Event );

            break; }

        // ...

        default: {

            return; } }

    }

void WorldModule::render ( sf::RenderWindow &Window ) {

    switch ( Mode ) {

        case IdleMode: {

            return; }

        // ...

        case GameMode: {

            Game->render( Window );

            break; }

            // ...

        default: {

            return; } }

    }

bool WorldModule::config ( Script ** GraphicsConfig, Script ** SoundsConfig ) {

    InitWindowWidth = 0;
    InitWindowHeight = 0;
    InitAntyaliasing = 0;
    InitFullScreen = false;
    HighScore = 0;

    pugi::xml_node * Root = Config.getRoot();

    if ( !Root ) {

        return false; }

    auto SettingsNode = Config.getChildren( *Root );

    if ( SettingsNode.empty() ) {

        return false; }

    auto SettingNodes = Config.getChildren( SettingsNode[0] );

    for ( auto Setting : SettingNodes ) {

        if ( std::string( Setting.name() ) == "GraphicsSettings" ) {

            delete *GraphicsConfig;
            *GraphicsConfig = new Script ( Config.getTextValue( Setting ) ); }

        else if ( std::string( Setting.name() ) == "SoundsSettings" ) {

            // delete SoundsConfig;
            // SoundsConfig = new Script ( Config.getTextValue( Setting ) );

            }

        else if ( std::string( Setting.name() ) == "WindowWidth" ) {

            InitWindowWidth = (unsigned int) Config.getIntegerValue( Setting ); }

        else if ( std::string( Setting.name() ) == "WindowHeight" ) {

            InitWindowHeight = (unsigned int) Config.getIntegerValue( Setting ); }

        else if ( std::string( Setting.name() ) == "FullScreen" ) {

            InitFullScreen = Config.getBooleanValue( Setting ); }

        else if ( std::string( Setting.name() ) == "Antyaliasing" ) {

            InitAntyaliasing = (unsigned int) Config.getIntegerValue( Setting ); }

        else if ( std::string( Setting.name() ) == "HighScore" ) {

            HighScore = (unsigned int) Config.getIntegerValue( Setting ); }

        else if ( std::string( Setting.name() ) == "Debug" ) {

            Debugging = Config.getBooleanValue( Setting ); } }

    return !( InitWindowWidth == 0 || InitWindowHeight == 0 ); }

void WorldModule::init ( ) {

    if ( InitState == 0 ) {

        GraphicsThread = new sf::Thread ( &GraphicsModule::init, Graphics );
        // SoundsThread = new sf::Thread ( &GraphicsModule::init, Sounds );

        GraphicsThread->launch();
        // SoundThread->launch();

        InitState++; }

    else if ( InitState < 2 ) { // 3 with sounds module

        Graphics->initContext();

        // TODO UPDATE LOADING SCREEN

        }

    else {

        delete GraphicsThread;
        //delete SoundsThread;

        Log->update();

        if ( Log->wasErrorLogged() ) {

            setMode( Modes::InitTimeErrorMode ); }

        else if ( Log->wasWarningLogged() ) {

            setMode( Modes::InitTimeWarningMode ); }

        else if ( Debugging ) {

            setMode( Modes::DebugMode ); }

        else {

            Game = new GameModule ( Graphics );

            setMode( Modes::MainMenuMode ); } } }