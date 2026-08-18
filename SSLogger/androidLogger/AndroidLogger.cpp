//C++ Includes
#include <iostream>
#include <fstream>
#include <stdexcept>

#ifndef __ANDROID__
#warning "__ANDROID__ not set"
#endif

// Android Includes
#include <android/log.h>

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
        __android_log_print(ANDROID_LOG_WARN, "SSLogger", "No file implementation yet");
    }
    
    void CoutLogger::trace(const std::string& message,
                           const char* func/* = __func__,*/,
                           const char* file/* = __FILE__*/,
                           int line/* = __LINE__*/)
    {
        //if (plogOtf.is_open())
        //{
        //    plogOtf << "TRACE: " << file << ":" << line << " in " << func << " --> " <<  message << "\n";
        //}
        __android_log_print(ANDROID_LOG_VERBOSE, "SSLogger", "TRACE: %s:%i in %s --> %s \n", file, line, func, message.c_str());
    }
    
    void CoutLogger::debug(const std::string& message,
                           const char* func/* = __func__,*/,
                           const char* file/* = __FILE__*/,
                           int line/* = __LINE__*/)
    {
        if (mGlobalLevel == logLevel::pDEBUG)
        {
            //if (plogOtf.is_open())
            //{
            //    plogOtf << "DEBUG: " << file << ":" << line << " in " << func << " --> " <<  message << "\n";
            //}
            __android_log_print(ANDROID_LOG_DEBUG, "SSLogger", "DEBUG: %s:%i in %s --> %s\n", file, line, func, message.c_str());
        }
    }
    
    void CoutLogger::info(const std::string& message)
    {
        //if (plogOtf.is_open())
        //{
        //    plogOtf << "INFO: " << message << "\n";
        //}
        __android_log_print(ANDROID_LOG_INFO, "SSLogger", "INFO: %s\n", message.c_str());
    }
    
    void CoutLogger::warn(const std::string& message)
    {
        //if (plogOtf.is_open())
        //{
        //    plogOtf << "WARNING: " << message << "\n";
        //}
        __android_log_print(ANDROID_LOG_WARN, "SSLogger", "WARN: %s\n", message.c_str());
    }
    
    void CoutLogger::error(const std::string& message)
    {
        //if (plogOtf.is_open())
        //{
        //    plogOtf << "ERROR: " << message << "\n";
        //}
        __android_log_print(ANDROID_LOG_ERROR, "SSLogger", "ERROR: %s\n", message.c_str());
    }

    void CoutLogger::fatal(const std::string& message)
    {
        //if (plogOtf.is_open())
        //{
        //    __android_log_print(ANDROID_LOG_FATAL, "SSLogger", "ERROR: %s:%i in %s --> %s \n", file, line, func, message);
        //    plogOtf << "FATAL: " << message << "\n";
        //}
        throw std::runtime_error("FATAL: " + message);
    }
}
