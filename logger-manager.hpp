#ifndef GRAVITY_MADNESS_LOGGER_MANAGER
#define GRAVITY_MADNESS_LOGGER_MANAGER

#include <ctime>
#include <fstream>

#include "logger.hpp"

class LoggerManager {

public:

    explicit LoggerManager ( std::string FilePath );
    ~ LoggerManager ( );

    void manage ( Logger * Log );

    bool wasErrorLogged ( );
    bool wasWarningLogged ( );

    void update ( );

private:

    bool ErrorLogged;
    bool WarningLogged;

    std::fstream * Output;
    std::vector <Logger*> Loggers;

    };

#endif
