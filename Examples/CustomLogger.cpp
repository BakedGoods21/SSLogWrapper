//C++ Includes
#include <iostream>
#include <fstream>
#include <stdexcept>

//Logger Includes
#include "CustomLogger.h"

std::ofstream plogOtf;

void CustomLogger::setGlobalLogLevel(const SSLogger::logLevel& newLogLevel)
{
    mGlobalLevel = newLogLevel;
}

void CustomLogger::setLogFile(const std::string& logFile)
{
    if (plogOtf.is_open())
    {
        plogOtf.close();
    }

    plogOtf.open(logFile, std::ios::app);
}

void CustomLogger::trace(const std::string& message,
                       const char* func/* = __func__,*/,
                       const char* file/* = __FILE__*/,
                       int line/* = __LINE__*/)
{
    if (plogOtf.is_open())
    {
        plogOtf << "Custom TRACE: " << file << ":" << line << " in " << func << " --> " <<  message << "\n";
    }
    std::cout << "Custom TRACE: " << file << ":" << line << " in " << func << " --> " <<  message << "\n";
}

void CustomLogger::debug(const std::string& message,
                       const char* func/* = __func__,*/,
                       const char* file/* = __FILE__*/,
                       int line/* = __LINE__*/)
{
    if (mGlobalLevel == SSLogger::logLevel::pDEBUG)
    {
        if (plogOtf.is_open())
        {
            plogOtf << "Custom DEBUG: " << file << ":" << line << " in " << func << " --> " <<  message << "\n";
        }
        std::cout << "Custom DEBUG: " << file << ":" << line << " in " << func << " --> " <<  message << "\n";
    }
}

void CustomLogger::info(const std::string& message)
{
    if (plogOtf.is_open())
    {
        plogOtf << "Custom INFO: " << message << "\n";
    }
    std::cout << "Custom INFO: " << message << "\n";
}

void CustomLogger::warn(const std::string& message)
{
    if (plogOtf.is_open())
    {
        plogOtf << "Custom WARNING: " << message << "\n";
    }
    std::cerr << "Custom WARNING: " << message << "\n";
}

void CustomLogger::error(const std::string& message)
{
    if (plogOtf.is_open())
    {
        plogOtf << "Custom ERROR: " << message << "\n";
    }
    std::cerr << "Custom ERROR: " << message << "\n";
}

void CustomLogger::fatal(const std::string& message)
{
    if (plogOtf.is_open())
    {
        plogOtf << "Custom FATAL: " << message << "\n";
    }
    throw std::runtime_error("Custom FETAL: " + message);
}

