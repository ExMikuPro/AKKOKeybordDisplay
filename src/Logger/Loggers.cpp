//
// Created by Hatsune Miku on 2023/12/26.
//

#include "Loggers.h"
#include "Level.h"

namespace Logger {
    void Loggers::setTag(const char *tag) {
        m_Tag = (char *) malloc(strlen(tag) + 1);
        strcpy(m_Tag, tag);
    }

    void Loggers::trace(const char *format, ...) {
        va_list args;
        va_start(args, format);
        log(Log::TRACE, format, args);
        va_end(args);
    }

    void Loggers::debug(const char *format, ...) {
        va_list args;
        va_start(args, format);
        log(Log::DEBUG, format, args);
        va_end(args);
    }

    void Loggers::info(const char *format, ...) {
        va_list args;
        va_start(args, format);
        log(Log::INFO, format, args);
        va_end(args);
    }

    void Loggers::warn(const char *format, ...) {
        va_list args;
        va_start(args, format);
        log(Log::WARN, format, args);
        va_end(args);
    }

    void Loggers::error(const char *format, ...) {
        va_list args;
        va_start(args, format);
        log(Log::ERROR, format, args);
        va_end(args);
    }

    void Loggers::fatal(const char *format, ...) {
        va_list args;
        va_start(args, format);
        log(Log::FATAL, format, args);
        va_end(args);
    }

    void Loggers::log(Log::Level level, const char *format, va_list args) {
        if (level < LOG_LEVEL_DEBUG) {
            return;
        }

        char buffer[256];
        vsnprintf(buffer, 256, format, args);

        char buf[strlen(m_Prefix) + (m_Tag == nullptr ? 0 : strlen(m_Tag)) + 2];
        strcpy(buf, m_Prefix);
        if (m_Tag != nullptr) {
            strcat(buf, ":");
            strcat(buf, m_Tag);
        }

        Serial.printf("[%-5s] [%s] %s\n", levelToString(level), buf, buffer);
    }
}