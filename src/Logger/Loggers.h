//
// Created by Hatsune Miku on 2023/12/26.
//

#ifndef AKKOKEYBORDDISPLAY_LOGGERS_H
#define AKKOKEYBORDDISPLAY_LOGGERS_H

#include <Arduino.h>
#include "Level.h"

namespace Logger {
    class Loggers {
    public:
        Loggers(const char *prefix) : m_Prefix(prefix), m_Tag(nullptr) {};

        Loggers(const char *prefix, const char *tag) : m_Prefix(prefix), m_Tag(nullptr) {
            setTag(tag);
        };

        ~Loggers() {
            if (m_Tag != nullptr) {
                free(m_Tag);
            }
        }

        void setTag(const char *tag);

        void trace(const char *str, ...);

        void debug(const char *str, ...);

        void info(const char *str, ...);

        void warn(const char *str, ...);

        void error(const char *str, ...);

        void fatal(const char *str, ...);

        template<typename T>
        inline void traceArray(const char *str, const T *array, size_t size) {
            logArray(Log::TRACE, str, array, size);
        }

        template<typename T>
        inline void debugArray(const char *str, const T *array, size_t size) {
            logArray(Log::DEBUG, str, array, size);
        }

        template<typename T>
        inline void infoArray(const char *str, const T *array, size_t size) {
            logArray(Log::INFO, str, array, size);
        }

        template<typename T>
        inline void warnArray(const char *str, const T *array, size_t size) {
            logArray(Log::WARN, str, array, size);
        }

        template<typename T>
        inline void errorArray(const char *str, const T *array, size_t size) {
            logArray(Log::ERROR, str, array, size);
        }

        template<typename T>
        inline void fatalArray(const char *str, const T *array, size_t size) {
            logArray(Log::FATAL, str, array, size);
        }

    private:
        void log(Log::Level level, const char *str, va_list args);

        template<typename T>
        void logArray(Log::Level level, const char *str, const T *array, size_t size) {
            if (level < LOG_LEVEL_DEBUG) {
                return;
            }

            char buf[strlen(m_Prefix) + (m_Tag == nullptr ? 0 : strlen(m_Tag)) + 2];
            strcpy(buf, m_Prefix);
            if (m_Tag != nullptr) {
                strcat(buf, ":");
                strcat(buf, m_Tag);
            }

            Serial.printf("[%-5s] [%s] %s", levelToString(level), buf, str);

            for (size_t i = 0; i < size; i++) {
                Serial.print(array[i]);
            }

            Serial.println();
        }

        const char *const m_Prefix;
        char *m_Tag;
    };
}

#endif //AKKOKEYBORDDISPLAY_LOGGERS_H
