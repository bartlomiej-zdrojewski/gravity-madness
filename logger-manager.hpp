#ifndef GRAVITY_MADNESS_LOGGER_MANAGER
#define GRAVITY_MADNESS_LOGGER_MANAGER

#include "logger.hpp"

class LoggerManager {

public:

    LoggerManager ( std::string FilePath );

    void manage ( Logger * Log );

    bool wasErrorLogged ( );
    bool wasWarningLogged ( );

    void update ( );

private:

    std::vector <Logger*> Loggers;

    };

#endif
