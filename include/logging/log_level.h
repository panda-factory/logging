//
// Created by guozhenxiong on 2021/1/28.
//

#ifndef LOGGING_LOG_LEVEL_H
#define LOGGING_LOG_LEVEL_H
namespace wtf {

using LogSeverity = int;

constexpr LogSeverity LOG_INFO = 0;
constexpr LogSeverity LOG_DEBUG = 1;
constexpr LogSeverity LOG_WARNING = 2;
constexpr LogSeverity LOG_ERROR = 3;
constexpr LogSeverity LOG_FATAL = 4;
constexpr LogSeverity LOG_NUM_SEVERITIES = 5;

#ifdef _WIN32
#define LOG_0 LOG_ERROR
#endif

#ifdef NDEBUG
const LogSeverity LOG_DFATAL = LOG_ERROR;
#else
const LogSeverity LOG_DFATAL = LOG_FATAL;
#endif

} // namespace wtf
#endif //LOGGING_LOG_LEVEL_H
