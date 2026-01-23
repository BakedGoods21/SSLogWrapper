//C++ Includes
#include <iostream>
#include <fstream>
#include <stdexcept>

//Logger Includes
#include "coutLogger/CoutLogger.h"

namespace SSLogger
{
    std::ofstream plogOtf;

    void CoutLogger::setGlobalLogLevel(const logLevel& newLogLevel)
    {
        mGlobalLevel = newLogLevel;
    }

    void CoutLogger::setLogFile(const std::string& logFile)
    {
        if (plogOtf.is_open())
        {
            plogOtf.close();
        }

        plogOtf.open(logFile, std::ios::app);
    }
    
    void CoutLogger::trace(const std::string& message,
                           const char* func/* = __func__,*/,
                           const char* file/* = __FILE__*/,
                           int line/* = __LINE__*/)
    {
        if (plogOtf.is_open())
        {
            plogOtf << "TRACE: " << file << ":" << line << " in " << func << " --> " <<  message << "\n";
        }
        std::cout << "TRACE: " << file << ":" << line << " in " << func << " --> " <<  message << "\n";
    }
    
    void CoutLogger::debug(const std::string& message,
                           const char* func/* = __func__,*/,
                           const char* file/* = __FILE__*/,
                           int line/* = __LINE__*/)
    {
        if (mGlobalLevel == logLevel::pDEBUG)
        {
            if (plogOtf.is_open())
            {
                plogOtf << "DEBUG: " << file << ":" << line << " in " << func << " --> " <<  message << "\n";
            }
            std::cout << "DEBUG: " << file << ":" << line << " in " << func << " --> " <<  message << "\n";
        }
    }
    
    void CoutLogger::info(const std::string& message)
    {
        if (plogOtf.is_open())
        {
            plogOtf << "INFO: " << message << "\n";
        }
        std::cout << "INFO: " << message << "\n";
    }
    
    void CoutLogger::warn(const std::string& message)
    {
        if (plogOtf.is_open())
        {
            plogOtf << "WARNING: " << message << "\n";
        }
        std::cerr << "WARNING: " << message << "\n";
    }
    
    void CoutLogger::error(const std::string& message)
    {
        if (plogOtf.is_open())
        {
            plogOtf << "ERROR: " << message << "\n";
        }
        std::cerr << "ERROR: " << message << "\n";
    }

    void CoutLogger::fatal(const std::string& message)
    {
        if (plogOtf.is_open())
        {
            plogOtf << "FATAL: " << message << "\n";
        }
        throw std::runtime_error("FETAL: " + message);
    }
}
