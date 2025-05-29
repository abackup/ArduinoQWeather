#include "AirQuality.h"

AirQuality::AirQuality()
{
}

// 配置请求信息，私钥、位置
void AirQuality::config(String API_Host, String API_KEY, String Latitude, String Longitude, String Lang)
{
    _reqToken = API_KEY;
    _reqHost = API_Host;
    _reqLang = Lang;
    _reqLatitude = Latitude;
    _reqLongitude = Longitude;
}

// 尝试获取信息，成功返回true，失败返回false
bool AirQuality::get()
{
    // https请求
    String url = "https://" + _reqHost + "/airquality/v1/current/" + _reqLatitude + "/" + _reqLongitude + "?key=" + _reqToken + "&lang=" + _reqLang;

    HTTPClient http;

    http.begin(url);

    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0)
    {
        // file found at server
        if (httpCode == HTTP_CODE_OK)
        {
            WiFiClient *stream = http.getStreamPtr();
            int size = http.getSize();
            uint8_t inbuff[size];
            stream->readBytes(inbuff, size);
            uint8_t *outbuf = NULL;
            uint32_t out_size = 0;
            int result = ArduinoUZlib::decompress(inbuff, size, outbuf, out_size);
            String payload = String(outbuf, out_size);
            _parseNowJson(payload);
        }
    }
    else
    {
        return false;
    }

    http.end();
    return true;
}

int AirQuality::getAqi()
{
    return _now_aqi_int;
}

float AirQuality::getPm10()
{
    return _now_pm10_float;
}

float AirQuality::getPm2p5()
{
    return _now_pm2p5_float;
}

float AirQuality::getNo2()
{
    return _now_no2_float;
}

float AirQuality::getSo2()
{
    return _now_so2_float;
}

float AirQuality::getO3()
{
    return _now_o3_float;
}
// 解析Json信息
void AirQuality::_parseNowJson(String payload)
{

    float pm2p5_value, pm10_value, no2_value, o3_value, so2_value;

    JsonDocument doc;

    deserializeJson(doc, payload);

    JsonObject indexes_0 = doc["indexes"][0];
    _now_aqi_int = indexes_0["aqi"];

    for (JsonObject pollutant : doc["pollutants"].as<JsonArray>())
    {

        const char *pollutant_code = pollutant["code"];
        float pollutant_concentration_value = pollutant["concentration"]["value"];

        if (strcmp(pollutant_code, "pm2p5") == 0)
            pm2p5_value = pollutant_concentration_value;
        else if (strcmp(pollutant_code, "pm10") == 0)
            pm10_value = pollutant_concentration_value;
        else if (strcmp(pollutant_code, "no2") == 0)
            no2_value = pollutant_concentration_value;
        else if (strcmp(pollutant_code, "o3") == 0)
            o3_value = pollutant_concentration_value;
        else if (strcmp(pollutant_code, "so2") == 0)
            so2_value = pollutant_concentration_value;
    }
    _now_pm2p5_float = pm2p5_value;
    _now_pm10_float = pm10_value;
    _now_no2_float = no2_value;
    _now_o3_float = o3_value;
    _now_so2_float = so2_value;
}
