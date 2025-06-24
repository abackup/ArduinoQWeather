#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "ArduinoUZlib.h"
#pragma once

class WeatherNow
{
public:
  WeatherNow();

  void config(String API_Host, String API_KEY, String Location_ID, String Unit, String Lang);

  bool get();

  String getCode();
  String getObsTime();
  int getTemp();
  int getFeelLike();
  int getIcon();
  String getText();
  int getWind360();
  String getWindDir();
  int getWindScale();
  int getWindSpeed();
  float getHumidity();
  float getPrecip();
  int getPressure();
  int getVis();
  int getCloud();
  int getDew();

private:
  String _reqToken;    // 私钥
  String _reqLocation; // 位置
  String _reqHost;
  String _reqUnit; // 单位
  String _reqLang; // 语言

  const char *_host = _reqHost.c_str(); // 服务器地址
  const int httpsPort = 443;

  void _parseNowJson(String payload); // 解析json信息

  String _response_code = "no_init";   // API状态码
  String _last_update_str = "no_init"; // 当前API最近更新时间
  int _now_temp_int = 0;               // 实况温度
  int _now_feelsLike_int = 0;          // 实况体感温度
  int _now_icon_int = 0;               // 当前天气状况和图标的代码
  String _now_text_str = "no_init";    // 实况天气状况的文字描述
  String _now_windDir_str = "no_init"; // 实况风向
  int _now_windScale_int = 0;          // 实况风力等级
  float _now_humidity_float = 0;       // 实况相对湿度百分比数值
  float _now_precip_float = 0;         // 实况降水量,毫米
  int _now_pressure_int = 0;           // 实况气压,百帕
  int _now_vis_int = 0;                // 实况能见度,公里
  int _now_cloud_int = 0;              // 实况云量,百分比数值
  int _now_dew_int = 0;                // 实况露点温度
  int _now_windSpeed_int = 0;          // 实况风速,米/秒
  int _now_wind360_int = 0;            // 实况风向,360度
};
