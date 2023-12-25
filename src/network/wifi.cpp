//
// Created by Hatsune Miku on 2023/12/25.
//

#include "wifi.h"
#include "WebServer.h"


#include <WiFi.h>
#include "SPIFFS.h"

WebServer server(80);

IPAddress WifiNetwork::StrToIP(const String &address) {
    IPAddress IPADDS;
    IPADDS.fromString(address);
    return IPADDS;
}

bool WifiNetwork::isConfig() { // 判断收否存在wifi配置
    return SPIFFS.exists("/config/wifi.txt");
}

void WifiNetwork::setUp() { // 初始化wifi连接
}


void WifiNetwork::setUp(const String &addr) { // 初始化wifi连接
    wifiWeb(addr);
}

[[noreturn]] void WifiNetwork::wifiWeb(const String &addr) {
    WiFi.softAPConfig(
            StrToIP(addr),
            StrToIP("10.0.3.1"),
            StrToIP("255.255.255.0")
    );
    WiFi.softAP("Link");
    server.on("/", page::index);
    server.on("/config", page::config);
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

void writeFlash(String str, String filename) {
    SPIFFS.format();
    File dataFile = SPIFFS.open("/config/" + filename, "w");
    Serial.println("参数写入：");
    Serial.println(str);
    Serial.println(dataFile.println(str));
    dataFile.close();
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

        writeFlash(retStr, "wifi.txt");

    } else {
        server.send(200, "text/html", ret1);
    }

    server.send(200, "text/html", ret);
    delay(5000);
    ESP.restart(); // 重启模块
}