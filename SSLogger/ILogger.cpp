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
    
    const std::unique_ptr<ILogger>& PLOG()
    {
        static std::unique_ptr<ILogger> g_PLOG = std::make_unique<LOGGER>();

        assert(g_PLOG && "g_PLOG not defined");
        return g_PLOG;
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
}
