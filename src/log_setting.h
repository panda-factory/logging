//
// Created by guozhenxiong on 2021/1/28.
//

#ifndef LOGGING_LOG_SETTING_H
#define LOGGING_LOG_SETTING_H
#include "logging/log_level.h"
namespace wtf {

struct LogSettings {

    LogSeverity min_log_level = LOG_INFO;
    size_t max_log_size = 4096;
};

void SetLogSettings(const LogSettings& settings);

LogSettings GetLogSettings();

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
