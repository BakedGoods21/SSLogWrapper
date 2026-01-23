#pragma once

#include <memory>
#include <string>
#include <cassert>

namespace SSLogger
{
    enum class logLevel
    {
        pTRACE,
        pDEBUG,
        pINFO,
        pWARN,
        pERROR,
        pFATAL
    };


    class ILogger
    {
    public:
        ILogger() = default;
        virtual ~ILogger() = default;

        virtual void trace(const std::string& message, // Extremely detailed information, often about program flow or internals
                           const char* func/* = __func__*/,
                           const char* file/* = __FILE__*/,
                           int line/* = __LINE__*/) = 0;
        virtual void debug(const std::string& message,  // Debugging information useful during development (Disabled during release)
                           const char* func/* = __func__*/,
                           const char* file/* = __FILE__*/,
                           int line/* = __LINE__*/) = 0;
        virtual void info(const std::string& message)  = 0;   // General information about application progress
        virtual void warn(const std::string& message)  = 0;   // Something unexpected happened, but the program can continue
        virtual void error(const std::string& message) = 0;  // A serious issue occurred, but the program can still run (maybe shutting off a particular feature or button press)
        virtual void fatal(const std::string& message) = 0;  // Very severe error, often requiring immediate attention (application usually exits)

        virtual void setGlobalLogLevel(const logLevel& newLogLevel);

        ILogger& operator()(const logLevel& newLogLevel)
        {
            mManualLevel = newLogLevel;
            return *this;
        }

        ILogger& operator<<(const std::string& message)
        {
            log(message);
            return *this;
        }
    protected:
        logLevel mManualLevel = logLevel::pINFO;
        logLevel mGlobalLevel = logLevel::pINFO;

    private:
        void log(const std::string& message);
    };

    class IFileLogger : public ILogger
    {
    public:
        IFileLogger() = default;
        ~IFileLogger() = default;

        virtual void setLogFile(const std::string& logFile) = 0;
    };

    const std::unique_ptr<ILogger>& PLOG();

    template<typename T>
    static void setPLogger(T&& newLogger)
    {
        PLOG() = std::make_unique<T>(std::move(newLogger));
    }

    static void setLogFile(const std::string& logFile)
    {
        assert(dynamic_cast<IFileLogger*>(PLOG().get()) && "PLOG() is not of type IFileLogger, cannot set file");

        dynamic_cast<IFileLogger*>(PLOG().get())->setLogFile(logFile);
    }

    static void setLevel(logLevel newGlobalLogLevel)
    {
        PLOG()->setGlobalLogLevel(newGlobalLogLevel);
    }

// The following #define's are used so that the user can do PTRACE("Message") or PTRACE() and it'll print the file, function, and line number it was called from along with the optional massage 
#define PTRACE_0(_) s_trace("Trace", __func__, __FILE__, __LINE__)
#define PTRACE_1(msg) s_trace(msg, __func__, __FILE__, __LINE__)

#define GET_MACRO(_1,_2,NAME,...) NAME
#define PTRACE(...) GET_MACRO(__VA_ARGS__,PTRACE_1,PTRACE_0)(__VA_ARGS__)
    static void s_trace(const std::string& message,
                      const char* func,
                      const char* file,
                      int line)
    {
        PLOG()->trace(message, func, file, line);
    }

// The following #define is used so that the user can do PDEBUG("Message") and it'll print the file, function, and line number it was called from along with the debug massage 
#define PDEBUG(msg) s_debug(msg, __func__, __FILE__, __LINE__)
    static void s_debug(const std::string& message,
                      const char* func,
                      const char* file,
                      int line)
    {
        PLOG()->debug(message, func, file, line);
    }

// The following #define is used solely to match the PTRACE and PDEBUG statements
#define PINFO(msg) s_info(msg)
    static void s_info(const std::string& message)
    {
        PLOG()->info(message);
    }

// The following #define is used solely to match the PTRACE and PDEBUG statements
#define PWARN(msg) s_warn(msg)
    static void s_warn(const std::string& message)
    {
        PLOG()->warn(message);
    }

// The following #define is used solely to match the PTRACE and PDEBUG statements
#define PERROR(msg) s_error(msg)
    static void s_error(const std::string& message)
    {
        PLOG()->error(message);
    }

// The following #define is used solely to match the PTRACE and PDEBUG statements
#define PFATAL(msg) s_fatal(msg)
    static void s_fatal(const std::string& message)
    {
        PLOG()->fatal(message);
    }
}

