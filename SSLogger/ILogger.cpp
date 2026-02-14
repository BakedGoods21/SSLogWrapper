//C++ Includes
#include <stdexcept>

//Logger Includes
#include "SSLogWrapper/ILogger.h"

#ifdef SPD_ENABLED
#include "spdlogWrapper/SpdLogWrapper.h"
#define LOGGER SpdLogger
#else
#include "coutLogger/CoutLogger.h"
#define LOGGER CoutLogger
#endif


namespace SSLogger
{
    
    static std::shared_ptr<ILogger> g_PLOG = std::make_shared<LOGGER>();
    std::shared_ptr<ILogger> PLOG()
    {
        assert(g_PLOG.get() && "g_PLOG not defined");
        return g_PLOG;
    }

    void _setPLogger(std::shared_ptr<ILogger> newLogger)
    {
        g_PLOG = std::move(newLogger);
    }

    void ILogger::setGlobalLogLevel(const logLevel& newLogLevel)
    {
        mGlobalLevel = newLogLevel;
    }

    void ILogger::log(const std::string& message)
    {
        switch(mManualLevel)
        {
            case logLevel::pTRACE:
                PTRACE(message);
                break;
            case logLevel::pDEBUG:
                PDEBUG(message);
                break;
            case logLevel::pINFO:
                PINFO(message);
                break;
            case logLevel::pWARN:
                PWARN(message);
                break;
            case logLevel::pERROR:
                PERROR(message);
                break;
            case logLevel::pFATAL:
                PFATAL(message);
                break;
        }
    }

    void setLogFile(const std::string& logFile)
    {
        assert(dynamic_cast<IFileLogger*>(g_PLOG.get()) && "g_PLOG is not of type IFileLogger, cannot set file");

        dynamic_cast<IFileLogger*>(g_PLOG.get())->setLogFile(logFile);
    }

    void setLevel(logLevel newGlobalLogLevel)
    {
        g_PLOG->setGlobalLogLevel(newGlobalLogLevel);
    }

// The following #define's are used so that the user can do PTRACE("Message") or PTRACE() and it'll print the file, function, and line number it was called from along with the optional massage 
#define PTRACE_0(_) s_trace("Trace", __func__, __FILE__, __LINE__)
#define PTRACE_1(msg) s_trace(msg, __func__, __FILE__, __LINE__)

#define GET_MACRO(_1,_2,NAME,...) NAME
#define PTRACE(...) GET_MACRO(__VA_ARGS__,PTRACE_1,PTRACE_0)(__VA_ARGS__)
    void s_trace(const std::string& message,
                      const char* func,
                      const char* file,
                      int line)
    {
        g_PLOG->trace(message, func, file, line);
    }

// The following #define is used so that the user can do PDEBUG("Message") and it'll print the file, function, and line number it was called from along with the debug massage 
#define PDEBUG(msg) s_debug(msg, __func__, __FILE__, __LINE__)
    void s_debug(const std::string& message,
                      const char* func,
                      const char* file,
                      int line)
    {
        g_PLOG->debug(message, func, file, line);
    }

// The following #define is used solely to match the PTRACE and PDEBUG statements
#define PINFO(msg) s_info(msg)
    void s_info(const std::string& message)
    {
        g_PLOG->info(message);
    }

// The following #define is used solely to match the PTRACE and PDEBUG statements
#define PWARN(msg) s_warn(msg)
    void s_warn(const std::string& message)
    {
        g_PLOG->warn(message);
    }

// The following #define is used solely to match the PTRACE and PDEBUG statements
#define PERROR(msg) s_error(msg)
    void s_error(const std::string& message)
    {
        g_PLOG->error(message);
    }

// The following #define is used solely to match the PTRACE and PDEBUG statements
#define PFATAL(msg) s_fatal(msg)
    void s_fatal(const std::string& message)
    {
        g_PLOG->fatal(message);
    }
}
