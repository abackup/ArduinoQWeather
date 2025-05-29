#include <ArduinoQWeather.h>

const char *ssid = "****";     // WiFi名称
const char *passwd = "********"; // WiFi密码

String API_KEY = "********21f7c4e63a03dcb2ec0af98bc"; // api-key                  //
String API_Host = "************g.re.qweatherapi.com";
String Latitude = "**.03";
String Longitude = "***.79";
String Lang = "en"; // 语言 英文-en/中文-zh
float ROUND = 0.2;  // 更新间隔<分钟>

AirQuality airQuality;
void ConnectWiFi();

void setup()
{
  Serial.begin(115200);
  Serial.println("");

  ConnectWiFi();                                                 // 连接WiFi
  airQuality.config(API_Host, API_KEY, Latitude, Longitude, Lang); // 配置请求信息
}

void loop()
{
  if (airQuality.get())
  { // 获取天气更新
    Serial.println(F("======Weahter Now Info======"));
    Serial.print(F("Aqi: "));
    Serial.println(airQuality.getAqi()); // 获取实况Aqi
    Serial.print(F("Pm10: "));
    Serial.println(airQuality.getPm10()); // 获取实况Pm10
    Serial.print(F("Pm2.5: "));
    Serial.println(airQuality.getPm2p5()); // 获取实况Pm2p5
    Serial.print(F("No2: "));
    Serial.println(airQuality.getNo2()); // 获取实况No2
    Serial.print(F("So2: "));
    Serial.println(airQuality.getSo2()); // 获取实况So2
    Serial.print(F("O3: "));
    Serial.println(airQuality.getO3()); // 获取实况O3

    Serial.println(F("========================"));
  }
  else
  { // 更新失败
    Serial.println("Update Failed...");
  }
  delay(ROUND * 60000);
}


// 连接WiFi
void ConnectWiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passwd);
  Serial.print("Connecting to ");
  Serial.print(ssid);

  int i = 0;
  while (WiFi.status() != WL_CONNECTED && (i < 10))
  {
    delay(1000);
    Serial.print('.');
    i++;
  }
  if (i == 10)
  { // 10s失败
    Serial.println("WiFi Connection Failed");
  }
  else
  { // 成功
    Serial.println("");
    Serial.println("WiFi Connection Successful!");
    Serial.print("IP address:   ");
    Serial.println(WiFi.localIP());
  }
}
