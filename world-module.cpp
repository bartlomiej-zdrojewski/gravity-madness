#include "world-module.hpp"

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

    if ( Log->wasErrorLogged() ) {

        setMode( Modes::RunTimeError ); } }

void WorldModule::init ( ) {

    if ( InitState == 0 ) {

        std::cout << "Init start" << std::endl; // TODO TEMP

        sf::Thread GraphicsThread ( &GraphicsModule::init, Graphics );
        // sf::Thread SoundsThread ( &GraphicsModule::init, Sounds );

        GraphicsThread.launch();
        // SoundThread.launch();

        InitState++; }

    else if ( InitState < 2 ) {

        std::cout << "Loading screen" << std::endl; // TODO TEMP

        Graphics->initContext();

        // TODO UPDATE LOADING SCREEN

        }

    else {

        std::cout << "Init stop" << std::endl; // TODO TEMP

        Log->update();

        if ( Log->wasErrorLogged() ) {

            setMode( Modes::InitTimeError ); }

        else if ( Log->wasWarningLogged() ) {

            setMode( Modes::InitTimeWarning ); }

        else if ( Debugging ) {

            setMode( Modes::Debug ); }

        else {

            setMode( Modes::MainMenu ); } } }