#include "logger-manager.hpp"

LoggerManager::LoggerManager ( std::string FilePath ) {

    ErrorLogged = false;
    WarningLogged = false;

    Output = new std::fstream;
    Output->open( FilePath, std::ios::app );

    if ( Output->is_open() ) {

        *Output << "[" << time( nullptr ) << "] " << "Opening log" << std::endl; }

    else {

        delete Output;
        Output = nullptr; } }

LoggerManager::~LoggerManager ( ) {

    if ( Output ) {

        *Output << "[" << time( nullptr ) << "] " << "Closing log" << std::endl; }

    delete Output; }

void LoggerManager::manage ( Logger * Log ) {

    Loggers.push_back( Log ); }

bool LoggerManager::wasErrorLogged ( ) {

    return ErrorLogged; }

bool LoggerManager::wasWarningLogged ( ) {

    return WarningLogged; }

void LoggerManager::update ( ) {

    for ( auto Log : Loggers ) {

        while ( Log->wasErrorLogged() ) {

            *Output << "[" << time( nullptr ) << "] " << Log->getError() << std::endl;

            ErrorLogged = true; }

        if ( Log->wasWarningLogged() ) {

            *Output << "[" << time( nullptr ) << "] " << Log->getWarning() << std::endl;

            WarningLogged = true; } } }
