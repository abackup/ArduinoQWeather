#include <ArduinoQWeather.h>

const char *ssid = "****";     // WiFi名称
const char *passwd = "********"; // WiFi密码

String API_KEY = "********7c4e63a03dcb2ec0af98bc"; // api-key                  //
String Location_ID = "10119****";                     //
String API_Host = "********gg.re.qweatherapi.com";
String Unit = "m";  // 公制-m/英制-i
String Lang = "en"; // 语言 英文-en/中文-zh
float ROUND = 0.2;  // 更新间隔<分钟>实时天气API 10~20分钟更新一次

WeatherNow weatherNow;
void ConnectWiFi();

void setup()
{
  Serial.begin(115200);
  Serial.println("");

  ConnectWiFi();                                            // 连接WiFi
  weatherNow.config(API_Host, API_KEY , Location_ID, Unit, Lang); // 配置请求信息
}

void loop()
{
  if (weatherNow.get())
  { // 获取天气更新
    Serial.println(F("======Weahter Now Info======"));
    Serial.print("Server Response: ");
    Serial.println(weatherNow.getCode()); // 获取API状态码
    Serial.print(F("Last Update: "));
    Serial.println(weatherNow.getObsTime()); // 获取服务器更新天气信息时间
    Serial.print(F("Temperature: "));
    Serial.println(weatherNow.getTemp()); // 获取实况温度
    Serial.print(F("FeelsLike: "));
    Serial.println(weatherNow.getFeelLike()); // 获取实况体感温度
    Serial.print(F("Icon: "));
    Serial.println(weatherNow.getIcon()); // 获取当前天气图标代码
    Serial.print(F("Weather Now: "));
    Serial.println(weatherNow.getText()); // 获取实况天气状况的文字描述
    Serial.print(F("windDir: "));
    Serial.println(weatherNow.getWindDir()); // 获取实况风向
    Serial.print(F("WindScale: "));
    Serial.println(weatherNow.getWindScale()); // 获取实况风力等级
    Serial.print(F("Humidity: "));
    Serial.println(weatherNow.getHumidity()); // 获取实况相对湿度百分比数值
    Serial.print(F("Precip: "));
    Serial.println(weatherNow.getPrecip()); // 获取实况降水量,毫米
    Serial.print(F("Pressure: "));
    Serial.println(weatherNow.getPressure()); // 获取实况风力等级
    Serial.print(F("Vis: "));
    Serial.println(weatherNow.getVis()); // 获取实况风力等级
    Serial.print(F("Cloud: "));
    Serial.println(weatherNow.getCloud()); // 获取实况风力等级
    Serial.print(F("Dew: "));
    Serial.println(weatherNow.getDew()); // 获取实况风力等级
    Serial.print(F("Wind360: "));
    Serial.println(weatherNow.getWind360()); // 获取实况风力等级
    Serial.print(F("WindSpeed: "));
    Serial.println(weatherNow.getWindSpeed()); // 获取实况风力等级

    Serial.println(F("========================"));
  }
  else
  { // 更新失败
    Serial.println("Update Failed...");
    Serial.print("Server Response: ");
    Serial.println(weatherNow.getCode()); // 参考 https://dev.heweather.com/docs/start/status-code
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
