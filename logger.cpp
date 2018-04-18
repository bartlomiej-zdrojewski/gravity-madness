#include "logger.hpp"

Logger * Logger::getLogger ( ) {

    return this; }

bool Logger::wasErrorLogged ( ) {

    return !Errors.empty(); }

bool Logger::wasWarningLogged ( ) {

    return !Warnings.empty(); }

void Logger::logError ( std::string Message ) {

    Errors.push( Message ); }

void Logger::logWarning ( std::string Message ) {

    Warnings.push( Message ); }

std::string Logger::getError ( ) {

    if ( !wasErrorLogged() ) {

        return ""; }

    std::string Message = Errors.front(); // It's okay
    Errors.pop();

    return Message; }

std::string Logger::getWarning ( ) {

    if ( !wasWarningLogged() ) {

        return ""; }

    std::string Message = Warnings.front(); // It's okay
    Warnings.pop();

    return Message; }