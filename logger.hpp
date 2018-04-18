#ifndef GRAVITY_MADNESS_LOGGER
#define GRAVITY_MADNESS_LOGGER

#include <string>
#include <queue>

class Logger {

public:

    Logger * getLogger ( );

    bool wasErrorLogged ( );
    bool wasWarningLogged ( );

    void logError ( std::string Message );
    void logWarning ( std::string Message );

    std::string getError ( );
    std::string getWarning ( );

private:

    std::queue <std::string> Errors;
    std::queue <std::string> Warnings;

    };

#endif