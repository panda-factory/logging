//
// Created by guozhenxiong on 2021/1/28.
//

#ifndef LOGGING_LOG_LEVEL_H
#define LOGGING_LOG_LEVEL_H
namespace wtf {

using LogSeverity = int;

// Default log levels. Negative values can be used for verbose log levels.
constexpr LogSeverity LOG_INFO = 0;
constexpr LogSeverity LOG_DEBUG = 1;
constexpr LogSeverity LOG_WARNING = 2;
constexpr LogSeverity LOG_ERROR = 3;
constexpr LogSeverity LOG_FATAL = 4;
constexpr LogSeverity LOG_NUM_SEVERITIES = 5;

// One of the Windows headers defines ERROR to 0. This makes the token
// concatenation in FML_LOG(ERROR) to resolve to LOG_0. We define this back to
// the appropriate log level.
#ifdef _WIN32
#define LOG_0 LOG_ERROR
#endif

// LOG_DFATAL is LOG_FATAL in debug mode, ERROR in normal mode
#ifdef NDEBUG
const LogSeverity LOG_DFATAL = LOG_ERROR;
#else
const LogSeverity LOG_DFATAL = LOG_FATAL;
#endif

} // namespace wtf
#endif //LOGGING_LOG_LEVEL_H
