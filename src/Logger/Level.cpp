//
// Created by Hatsune Miku on 2023/12/26.
//

#include "Level.h"


namespace Log {
    const char *levelToString(Level level) {
        switch (level) {
            case TRACE:
                return "TRACE";
            case DEBUG:
                return "DEBUG";
            case INFO:
                return "INFO";
            case WARN:
                return "WARN";
            case ERROR:
                return "ERROR";
            case FATAL:
                return "FATAL";
            default:
                return "UNKNOWN";
        }
    }
}

