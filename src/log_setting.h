//
// Created by guozhenxiong on 2021/1/28.
//

#ifndef LOGGING_LOG_SETTING_H
#define LOGGING_LOG_SETTING_H
#include "log_level.h"
namespace wtf {

// Settings which control the behavior of FML logging.
struct LogSettings {

    LogSeverity min_log_level = LOG_INFO;
    size_t max_log_size = 4096;
};

// Gets the active log settings for the current process.
void SetLogSettings(const LogSettings& settings);

// Sets the active log settings for the current process.
LogSettings GetLogSettings();

// Gets the minimum log level for the current process. Never returs a value
// higher than LOG_FATAL.
int GetMinLogLevel();

class ScopedSetLogSettings {
public:
    ScopedSetLogSettings(const LogSettings& settings);
    ~ScopedSetLogSettings();

private:
    LogSettings old_settings_;
};

} // namespace wtf


#endif //LOGGING_LOG_SETTING_H
