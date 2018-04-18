#include "world-module.hpp"

WorldModule::~WorldModule ( ) {

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

        case Idle: {

            return; }

        case Init: {

            init();

            break; }

        // ...

        default: {

            return; } }

    Log->update();
    //std::cout << Mode << " " << Modes::RunTimeError << " " << Log->wasErrorLogged() << std::endl;
    if ( Mode > Modes::RunTimeError && Log->wasErrorLogged() ) {

        setMode( Modes::RunTimeError ); } }

void WorldModule::update ( sf::Event &Event ) {

    // ...

    }

void WorldModule::render ( sf::RenderWindow &Window ) {

    switch ( Mode ) {

        case Idle: {

            return; }

        case Init: {

            // ...

            break; }

            // ...

        default: {

            return; } }

    }

bool WorldModule::config ( Script &Config, Script * GraphicsConfig, Script * SoundsConfig ) {

    // TODO SOUNDS MODULE

    }

void WorldModule::init ( ) {

    if ( InitState == 0 ) {

        std::cout << "Init start" << std::endl; // TODO TEMP

        GraphicsThread = new sf::Thread ( &GraphicsModule::init, Graphics );
        // SoundsThread = new sf::Thread ( &GraphicsModule::init, Sounds );

        GraphicsThread->launch();
        // SoundThread->launch();

        InitState++; }

    else if ( InitState < 2 ) { // 3 with sounds module

        // std::cout << "Loading screen" << std::endl; // TODO TEMP

        Graphics->initContext();

        // TODO UPDATE LOADING SCREEN

        }

    else {

        std::cout << "Init stop" << std::endl; // TODO TEMP

        delete GraphicsThread;
        //delete SoundsThread;

        Graphics->getTexture( "test" );
        Graphics->getFont( "test" );

        Log->update();

        if ( Log->wasErrorLogged() ) {

            setMode( Modes::InitTimeError ); }

        else if ( Log->wasWarningLogged() ) {

            setMode( Modes::InitTimeWarning ); }

        else if ( Debugging ) {

            setMode( Modes::Debug ); }

        else {

            setMode( Modes::MainMenu ); } } }