# ArduinoQWeather

- [ArduinoQWeather](#arduinoqweather)
  * [基本介绍](#基本介绍)
  * [准备工作](#准备工作)
  * [使用说明](#使用说明)
    + [获取实时天气信息](#获取实时天气信息)
    + [获取实时空气质量信息](#获取实时空气质量信息)

## 基本介绍

**Arduino** 平台使用 **ESP32** 获取 **和风天气** 的第三方库（原地址：[Ldufan](https://github.com/Ldufan/ESP8266_Heweather)，[ye-zhang0720](https://github.com/ye-zhang0720/ESP32_HEWEATHER)），更新了和风 API v7.15。



此库用于 **ESP32** 物联网开发板通过 **HTTPS 协议** 获取和风天气API所提供的免费天气信息。使用此库可以省去繁杂的 HTTPS 请求以及 JSON 解析部分，使用几行代码即可获取有效信息，大大简化了开发步骤。

> 注：
>
> - 已在ESP32-C3上测试，其他硬件未测试； 
> - 由于信息的安全性要求不高，故 HTTPS 请求中设置了不进行身份校验；
> - 只涉及常人经常关注的信息如`温度`、`湿度`、`风力`、`空气质量`等。



## 准备工作

1. 注册和风天气并到控制台获得 API KEY，详见 [控制台](https://console.qweather.com)  -> 我的项目 -> 凭证 -> API KEY；

2. 获得 API Host,详见 [控制台](https://console.qweather.com)  -> 设置 -> API Host；

3. 安装ESP32开发版管理程序

4. 安装 **ArduinoJson** 库，详见 [arduinojson](https://github.com/bblanchon/ArduinoJson) ；
   安装 **ArduinoUZlib** 库，详见 [ArduinoUZlib](https://github.com/tignioj/ArduinoUZlib) ;

	其他说明：

	- 查询 [城市代码](https://github.com/qwd/LocationList/blob/master/China-City-List-latest.csv)，查找城市 Location_ID 和经纬度 （经度 Longitude，纬度 Latitude）。

	- 和风天气开发者 **[官方文档](https://dev.qweather.com/docs/start/)** 。 

## 使用说明

1. 安装本库

	1）下载压缩包或克隆；

	2）解压并复制到 **项目文件夹** 下的 **libraries** 目录下；

	3）重启 Arduino IDE。

2. **[example](https://github.com/abackup/ArduinoQWeather/tree/master/example)** 目录中列出了使用的基本结构和所有函数示例，为主要参考文档；

### 获取实时天气信息

  ```c++
WeatherNow weatherNow;         // 建立weatherNow对象

weatherNow.config(API_Host, API_KEY, Location_ID, Unit, Lang); // 配置请求信息

weatherNow.getServerCode();     // 获取API状态码   
weatherNow.getLastUpdate();     // 获取服务器更新天气信息时间
weatherNow.getTemp();           // 获取实况温度
weatherNow.getFeelLike();       // 获取实况体感温度
weatherNow.getIcon();           // 获取当前天气图标代码
weatherNow.getWeatherText();    // 获取实况天气状况的文字描述
weatherNow.getWind360();        // 获取实况风向角度
weatherNow.getWindDir();        // 获取实况风向
weatherNow.getWindScale();      // 获取实况风力等级
weatherNow.getHumidity();       // 获取实况相对湿度百分比数值
weatherNow.getPrecip();         // 获取实况降水量,毫米
weatherNow.getPressure();       // 获取实况大气压
weatherNow.getVis();            // 获取实况能见度
weatherNow.getCloud();          // 获取实况云层
weatherNow.getDew();            // 获取实况露点
  ```



### 获取实时空气质量信息

```c++
AirQuality airQuality;           // 建立airQuality对象

airQuality.config(API_Host, API_KEY, Latitude, Longitude, Lang); // 配置请求信息

airQualityir.getAqi();              // 实时空气质量指数
airQualityir.getPm10();             // 实时空气Pm10
airQualityir.getPm2p5();            // 实时空气Pm2.5
airQualityir.getNo2();              // 实时空气No2
airQualityir.getSo2();              // 实时空气So2
airQualityir.getO3();               // 实时空气O3浓度
```





















