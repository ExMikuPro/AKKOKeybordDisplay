//
// Created by Hatsune Miku on 2023/12/25.
//

#ifndef AKKOKEYBORDDISPLAY_WIFI_H
#define AKKOKEYBORDDISPLAY_WIFI_H

#endif //AKKOKEYBORDDISPLAY_WIFI_H

#include "Arduino.h"
#include "webPage.h"
#include "Logger/Loggers.h"
#include "Flash/flash.h"

namespace WifiNetwork {
    IPAddress StrToIP(const String &address);

    bool isConfig();

    void Content();

    void WEBStart(const String &addr);

    [[noreturn]] void wifiWeb(const String &addr);
}

namespace page {
    void index();

    void config();
}