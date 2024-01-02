//
// Created by Hatsune Miku on 2023/12/25.
//

#include "wifi.h"
#include "WebServer.h"

#include "Arduino.h"


#include <WiFi.h>
#include "SPIFFS.h"

WebServer server(80);

Logger::Loggers WifiLogger("Wifi");

IPAddress WifiNetwork::StrToIP(const String &address) {
    IPAddress IPADDS;
    IPADDS.fromString(address);
    return IPADDS;
}

bool WifiNetwork::isConfig() { // 判断是否存在wifi配置
    return SPIFFS.exists("/config/wifi.txt");
}


String echoSSID() {
    // 输出名称
    String str = Flash::ReadFlash("wifi.txt");
    int sde = str.indexOf("ssid=");
    int pde = str.indexOf("pwd=");
    return str.substring(sde + 5, pde - 1);
}

String echoPASSWD() {
    // 输出密码
    String str = Flash::ReadFlash("wifi.txt");
    int pde = str.indexOf("pwd=");
    return str.substring(pde + 4);
}

void WifiNetwork::Content() { // 初始化wifi连接

    WiFiClass::mode(WIFI_STA);

    // PasswdConfigParse(Flash::ReadFlash("wifi.txt"));

    WiFi.begin(echoSSID().c_str(), echoPASSWD().c_str());
    // WiFi.begin("kalin", "ruoxiaokelianwuzhu");
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        WifiLogger.info(String(WiFi.waitForConnectResult()).c_str());
        WifiLogger.info(WiFi.localIP().toString().c_str());
        delay(500);
        // Serial.print(".");
    }
    if (WiFi.isConnected()) {
        WifiLogger.info("连接成功");
    } else {
        WifiLogger.info("连接未成功");
    }
}


void WifiNetwork::WEBStart(const String &addr) { // 初始化wifi配置页面
    wifiWeb(addr);
}

[[noreturn]] void WifiNetwork::wifiWeb(const String &addr) {
    WiFi.softAPConfig(
            StrToIP(addr),
            StrToIP("10.0.3.1"),
            StrToIP("255.255.255.0")
    );
    WiFi.softAP("Keyboard");
    server.on("/", page::index);
    server.on("/config", page::config);
    WifiLogger.info("wifi服务开启");
    server.begin();
    while (true) {
        server.handleClient();
    }
}

void page::index() {
    String ret = String(
            "<html><head><meta charset=\"UTF-8\"><title>KeyBoard</title></head><body style=\"text-align: center\"><h2>配网</h2><p>从下列选择需要连接的网络并输入密码</p><form action=\"/config\" method=\"post\">");
    int8_t n = WiFi.scanNetworks();
    if (n == 0) {
        ret = ret + "<h2>未查询到Wi-Fi网络QAQ</h2>";
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            ret = ret + "<input type=\"radio\" name=\"ssid\" value=\"" + WiFi.SSID(i) + "\" /> " + WiFi.SSID(i) +
                  "<br>";
        }
    }
    ret = ret +
          "<p></p>WiFi密码：<input type=\"text\" name=\"pwd\"/><br><input type=\"submit\" value=\"提交\"></form></body></html>";
    server.send(200, "text/html", ret);
}


void page::config() {
    String ssid = server.arg("ssid");
    String pwd = server.arg("pwd");
    String retStr = "ssid=" + ssid + ",pwd=" + pwd;

    String ret =
            String("<html><head><meta charset=\"utf-8\"><title>KeyBoard</title></head><body>") + String("<center>") +
            String("<h2>配网写入成功</h2>") + String("<h2>已配置WiFi名称：" + ssid + "</h2>") +
            String("<h2>已配置WiFi密码:" + pwd + "</h2>") + String("<p>确认无误后，请退出页面，并重启设备～</p>") +
            String("<input type=\"submit\" value=\"返回配网页面\" onclick=\"javascript:history.back();\"></center></body></html>");

    String ret1 =
            String("<html><head><meta charset=\"utf-8\"><title>easyLink</title></head><body>") + String("<center>") +
            String("<h2>配网写入失败：缺少关键的信息</h2>") + String("<p>请返回配置页面，重新配置，并填入正确信息～</p>") +
            String("<input type=\"submit\" value=\"返回配网页面\" onclick=\"javascript:history.back();\"></center></body></html>");
    if (ssid != "" && pwd != "") {
        Flash::writeFlash(retStr, "wifi.txt");
    } else {
        server.send(200, "text/html", ret1);
    }
    server.send(200, "text/html", ret);
    delay(5000);
    ESP.restart(); // 重启模块
}