#include <arduino.h>
#include "U8g2lib.h"
#include "SPIFFS.h"

#include "network/wifi.h"
#include "Flash/flash.h"
#include "WiFi.h"

/* ========================= 接线定义 ========================
 * SDA -> GPIO21
 * SCK -> GPIO22
========================================================== */

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE); // SSD1315 0.91小长屏

void setup() {
    Serial.begin(115200);
    SPIFFS.begin();
    // Flash::FormatFlash(); // 格式化内存
    u8g2.begin();
    u8g2.enableUTF8Print();

    u8g2.setFont(u8g2_font_wqy12_t_gb2312);
    if (!WifiNetwork::isConfig()) {
        u8g2.drawUTF8(0, 12, "连接组件wifi : Keyboard");
        u8g2.drawUTF8(0, 25, "打开 10.0.3.9");
        u8g2.sendBuffer();
        WifiNetwork::WEBStart("10.0.3.9");
    } else {
        WifiNetwork::Content();  // wifi连接
        // Flash::FormatFlash();
    }
}

void loop() {

}
