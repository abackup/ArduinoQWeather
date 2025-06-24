#include <Arduino.h>
#include "ArduinoJson.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "ArduinoUZlib.h"
#pragma once

class AirQuality
{
public:
  AirQuality();

  void config(String API_Host, String API_KEY, String Latitude, String Longitude, String Lang);

  bool get();
  int getAqi();
  float getPm2p5();
  float getPm10();
  float getNo2();
  float getO3();
  float getSo2();

private:
  String _reqToken; // 私钥
  String _reqLatitude;
  String _reqLongitude;
  String _reqHost;
  String _reqLang; // 语言

  const char *_host = _reqHost.c_str(); // 服务器地址
  const int httpsPort = 443;

  void _parseNowJson(String payload); // 解析json信息
  int _now_aqi_int = 999;             // 实况温度
  float _now_pm10_float = 0;          // 实况pm10
  float _now_pm2p5_float = 0;         // 实况pm2.5
  float _now_no2_float = 0;           // 实况no2
  float _now_so2_float = 0;           // 实况so2
  float _now_co_float = 0;            // 实况co
  float _now_o3_float = 0;            // 实况o3
};
