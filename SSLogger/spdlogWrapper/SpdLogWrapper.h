#pragma once

#include <string>
#include <memory>

#include "SSLogWrapper/ILogger.h"

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace SSLogger
{
    class SSLOGWRAPPER_LOCAL SpdLogger : public IFileLogger
    {
    public:
        SpdLogger();

        void setLogFile(const std::string& logFile) override;

        void trace(const std::string& message, // Extremely detailed information, often about program flow or internals
                   const char* func,
                   const char* file,
                   int line) override;
        void debug(const std::string& message,  // Debugging information useful during development (Disabled during release)
                   const char* func,
                   const char* file,
                   int line) override;
        void info(const std::string& message) override;   // General information about application progress
        void warn(const std::string& message) override;   // Something unexpected happened, but the program can continue
        void error(const std::string& message) override;  // A serious issue occurred, but the program can still run (maybe shutting off a particular feature or button press)
        void fatal(const std::string& message) override;  // Very severe error, often requiring immediate attention (application usually exits)
        void setGlobalLogLevel(const logLevel& newLogLevel) override;

    private:
        std::shared_ptr<spdlog::logger> mStdoutLogger;
        std::shared_ptr<spdlog::logger> mStderrLogger;
    };
}

