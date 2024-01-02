//
// Created by Hatsune Miku on 2023/12/26.
//

#include "flash.h"

#include "Logger/Loggers.h"

Logger::Loggers FlashLogger("Flash");

void Flash::writeFlash(const String &str, const String &filename) { // 向FLASH写入
    SPIFFS.format();
    File dataFile = SPIFFS.open("/config/" + filename, "w");
    FlashLogger.info("WiFi配置:");
    FlashLogger.info(str.c_str());
    dataFile.println(str);
    dataFile.close();
}

void Flash::FormatFlash() { // 格式化FLASH
    FlashLogger.warn("格式化内部存储");
    if (SPIFFS.format()) {
        FlashLogger.info("格式化内部存储成功");
    } else {
        FlashLogger.error("格式化内部存储失败");
    }
}

String Flash::ReadFlash(const String &name) {
    if (SPIFFS.exists("/config/" + name)) {
        File dataFile = SPIFFS.open("/config/" + name, "r");
        String retStr;
        for (int i = 0; i < dataFile.size(); i++) {
            retStr += (char) dataFile.read();
        }
        dataFile.close();
        return retStr;
    }
    return "error";
}
