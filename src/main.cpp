#include <arduino.h>
#include "U8g2lib.h"

/* ========================= 接线定义 ========================
 * SDA -> GPIO21
 * SCK -> GPIO22
========================================================== */

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE); // SSD1315 0.91小长屏

void setup() {
    Serial.begin(115200);

    u8g2.begin();

    u8g2.setFont(u8g2_font_t0_11_t_all);
    u8g2.drawBox(0, 0, 128, 32);
    u8g2.sendBuffer();
}

void loop() {

}
