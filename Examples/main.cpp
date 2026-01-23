#include <stdexcept>
#include <cstdlib>
#include <memory>

#include "SSLogWrapper/ILogger.h"

int main()
{
    std::string logPath = "log.log";
    SSLogger::PLOG()->info("Setting output log file: " + logPath);
    SSLogger::setLogFile(logPath);

    SSLogger::PLOG()->info("test info");
    SSLogger::PINFO("test info static");
    (*SSLogger::PLOG())(SSLogger::logLevel::pINFO) << "Another way to do it...\n";
    (*SSLogger::PLOG()) << "Yet another way to do it...\n";

    SSLogger::PDEBUG("Test debug");
#ifdef APP_DEBUG
    SSLogger::setLevel(SSLogger::logLevel::pDEBUG);
#endif
    SSLogger::PDEBUG("Test debug1");

    return EXIT_SUCCESS;
}

