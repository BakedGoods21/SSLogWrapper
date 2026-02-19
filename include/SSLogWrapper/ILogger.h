#pragma once

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define SSLOGWRAPPER_IMPORT_ATTRIB __declspec(dllimport)
  #define SSLOGWRAPPER_EXPORT_ATTRIB __declspec(dllexport)
  #define SSLOGWRAPPER_LOCAL_ATTRIB
#else
  #if __GNUC__ >= 4
    #define SSLOGWRAPPER_IMPORT_ATTRIB __attribute__ ((visibility ("default")))
    #define SSLOGWRAPPER_EXPORT_ATTRIB __attribute__ ((visibility ("default")))
    #define SSLOGWRAPPER_LOCAL_ATTRIB __attribute__ ((visibility ("hidden")))
  #else
    #define SSLOGWRAPPER_IMPORT_ATTRIB
    #define SSLOGWRAPPER_EXPORT_ATTRIB
    #define SSLOGWRAPPER_LOCAL_ATTRIB
  #endif
#endif

// Now we use the generic helper definitions above to define SSLOGWRAPPER_API and SSLOGWRAPPER_LOCAL.
// SSLOGWRAPPER_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// SSLOGWRAPPER_LOCAL is used for non-api symbols.

#ifdef SSLOGWRAPPER_DLL // defined if SSLOGWRAPPER is compiled as a DLL
  #ifdef SSLOGWRAPPER_DLL_EXPORTS // defined if we are building the SSLOGWRAPPER DLL (instead of using it)
    #define SSLOGWRAPPER_API SSLOGWRAPPER_EXPORT_ATTRIB
  #else
    #define SSLOGWRAPPER_API SSLOGWRAPPER_IMPORT_ATTRIB
  #endif // SSLOGWRAPPER_DLL_EXPORTS
  #define SSLOGWRAPPER_LOCAL SSLOGWRAPPER_LOCAL_ATTRIB
#else // SSLOGWRAPPER_DLL is not defined: this means SSLOGWRAPPER is a static lib.
  #define SSLOGWRAPPER_API
  #define SSLOGWRAPPER_LOCAL
#endif // SSLOGWRAPPER_DLL


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


    class SSLOGWRAPPER_API ILogger
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

    class SSLOGWRAPPER_API IFileLogger : public ILogger
    {
    public:
        IFileLogger() = default;
        ~IFileLogger() = default;

        virtual void setLogFile(const std::string& logFile) = 0;
    };

    extern SSLOGWRAPPER_API std::shared_ptr<ILogger> PLOG();
    extern SSLOGWRAPPER_API void _setPLogger(std::shared_ptr<ILogger> newLogger);

    template <typename T, typename... Args>
    SSLOGWRAPPER_API void setPLogger(Args... rest_args)
    {
        _setPLogger(std::make_shared<T>(T(rest_args...)));
    }

    extern SSLOGWRAPPER_API void setLogFile(const std::string& logFile);
    extern SSLOGWRAPPER_API void setLevel(logLevel newGlobalLogLevel);

// The following #define's are used so that the user can do PTRACE("Message") or PTRACE() and it'll print the file, function, and line number it was called from along with the optional massage 
#define PTRACE_0(_) s_trace("Trace", __func__, __FILE__, __LINE__)
#define PTRACE_1(msg) s_trace(msg, __func__, __FILE__, __LINE__)

#define GET_MACRO(_1,_2,NAME,...) NAME
#define PTRACE(...) GET_MACRO(__VA_ARGS__,PTRACE_1,PTRACE_0)(__VA_ARGS__)
    extern SSLOGWRAPPER_API void s_trace(const std::string& message,
                      const char* func,
                      const char* file,
                      int line);

// The following #define is used so that the user can do PDEBUG("Message") and it'll print the file, function, and line number it was called from along with the debug massage 
#define PDEBUG(msg) s_debug(msg, __func__, __FILE__, __LINE__)
    extern SSLOGWRAPPER_API void s_debug(const std::string& message,
                      const char* func,
                      const char* file,
                      int line);

// The following #define is used solely to match the PTRACE and PDEBUG statements
#define PINFO(msg) s_info(msg)
    extern SSLOGWRAPPER_API void s_info(const std::string& message);

// The following #define is used solely to match the PTRACE and PDEBUG statements
#define PWARN(msg) s_warn(msg)
    extern SSLOGWRAPPER_API void s_warn(const std::string& message);

// The following #define is used solely to match the PTRACE and PDEBUG statements
#define PERROR(msg) s_error(msg)
    extern SSLOGWRAPPER_API void s_error(const std::string& message);

// The following #define is used solely to match the PTRACE and PDEBUG statements
#define PFATAL(msg) s_fatal(msg)
    extern SSLOGWRAPPER_API void s_fatal(const std::string& message);
}

