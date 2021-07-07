//
// Created by guozhenxiong on 2021/1/28.
//

#include "logging.h"

#include <algorithm>
#include <iostream>

#if defined(OS_ANDROID)
#include <android/log.h>
#elif defined(OS_IOS)
#include <syslog.h>
#elif defined(OS_WIN)
#include <windows.h>
#ifdef max
#undef max
#endif
#endif

#include "log_setting.h"

namespace wtf {
namespace {

const char* const kLogSeverityNames[LOG_NUM_SEVERITIES] = {"INFO", "DEBUG", "WARNING",
                                                           "ERROR", "FATAL"};

const char* GetNameForLogSeverity(LogSeverity severity) {
    if (severity >= LOG_INFO && severity < LOG_NUM_SEVERITIES) {
        return kLogSeverityNames[severity];
    }
    return "UNKNOWN";
}

const char* StripDots(const char* path) {
    while (strncmp(path, "../", 3) == 0) {
        path += 3;
    }
    return path;
}

const char* StripPath(const char* path) {
    auto* p = strrchr(path, '/');
    if (p) {
        return p + 1;
    }
    return path;
}

}  // namespace

LogMessage::LogMessage(LogSeverity severity,
                       const char* file,
                       int line,
                       const char* condition)
        : severity_(severity), file_(file), line_(line) {
    stream_ << "[";
    if (severity >= LOG_INFO) {
        stream_ << GetNameForLogSeverity(severity);
    } else {
        stream_ << "VERBOSE" << -severity;
    }
    stream_ << ":" << (severity > LOG_INFO ? StripDots(file_) : StripPath(file_))
            << "(" << line_ << ")] ";

    if (condition) {
        stream_ << "Check failed: " << condition << ". ";
    }
}

LogMessage::~LogMessage() {
    stream_ << std::endl;

#if defined(OS_ANDROID)
    android_LogPriority priority =
      (severity_ < 0) ? ANDROID_LOG_VERBOSE : ANDROID_LOG_UNKNOWN;
  switch (severity_) {
    case LOG_INFO:
      priority = ANDROID_LOG_INFO;
      break;
    case LOG_WARNING:
      priority = ANDROID_LOG_WARN;
      break;
    case LOG_ERROR:
      priority = ANDROID_LOG_ERROR;
      break;
    case LOG_FATAL:
      priority = ANDROID_LOG_FATAL;
      break;
  }
  __android_log_write(priority, "core", stream_.str().c_str());
#elif defined(OS_IOS)
    syslog(LOG_ALERT, "%s", stream_.str().c_str());
#else
    std::cerr << stream_.str();
    std::cerr.flush();
#endif

    if (severity_ >= LOG_FATAL) {
        KillProcess();
    }
}

int GetVlogVerbosity() {
    return std::max(-1, LOG_INFO - GetMinLogLevel());
}

bool ShouldCreateLogMessage(LogSeverity severity) {
    return severity >= GetMinLogLevel();
}

void KillProcess() {
    abort();
}

}  // namespace wtf