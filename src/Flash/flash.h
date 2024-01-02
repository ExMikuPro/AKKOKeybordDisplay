//
// Created by Hatsune Miku on 2023/12/26.
//

#ifndef AKKOKEYBORDDISPLAY_FLASH_H
#define AKKOKEYBORDDISPLAY_FLASH_H

#endif //AKKOKEYBORDDISPLAY_FLASH_H

#include "Arduino.h"
#include "SPIFFS.h"


namespace Flash { // flash操作函数
    void writeFlash(const String &str, const String &filename);

    void FormatFlash();

    String ReadFlash(const String& name);
}
