#include <string>

#include "spdlogWrapper/SpdLogWrapper.h"

namespace SSLogger
{
    const std::string LOGGER_NAME = "spd_logger";

    SpdLogger::SpdLogger()
    {
        auto consoleSinkStdout = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        mStdoutLogger = std::make_shared<spdlog::logger>(LOGGER_NAME, consoleSinkStdout);

        auto consoleSinkStderr = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
        mStderrLogger = std::make_shared<spdlog::logger>(LOGGER_NAME, consoleSinkStderr);
    }

    void SpdLogger::setGlobalLogLevel(const logLevel& newLogLevel)
    {
        ILogger::setGlobalLogLevel(newLogLevel);
        switch(newLogLevel)
        {
            case logLevel::pTRACE:
                SSLogger::PLOG()->info("Setting log level: TRACE");
                mStdoutLogger->set_level(spdlog::level::trace);
                mStderrLogger->set_level(spdlog::level::trace);
                break;
            case logLevel::pDEBUG:
                SSLogger::PLOG()->info("Setting log level: DEBUG");
                mStdoutLogger->set_level(spdlog::level::debug);
                mStderrLogger->set_level(spdlog::level::debug);
                break;
            case logLevel::pINFO:
                SSLogger::PLOG()->info("Setting log level: INFO");
                mStdoutLogger->set_level(spdlog::level::info);
                mStderrLogger->set_level(spdlog::level::info);
                break;
            case logLevel::pWARN:
                SSLogger::PLOG()->info("Setting log level: WARN");
                mStdoutLogger->set_level(spdlog::level::warn);
                mStderrLogger->set_level(spdlog::level::warn);
                break;
            case logLevel::pERROR:
                SSLogger::PLOG()->info("Setting log level: ERROR");
                mStdoutLogger->set_level(spdlog::level::err);
                mStderrLogger->set_level(spdlog::level::err);
                break;
            case logLevel::pFATAL:
                SSLogger::PLOG()->info("Setting log level: FATAL");
                mStdoutLogger->set_level(spdlog::level::critical);
                mStderrLogger->set_level(spdlog::level::critical);
                break;
        }
    }

    void SpdLogger::setLogFile(const std::string& logFile)
    {
        if (mStdoutLogger)
        {
            mStdoutLogger.reset();
        }

        if (mStderrLogger)
        {
            mStderrLogger.reset();
        }

        auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFile, true);

        auto consoleSinkStdout = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        mStdoutLogger = std::make_shared<spdlog::logger>(LOGGER_NAME, spdlog::sinks_init_list{consoleSinkStdout, fileSink});
        
        auto consoleSinkStderr = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
        mStderrLogger = std::make_shared<spdlog::logger>(LOGGER_NAME, spdlog::sinks_init_list{consoleSinkStderr, fileSink});

        setGlobalLogLevel(mGlobalLevel);
    }
    
    void SpdLogger::trace(const std::string& message,
                          const char* func/* = __func__,*/,
                          const char* file/* = __FILE__*/,
                          int line/* = __LINE__*/)
    {
        mStdoutLogger->trace(std::string(file) + ":" + std::to_string(line) + " in " + std::string(func) + " --> " + message);
    }
    
    void SpdLogger::debug(const std::string& message,
                          const char* func/* = __func__,*/,
                          const char* file/* = __FILE__*/,
                          int line/* = __LINE__*/)
    {
        mStdoutLogger->debug(std::string(file) + ":" + std::to_string(line) + " in " + std::string(func) + " --> " + message);
    }
    
    void SpdLogger::info(const std::string& message)
    {
        mStdoutLogger->info(message);
    }
    
    void SpdLogger::warn(const std::string& message)
    {
        mStdoutLogger->warn(message);
    }
    
    void SpdLogger::error(const std::string& message)
    {
        mStderrLogger->error(message);
    }

    void SpdLogger::fatal(const std::string& message)
    {
        mStderrLogger->critical(message);
    }
}

